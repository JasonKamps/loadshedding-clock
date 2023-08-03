#ifndef DATETIME_H
#define DATETIME_H

#include "Arduino.h"
#include "time.h"
#include "oled.h"

void setupDateTime();
String getCurrentDateTimeString();
time_t getUnixTime();
time_t convertStringToUnixTime(String dateTimeString);

#endif
