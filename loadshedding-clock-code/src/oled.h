#ifndef OLED_H
#define OLED_H

#include "Arduino.h"

void setup_OLED();
void display_text(String text, int y_loc, int text_size = 1, bool wrap = false);
void clear_display();

#endif