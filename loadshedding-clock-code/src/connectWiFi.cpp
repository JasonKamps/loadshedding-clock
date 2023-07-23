#include "connectWiFi.h"

const char wifiName[] = "Eishkom";

const int API_TOKEN_LENGTH = 50;
const int AREA_NAME_LENGTH = 50;

bool shouldSaveConfig = false;

WiFiManager wifiManager;

void configModeCallback(WiFiManager *myWiFiManager)
{
    Serial.println("\nEntered config mode");
    Serial.println(WiFi.softAPIP());
    Serial.println(myWiFiManager->getConfigPortalSSID());

    displayText("Connect to WiFi:");
    displayText("\"" + String(wifiName) + "\"", 10, false);
    displayText("Then go to", 35, false);
    displayText(WiFi.softAPIP().toString(), 45, false);
    displayText("for configuration.", 55, false);
}

void saveConfigCallback()
{
    Serial.println("Should save config");
    shouldSaveConfig = true;
}

void setupWiFi()
{
    // get API token and area name from storage
    char apiToken[API_TOKEN_LENGTH];
    char areaName[AREA_NAME_LENGTH];
    strcpy(apiToken, readString("apiToken").c_str());
    strcpy(areaName, readString("areaName").c_str());

    Serial.println("\nConnecting to WiFi..");
    displayText("Connecting to WiFi...");

    // paramters for WiFiManager configuration page
    WiFiManagerParameter customApiToken("apiToken", "Your EskomSePush API token", apiToken, API_TOKEN_LENGTH);
    WiFiManagerParameter customAreaName("areaName", "Your area name as in the EskomSePush app", areaName, AREA_NAME_LENGTH);

    // initailise WiFiManager
    wifiManager.setAPCallback(configModeCallback);
    wifiManager.setSaveConfigCallback(saveConfigCallback);
    wifiManager.setDebugOutput(false);

    // setup parameters
    wifiManager.addParameter(&customApiToken);
    wifiManager.addParameter(&customAreaName);

    // setup AP
    wifiManager.autoConnect(wifiName);

    Serial.println("WiFi connected!");
    displayText("WiFi connected!");

    // read updated parameters
    strcpy(apiToken, customApiToken.getValue());
    strcpy(areaName, customAreaName.getValue());

    // save the custom parameters to storage
    if (shouldSaveConfig)
    {
        writeString("apiToken", String(apiToken));
        writeString("areaName", String(areaName));
    }
}

void resetWiFi()
{
    Serial.println("Resetting WiFi...");
    wifiManager.resetSettings();
}