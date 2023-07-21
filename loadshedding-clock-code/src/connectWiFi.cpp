#include "connectWiFi.h"

char wifiName[] = "Eishkom";

char apiToken[35] = "API_TOKEN_GOES_HERE"; // API token will be set during WiFi cofiguration via WiFiManager
char areaName[50] = "AREA_NAME_GOES_HERE"; // Area name will be set during WiFi cofiguration via WiFiManager

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
    // read configuration from FS json
    Serial.println("Configuring file system...");
    displayText("Configuring file");
    displayText("system...", 10, false);

    readConfig();

    Serial.println("\nConnecting to WiFi..");
    displayText("Connecting to WiFi...");

    // paramters for WiFiManager configuration page
    WiFiManagerParameter customApiToken("apiToken", "Your EskomSePush API token", apiToken, 35);
    WiFiManagerParameter customAreaName("areaName", "Your area name as in the EskomSePush app", areaName, 50);

    // initailise WiFiManager
    wifiManager.setAPCallback(configModeCallback);
    wifiManager.setSaveConfigCallback(saveConfigCallback);

    // setup parameters
    wifiManager.addParameter(&customApiToken);
    wifiManager.addParameter(&customAreaName);

    // setup AP
    wifiManager.autoConnect(wifiName);

    Serial.println("WiFi connected!");
    displayText("WiFi Connected!");

    // read updated parameters
    strcpy(apiToken, customApiToken.getValue());
    strcpy(areaName, customAreaName.getValue());
    Serial.println("API Token: " + String(apiToken));
    Serial.println("Area Name: " + String(areaName));

    // save the custom parameters to FS
    if (shouldSaveConfig)
        writeConfig();

        delay(1000);
    }

    void resetWiFi()
    {
        Serial.println("Resetting WiFi...");

        wifiManager.resetSettings();

        Serial.println("WiFi has been reset.");
    }

    void readConfig()
    {
        // clean FS, for testing
        // SPIFFS.format();

        // read configuration from FS json
        Serial.println("mounting FS...");

        if (SPIFFS.begin(true))
        {
            Serial.println("mounted file system");
            if (SPIFFS.exists("/config.json"))
            {
                // file exists, reading and loading
                Serial.println("reading config file");
                File configFile = SPIFFS.open("/config.json", "r");
                if (configFile)
                {
                    Serial.println("opened config file");
                    size_t size = configFile.size();
                    // allocate a buffer to store contents of the file.
                    std::unique_ptr<char[]> buf(new char[size]);

                    configFile.readBytes(buf.get(), size);

                    DynamicJsonDocument json(1024);
                    auto deserializeError = deserializeJson(json, buf.get());
                    serializeJson(json, Serial);
                    if (!deserializeError)
                    {
                        Serial.println("\nparsed json");
                        strcpy(apiToken, json["apiToken"]);
                        strcpy(areaName, json["areaName"]);
                    }
                    else
                    {
                        Serial.println("failed to load json config");
                    }
                    configFile.close();
                }
            }
        }
        else
        {
            Serial.println("failed to mount FS");
        }
    }

    void writeConfig()
    {
        Serial.println("saving config");
        DynamicJsonDocument json(1024);
        json["apiToken"] = apiToken;
        json["areaName"] = areaName;

        File configFile = SPIFFS.open("/config.json", "w");
        if (!configFile)
        {
            Serial.println("failed to open config file for writing");
        }

        serializeJson(json, Serial);
        serializeJson(json, configFile);
        configFile.close();
    }
