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
    Serial.println(getCurrentDateTimeString());
}

String getCurrentDateTimeString()
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

time_t getUnixTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return 0;
    }

    return mktime(&timeinfo);
}

/**
 * Converts a date/time string to Unix time.
 * 
 * @param dateTimeString The date/time string to convert. Must be in the format "YYYY-MM-DDTHH:MM:SS+HH:MM". Eg: "2023-07-27T00:30:00+02:00".
 * @return The Unix time.
 */
time_t convertStringToUnixTime(String dateTimeString)
{
    // parse string
    int year = dateTimeString.substring(0, 4).toInt();
    int month = dateTimeString.substring(5, 7).toInt();
    int day = dateTimeString.substring(8, 10).toInt();
    int hour = dateTimeString.substring(11, 13).toInt();
    int minute = dateTimeString.substring(14, 16).toInt();
    int second = dateTimeString.substring(17, 19).toInt();

    // convert to Unix time
    struct tm timeinfo;
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = hour;
    timeinfo.tm_min = minute;
    timeinfo.tm_sec = second;
    time_t unixTime = mktime(&timeinfo);

    return unixTime;
}

