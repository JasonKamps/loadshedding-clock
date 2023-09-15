#include <Arduino.h>
#include "oled.h"
#include "connectWiFi.h"
#include "storage.h"
#include "dateTime.h"
#include "api.h"
#include "schedule.h"
#include "ssd.h"

const int RESET_PIN = 36;
const int API_CALL_INTERVAL = 30; // minutes

Schedule schedule;

time_t lastEventRetrievalTime = 0;

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

  // seven-segment display
  setupSSD();

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

int ssdCount = 0;
int ssdDigit = 0;

void loop()
{
  // display countdown to next transition
  int secondsUntilNextTransition = schedule.getSecondsUntilNextTransition();
  if (secondsUntilNextTransition > 0)
  {
    int hoursUntilNextEvent = secondsUntilNextTransition / 3600;
    int minutesUntilNextEvent = (secondsUntilNextTransition % 3600) / 60;
    if (schedule.isCurrentlyLoadshedding())
    {
      displayText("Loadshedding", 0, 1, true, false);
      displayText("ends in", 10, false);
    }
    else
    {
      displayText("Loadshedding", 0, 1, true, false);
      displayText("starts in", 10, false);
    }
    displayText(String(hoursUntilNextEvent) + "h " + String(minutesUntilNextEvent) + "m", 20, false);
  }
  else
  {
    displayText("No loadshedding expected today!", 0, 1, true, false);
  }

  // display the highest current/upcoming loadshedding stage
  int highestStage = schedule.getHighestUpcomingStage();
  displayText("Stage: " + String(highestStage), 40, false);

  // retrieve events from API if sufficient time has passed since last retrieval
  if (getUnixTime() - lastEventRetrievalTime > (API_CALL_INTERVAL * 60))
  {
    Serial.println("Retrieving events. It has been more than " + String(API_CALL_INTERVAL) + " minutes since last retrieval.");
    retrieveEvents();
    time_t now = getUnixTime();
    writeTime("lastRetrieval", now);
    lastEventRetrievalTime = now;
    schedule.update();
  }

  // update seven-segment display
  displayNumber(ssdCount++ % 10, ssdDigit++ % 4);

  delay(1000);
}
