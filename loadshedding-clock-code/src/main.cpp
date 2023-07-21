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

  // reset button
  pinMode(RESET_PIN, INPUT_PULLUP);
  if (digitalRead(RESET_PIN) == LOW)
  {
    displayText("Reset button pressed.");
    delay(1000);
    resetWiFi();
  }

  // WiFi
  setupWiFi();

  // display details
  readConfig();
  Serial.println("API Token:" + String(apiToken));
  Serial.println("Area Name: " + String(areaName));
  displayText("API: " + String(apiToken), 0, 1, true);
  displayText("Area: " + String(areaName), 30, 1, true, false);
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
