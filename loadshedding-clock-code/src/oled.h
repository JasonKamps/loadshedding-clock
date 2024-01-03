#ifndef OLED_H
#define OLED_H

#include "Arduino.h"

void setupOLED();
void displayText(String text, int yLoc, bool overwriteDisplay);
void displayText(String text, int yLoc = 0, int textSize = 1, bool wrap = false, bool overwriteDisplay = true);
void clearDisplay();
void displayBegins();
void displayEnds();

#endif