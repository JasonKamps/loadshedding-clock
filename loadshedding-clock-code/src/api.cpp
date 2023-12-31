#include "api.h"

const int API_DAILY_ALLOWANCE = 50;

/**
 * Encodes a string to be used in a URL.
 *
 * @param str The raw string to encode.
 * @return The encoded string with special characters replaced.
 */
String urlEncode(String str)
{
    String encodedString = "";

    char c;
    char code0;
    char code1;

    for (unsigned int i = 0; i < str.length(); i++)
    {
        c = str.charAt(i);

        if (c == ' ')
        {
            encodedString += '+';
        }
        else if (isalnum(c))
        {
            encodedString += c;
        }
        else
        {
            code1 = (c & 0xf) + '0';
            if ((c & 0xf) > 9)
            {
                code1 = (c & 0xf) - 10 + 'A';
            }
            c = (c >> 4) & 0xf;
            code0 = c + '0';
            if (c > 9)
            {
                code0 = c - 10 + 'A';
            }
            encodedString += '%';
            encodedString += code0;
            encodedString += code1;
        }
        yield();
    }
    return encodedString;
}

/**
 * Gets and stores (in NVM with preferences) the area id & area name from the EskomSePush API.
 * Uses the API token and area name provided by the user (stored in NVM with preferences).
 */
void retrieveArea()
{
    Serial.println("Getting area");

    String apiToken = readString("apiToken");
    String userAreaName = readString("userAreaName");

    if (apiToken.length() == 0 || userAreaName.length() == 0)
    {
        Serial.println("API token or user area name not set");
        return;
    }

    String url = "https://developer.sepush.co.za/business/2.0/areas_search?text=" + urlEncode(userAreaName);

    // API get request
    HTTPClient http;
    http.begin(url);
    http.addHeader("token", apiToken);

    int httpResponseCode = http.GET();
    if (httpResponseCode == HTTP_CODE_OK)
    {
        String payload = http.getString();
        Serial.println(payload);

        // parse the JSON response
        StaticJsonDocument<2048> doc;
        DeserializationError error = deserializeJson(doc, payload);

        if (!error)
        {
            // get the ID of the first area
            String areaId = doc["areas"][0]["id"];
            Serial.println("Area ID: " + areaId);

            // get the name of the first area
            String areaName = doc["areas"][0]["name"];
            Serial.println("Area name: " + areaName);

            // store the area ID and name
            writeString("areaId", areaId);
            writeString("areaName", areaName);
        }
        else
        {
            Serial.println("Failed to parse JSON response.");
        }
    }
    else
    {
        Serial.print("Error in HTTP request. HTTP response code: ");
        Serial.println(httpResponseCode);
    }

    http.end();

    Serial.println("API allowance usage: " + String(getAllowanceUsage()) + "/" + String(API_DAILY_ALLOWANCE));
}

/**
 * Gets and stores (in FS with LittleFS) the upcoming loadshedding events from the EskomSePush API.
 * Uses the area id provided by the user (stored in NVM with preferences).
 */
void retrieveEvents()
{
    Serial.println("Getting events");

    String apiToken = readString("apiToken");
    String areaId = readString("areaId");

    if (apiToken.length() == 0 || areaId.length() == 0)
    {
        Serial.println("API token or area ID not set");
        return;
    }

    // testing urls (don't count towards API quota)
    // String url = "https://developer.sepush.co.za/business/2.0/area?id=" + urlEncode(areaId) + "&test=future";
    // String url = "https://developer.sepush.co.za/business/2.0/area?id=" + urlEncode(areaId) + "&test=current";

    String url = "https://developer.sepush.co.za/business/2.0/area?id=" + urlEncode(areaId);

    // API get request
    HTTPClient http;
    http.begin(url);
    http.addHeader("token", apiToken);

    int httpResponseCode = http.GET();
    if (httpResponseCode == HTTP_CODE_OK)
    {
        String payload = http.getString();
        Serial.println(payload);

        // store the events
        char payloadChar[payload.length() + 1];
        strcpy(payloadChar, payload.c_str());
        writeEvents(payloadChar);
    }
    else
    {
        Serial.print("Error in HTTP request. HTTP response code: ");
        Serial.println(httpResponseCode);
    }
    http.end();

    Serial.println("API allowance usage: " + String(getAllowanceUsage()) + "/" + String(API_DAILY_ALLOWANCE));
}

/**
 * Gets the number of API calls made today.
 * 
 * @return The number of API calls made today.
 */
int getAllowanceUsage()
{
    Serial.println("Getting allowance usage");
    
    int allowance_count = -1;

    String apiToken = readString("apiToken");

    if (apiToken.length() == 0)
    {
        Serial.println("API token not set");
        return -1;
    }

    String url = "https://developer.sepush.co.za/business/2.0/api_allowance";

    // API get request
    HTTPClient http;
    http.begin(url);
    http.addHeader("token", apiToken);

    int httpResponseCode = http.GET();
    if (httpResponseCode == HTTP_CODE_OK)
    {
        String payload = http.getString();

        // parse the JSON response
        StaticJsonDocument<128> doc;
        DeserializationError error = deserializeJson(doc, payload);

        if (!error)
        {
            allowance_count = doc["allowance"]["count"];
        }
        else
        {
            Serial.println("Failed to parse JSON response.");
        }
    }
    else
    {
        Serial.print("Error in HTTP request. HTTP response code: ");
        Serial.println(httpResponseCode);
    }
    http.end();

    return allowance_count;
}