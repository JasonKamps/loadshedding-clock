#ifndef STORAGE_H
#define STORAGE_H

#include "Arduino.h"
#include "LittleFS.h"
#include <ArduinoJson.h>
#include <Preferences.h>
#include "dateTime.h"

void setupStorage();
void resetStorage();
String readString(char const *key);
void writeString(char const *key, String value);
time_t readTime(char const *key);
void writeTime(char const *key, time_t value);
void writeEvents(char* areaInfoJsonString);
DynamicJsonDocument readEvents();

#endif