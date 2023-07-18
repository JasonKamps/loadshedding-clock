#include <Arduino.h>
#include "oled.h"

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
  setup_OLED();

  display_text("Hello \nWorld!", 0, 2, true);
  delay(2000);
  display_text("Test", 0);
  delay(2000);
  display_text("This is a long message that will wrap around the screen.", 0, 1, true);
  delay(2000);
}

String dots = "";

void loop()
{
  // display an increasing number of dots
  dots += ".";
  display_text(dots, 0, 1, true);
  delay(500);
}
