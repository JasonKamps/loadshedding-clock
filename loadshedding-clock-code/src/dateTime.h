#ifndef DATETIME_H
#define DATETIME_H

#include "Arduino.h"
#include "time.h"
#include "oled.h"

void setupDateTime();
String getDateTimeString();
int32_t getDateTimeEpoch();

#endif
