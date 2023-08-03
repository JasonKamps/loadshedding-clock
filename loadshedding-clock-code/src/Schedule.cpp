#include "Schedule.h"

// Default constructor
Schedule::Schedule()
{
    this->numberOfEvents = 0;
    this->events = NULL;
}

/**
 * Updates the schedule.
 *
 * This method reads the events from storage and populates the array of events.
 */
void Schedule::update()
{
    Serial.println("Updating schedule...");

    // read events from storage
    DynamicJsonDocument doc = readEvents();

    // get the number of events
    this->numberOfEvents = doc.size();

    if (this->numberOfEvents == 0)
    {
        Serial.println("No events found.");
        return;
    }

    // create array of events
    this->events = new Event[this->numberOfEvents];

    // populate array of events
    for (int i = 0; i < this->numberOfEvents; i++)
    {
        time_t start = convertStringToUnixTime(doc[i]["start"]);
        time_t end = convertStringToUnixTime(doc[i]["end"]);
        String note = doc[i]["note"];
        int stage = note.substring(6).toInt();
        this->events[i] = Event(start, end, stage);
    }

    Serial.println("Schedule updated.");
}

/**
 * Checks if currently loadshedding.
 *
 * @return True if any loadshedding event is occuring, false otherwise.
 */
boolean Schedule::isCurrentlyLoadshedding()
{
    time_t now = getUnixTime();

    for (int i = 0; i < this->numberOfEvents; i++)
    {
        if (this->events[i].isCurrentlyOccuring())
        {
            return true;
        }
    }

    return false;
}

/**
 * Gets the number of seconds until the next transition.
 *
 * @return The number of seconds until the next (soonest) transition. If no transition is scheduled, returns -1.
 */
int Schedule::getSecondsUntilNextTransition()
{
    int secondsUntilNextTransition = INT_MAX;

    for (int i = 0; i < this->numberOfEvents; i++)
    {
        int currentSecondsUntilNextTransition = this->events[i].getSecondsUntilNextTransition();
        if (currentSecondsUntilNextTransition > 0 && currentSecondsUntilNextTransition < secondsUntilNextTransition)
        {
            secondsUntilNextTransition = currentSecondsUntilNextTransition;
        }
    }

    if (secondsUntilNextTransition == INT_MAX)
    {
        return -1;
    }
    return secondsUntilNextTransition;
}

/**
 * Gets the highest stage of current/upcoming loadshedding events.
 *
 * @return The highest upcoming stage of loadshedding.
 */
int Schedule::getHighestUpcomingStage()
{
    int highestStage = 0;

    for (int i = 0; i < this->numberOfEvents; i++)
    {
        time_t eventEnd = this->events[i].end;
        int eventStage = this->events[i].stage;

        // check if event ends in the future
        if (eventEnd > getUnixTime())
        {
            if (eventStage > highestStage)
            {
                highestStage = eventStage;
            }
        }
    }

    return highestStage;
}
/**
 * Checks if the given Unix time falls on the same day as today.
 *
 * @param time The Unix time to check.
 * @return True if the given time is today, false otherwise.
 */
boolean isToday(time_t time)
{
    // get Unix time for start of today
    struct tm startOfToday;
    getLocalTime(&startOfToday);
    startOfToday.tm_hour = 0;
    startOfToday.tm_min = 0;
    startOfToday.tm_sec = 0;
    time_t startOfTodayUnixTime = mktime(&startOfToday);

    // get Unix time for end of today
    struct tm endOfToday;
    getLocalTime(&endOfToday);
    endOfToday.tm_hour = 23;
    endOfToday.tm_min = 59;
    endOfToday.tm_sec = 59;
    time_t endOfTodayUnixTime = mktime(&endOfToday);

    return time >= startOfTodayUnixTime && time <= endOfTodayUnixTime;
}

/**
 * Gets the highest stage of loadshedding for today.
 *
 * @return The highest stage of loadshedding for today.
 */
int Schedule::getHighestStageOfToday()
{
    int highestStage = 0;

    for (int i = 0; i < this->numberOfEvents; i++)
    {
        time_t eventStart = this->events[i].start;
        int eventStage = this->events[i].stage;

        // check if event starts today
        if (isToday(eventStart))
        {
            // Serial.println("Event starts today.");
            if (eventStage > highestStage)
            {
                highestStage = eventStage;
            }
        }
    }

    return highestStage;
}