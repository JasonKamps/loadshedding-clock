#include <Arduino.h>
#include "oled.h"
#include "connectWiFi.h"
#include "storage.h"
#include "dateTime.h"
#include "api.h"

const int RESET_PIN = 36;

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

  // display area info from storage
  displayText("Area: " + readString("areaName"), 0, 1, true);
  displayText("Area ID: " + readString("areaId"), 30, 1, true, false);
  delay(2000);

  clearDisplay();
}

String dots = "";

void loop()
{
  // display an increasing number of dots
  dots += ".";
  displayText(dots, 0, 1, true, false);

  // display date and time
  displayText(getDateTimeString(), 30, 1, true, false);

  delay(500);
}
