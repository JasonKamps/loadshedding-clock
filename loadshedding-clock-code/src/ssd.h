#ifndef SSD_H
#define SSD_H

#include "Arduino.h"

void clearSSDs();
void testSSDs();
void displayOnSSD(int digit, int value);
void updateSSDs(int secondsUntilNextTransition, int stage);
void refreshSSDs();

#endif