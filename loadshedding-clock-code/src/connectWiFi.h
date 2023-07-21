#ifndef CONNECTWIFI_H
#define CONNECTWIFI_H

#include "Arduino.h"
#include <FS.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <SPIFFS.h>
#include <ArduinoJson.h> // https://github.com/bblanchon/ArduinoJson
#include "oled.h"

void setupWiFi();
void resetWiFi();
void readConfig();
void writeConfig();

extern char apiToken[];
extern char areaName[];

#endif