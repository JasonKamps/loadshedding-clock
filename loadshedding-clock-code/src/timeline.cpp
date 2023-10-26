#include "timeline.h"

#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
#define MAX_DEVICES 1
#define CLK_PIN 18
#define DATA_PIN 23
#define CS_PIN 19

MD_MAX72XX timelineLEDs = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

const int SECONDS_IN_DAY = 86400;
const int GMT_OFFSET = 7200; // 2 hours
const int LED_COUNT = 48;

void setupTimeline()
{
    Serial.println("Setting up timeline...");

    timelineLEDs.begin();
    timelineLEDs.clear();
}

/**
 * Updates the timeline with the given schedule.
 * The upcoming loadshedding events (<24h) will be displayed on the LED array.
 *
 * @param schedule The schedule with which to update the timeline.
 */
void updateTimeline(Schedule schedule)
{
    clearTimelineLEDs();

    // iterate through events and set LED states
    for (int i = 0; i < schedule.numberOfEvents; i++)
    {
        Event event = schedule.events[i];

        // display on timeline if event is currently occuring, or will occur within the next 24 hours
        if (event.isCurrentlyOccuring() || event.end - getUnixTime() < SECONDS_IN_DAY)
        {
            updateTimelineWithEvent(event);
        }
    }
}

/**
 * Updates the timeline with the given event.
 * The LEDs corresponding to the duration of the event will be turned on.
 *
 * @param event The event with which to update the timeline.
 */
void updateTimelineWithEvent(Event event)
{
    // calculate the number of seconds from midnight to the start and end of the event
    int secondsFromMidnightToStart = (event.start + GMT_OFFSET) % SECONDS_IN_DAY;
    int secondsFromMidnightToEnd = (event.end + GMT_OFFSET) % SECONDS_IN_DAY;

    // determine the first and last LED to be turned on
    int firstLED = round(secondsFromMidnightToStart / (SECONDS_IN_DAY / LED_COUNT));
    int lastLED = round(secondsFromMidnightToEnd / (SECONDS_IN_DAY / LED_COUNT));

    // turn on LEDs
    int i = firstLED;
    while (i != lastLED)
    {
        setLED(i);
        i = (i + 1) % LED_COUNT;
    }
}

/**
 * Turns on the LED at the given index.
 *
 * @param index The index of the LED (0-47).
 */
void setLED(int index)
{
    // convert index to row and column of 8x8 matrix before using setPoint()
    int row = index / 8;
    int col = index % 8;

    timelineLEDs.setPoint(row, col, true);
}

/**
 * Turns off entire LED array.
 */
void clearTimelineLEDs()
{
    timelineLEDs.clear();
}

/**
 * Sweep the timeline LEDs from left to right.
 */
void sweepTimelineLEDs()
{
    for (int i = 0; i < 48; i++)
    {
        clearTimelineLEDs();
        setLED(i);
        delay(25);
    }

    clearTimelineLEDs();
}
