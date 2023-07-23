#include <Arduino.h>
#include "oled.h"
#include "connectWiFi.h"

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
  setupWiFi();

  // display stored values
  String apiToken = readString("apiToken");
  String areaName = readString("areaName");
  displayText("API: " + apiToken, 0, 1, true);
  displayText("Area: " + areaName, 30, 1, true, false);
  delay(2000);
}

String dots = "";

void loop()
{
  // display an increasing number of dots
  dots += ".";
  displayText(dots, 0, 1, true);
  delay(500);
}
