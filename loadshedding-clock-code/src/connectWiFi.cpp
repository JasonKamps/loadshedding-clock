#include "connectWiFi.h"

WiFiManager wifiManager;

char wifiName[] = "Eishkom";

void configModeCallback(WiFiManager *myWiFiManager)
{
    Serial.println("\nEntered config mode");
    Serial.println(WiFi.softAPIP());
    Serial.println(myWiFiManager->getConfigPortalSSID());

    displayText("Please connect to", 0);
    displayText("\"" + String(wifiName) + "\"", 10, 1, false, false);
    displayText("to setup WiFi.", 20, 1, false, false);
}

void setupWiFi()
{
    Serial.println("\nConnecting to WiFi..");
    displayText("Connecting to WiFi...");

    // initailise WiFiManager
    wifiManager.setAPCallback(configModeCallback);
    wifiManager.setDebugOutput(false);

    // setup AP
    wifiManager.autoConnect(wifiName);

    Serial.println("WiFi connected!");
    displayText("WiFi Connected!");
    delay(1000);
}

void resetWiFi()
{
    Serial.println("Resetting WiFi...");

    wifiManager.resetSettings();

    Serial.println("WiFi has been reset.");
}
