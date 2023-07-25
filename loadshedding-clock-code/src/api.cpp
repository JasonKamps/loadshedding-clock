#include "api.h"

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
 * Gets and stores the area id & area name from the EskomSePush API.
 * Uses the API token and area name provided by the user (stored in NVM).
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
    Serial.println("URL: " + url);

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
}
