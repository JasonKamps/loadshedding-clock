#include <Arduino.h>
#include "oled.h"
#include "connectWiFi.h"
#include "storage.h"
#include "dateTime.h"
#include "api.h"
#include "schedule.h"
#include "ssd.h"
#include "timeline.h"

const int RESET_PIN = 36;
const int API_CALL_INTERVAL = 30; // minutes

Schedule schedule;

time_t lastEventRetrievalTime = 0;

hw_timer_t *ssdTimer = NULL;

// ISR to refresh seven-segment displays
void IRAM_ATTR ssdISR()
{
  refreshSSDs();
}

void setup()
{
  // serial
  Serial.begin(19200);

  while (!Serial)
  {
    // wait for serial port to connect
  }

  Serial.println("Starting up...");

  // OLED
  setupOLED();

  // timeline
  setupTimeline();
  sweepTimelineLEDs();

  // seven-segment display refresh timer (500 Hz)
  ssdTimer = timerBegin(0, 80, true); // 80 prescaler gives 1 MHz
  timerAttachInterrupt(ssdTimer, &ssdISR, true);
  timerAlarmWrite(ssdTimer, 2000, true); // 2000 microseconds gives 500 Hz
  timerAlarmEnable(ssdTimer);

  // test seven-segment displays
  testSSDs();

  // storage
  setupStorage();

  // reset button
  pinMode(RESET_PIN, INPUT_PULLUP);
  if (digitalRead(RESET_PIN) == LOW)
  {
    // short press
    displayText("Resetting WiFi...");
    delay(5000);
    resetWiFi();

    if (digitalRead(RESET_PIN) == LOW)
    {
      // long press
      displayText("Resetting storage...", 10, false);
      delay(5000);
      resetStorage();
    }
  }

  // WiFi
  boolean customParamsSaved = setupWiFi();

  // display user info from storage
  displayText("API: " + readString("apiToken"), 0, 1, true);
  displayText("User area: " + readString("userAreaName"), 30, 1, true, false);
  delay(2000);

  // date and time
  setupDateTime();

  // API
  if (customParamsSaved)
  {
    // only retrieve area if custom parameters were saved (don't want to waste API calls)
    retrieveArea();
  }

  // retrieve events if sufficient time has passed since last retrieval
  lastEventRetrievalTime = readTime("lastRetrieval");
  if (getUnixTime() - lastEventRetrievalTime > (API_CALL_INTERVAL * 60))
  {
    Serial.println("Retrieving events. It has been more than " + String(API_CALL_INTERVAL) + " minutes since last retrieval.");
    retrieveEvents();
    time_t now = getUnixTime();
    writeTime("lastRetrieval", now);
    lastEventRetrievalTime = now;
  }
  else
  {
    Serial.println("Not retrieving events. It has only been " + String((getUnixTime() - lastEventRetrievalTime) / 60.0) + " minutes since last retrieval.");
  }

  // schedule
  schedule.update();

  // read and print events
  DynamicJsonDocument doc = readEvents();
  serializeJsonPretty(doc, Serial);
  Serial.println();

  // display area info from storage
  displayText("Area: " + readString("areaName"), 0, 1, true);
  displayText("Area ID: " + readString("areaId"), 30, 1, true, false);
  delay(2000);

  clearDisplay();
}

void loop()
{
  // display "ends" on OLED if currently loadshedding, "begins" if not yet loadshedding
  if (schedule.isCurrentlyLoadshedding())
  {
    displayText("ends", 15, 3);
  }
  else
  {
    displayText("begins", 15, 3);
  }

  // update values to display on seven-segment displays
  int secondsUntilNextTransition = schedule.getSecondsUntilNextTransition();
  int highestStage = schedule.getHighestUpcomingStage();
  updateSSDs(secondsUntilNextTransition, highestStage);

  // update timeline
  updateTimeline(schedule);

  delay(1000);
}
