#ifndef CONNECTWIFI_H
#define CONNECTWIFI_H

#include "Arduino.h"
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include "oled.h"
#include "storage.h"

void setupWiFi();
void resetWiFi();

#endif