#include <Arduino.h>
#include "oled.h"
#include "connectWiFi.h"
#include "storage.h"
#include "dateTime.h"
#include "api.h"
#include "schedule.h"
#include "ssd.h"
#include "timeline.h"
#include "Led.h"

const int RESET_PIN = 36;
const int API_CALL_INTERVAL = 30; // minutes

// Input voltage measurement
const int VIN_MEASURE_PIN = 35;
const float BATTERY_VOLTAGE_THRESHOLD = 3.5; // volts

Adafruit_MCP23X17 mcp;

LED wifiLED(2, 1, 0);
LED pwrLED(5, 4, 3);
LED signLEDs(8, 10, 14);

Schedule schedule;


time_t lastEventRetrievalTime = 0;

hw_timer_t *ssdTimer = NULL;

float getInputVoltage()
{
  return analogRead(VIN_MEASURE_PIN) / 4095.0 * 3.3 * 2; // 2x voltage divider
}

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

  // VIN measurement
  pinMode(VIN_MEASURE_PIN, INPUT);
  Serial.println("VIN voltage: " + String(getInputVoltage()) + " V");

  // status LEDs
  wifiLED.setup();
  pwrLED.setup();
  signLEDs.setup();

  // test LEDs
  wifiLED.turnBlue();
  pwrLED.turnBlue();
  delay(200);
  wifiLED.turnGreen();
  pwrLED.turnGreen();
  signLEDs.turnGreen();
  delay(200);
  wifiLED.turnRed();
  pwrLED.turnRed();
  signLEDs.turnRed();
  delay(200);
  pwrLED.turnOff();
  signLEDs.turnOff();

  // display power source
  getInputVoltage() > BATTERY_VOLTAGE_THRESHOLD ? pwrLED.turnGreen() : pwrLED.turnRed();

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
  isWiFiConnected() ? wifiLED.turnGreen() : wifiLED.turnRed();

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
  schedule.isCurrentlyLoadshedding() ? signLEDs.turnRed() : signLEDs.turnGreen();

  // read and print events
  DynamicJsonDocument doc = readEvents();
  serializeJsonPretty(doc, Serial);
  Serial.println();

  // display area info from storage
  displayText("Area: " + readString("areaName"), 0, 1, true);
  displayText("Area ID: " + readString("areaId"), 30, 1, true, false);
  delay(2000);

  // display VIN voltage
  clearDisplay();
  displayText("VIN: " + String(getInputVoltage()) + " V", 0, 1, true, false);
  delay(1000);

  clearDisplay();
}

void loop()
{
  // update values to display on seven-segment displays
  int secondsUntilNextTransition = schedule.getSecondsUntilNextTransition();
  // Serial.println(secondsUntilNextTransition);
  int highestStage = schedule.getHighestUpcomingStage();
  updateSSDs(secondsUntilNextTransition, highestStage);

  if (secondsUntilNextTransition >= 0)
  {
    // display "ends" on OLED if currently loadshedding, "begins" if not yet loadshedding
    schedule.isCurrentlyLoadshedding() ? displayEnds() : displayBegins();
  }
  else
  {
    // no upciming events, display "suspended" on OLED
    displayText("suspended", 20, 2);
  }

  // update timeline
  updateTimeline(schedule);
  flashCurrentTimelineLED();

  // update LEDs
  schedule.isCurrentlyLoadshedding() ? signLEDs.turnRed() : signLEDs.turnGreen();
  isWiFiConnected() ? wifiLED.turnGreen() : wifiLED.turnRed();
  getInputVoltage() > BATTERY_VOLTAGE_THRESHOLD ? pwrLED.turnGreen() : pwrLED.turnRed();

  delay(1000);
}
