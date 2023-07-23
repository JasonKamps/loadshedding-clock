#include "dateTime.h"

const char *ntpServer = "pool.ntp.org";
const long gmtOffset = 2 * 60 * 60; // seconds. South Africa is GMT+2
const int daylightOffset = 0;       // seconds

void setupDateTime()
{
    Serial.println("Retrieving time");
    displayText("Retrieving time...");
    configTime(gmtOffset, daylightOffset, ntpServer);

    Serial.println("Time retrieved. It is now: ");
    Serial.println(getDateTimeString());
}

String getDateTimeString()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return "";
    }

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%A, %d %B %Y %H:%M:%S", &timeinfo);
    return String(buffer);
}