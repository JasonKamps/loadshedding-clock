#include "storage.h"

Preferences preferences;

void setupStorage()
{
    // preferences
    preferences.begin("loadshedding", false);

    // LittleFS
    if (!LittleFS.begin())
    {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }

    Serial.println("Storage setup complete.");
}

void resetStorage()
{
    Serial.println("Resetting storage...");
    preferences.clear();
    LittleFS.format();
}

String readString(char const *key)
{
    String value = preferences.getString(key, "");
    Serial.println("Read " + String(key) + ": " + value);
    return value;
}

void writeString(char const *key, String value)
{
    preferences.putString(key, value);
    Serial.println("Wrote " + String(key) + ": " + value);
}

time_t readTime(char const *key)
{
    time_t value = preferences.getLong(key, 0);
    Serial.println("Read " + String(key) + ": " + value);
    return value;
}

void writeTime(char const *key, time_t value)
{
    preferences.putLong(key, value);
    Serial.println("Write " + String(key) + ": " + value);
}

/**
 * Writes the upcoming loadshedding events in JSON format to storage with LittleFS.
 * The events are parsed from the entire area information JSON string from the API.
 *
 * @param areaInfoJsonString The entire area information JSON string from the API.
 */
void writeEvents(char *areaInfoJsonString)
{
    DynamicJsonDocument doc(16384);

    DeserializationError error = deserializeJson(doc, areaInfoJsonString);
    if (error)
    {
        Serial.println("Failed to parse JSON");
        Serial.println(error.f_str());
        return;
    }

    // write the events to storage with LittleFS
    File file = LittleFS.open("/events.json", "w");
    if (!file)
    {
        Serial.println("Failed to open file for writing");
        return;
    }

    Serial.println("Writing events to storage.");

    serializeJson(doc["events"], file);

    file.close();
}

/**
 * Reads the upcoming loadshedding events from storage with LittleFS.
 *
 * @return The upcoming loadshedding events in JSON format.
 */
DynamicJsonDocument readEvents()
{
    DynamicJsonDocument doc(8192);

    Serial.println("Reading events from storage.");

    File file = LittleFS.open("/events.json", "r");
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return doc;
    }

    DeserializationError error = deserializeJson(doc, file);
    if (error)
    {
        Serial.println("Failed to parse JSON");
        Serial.println(error.f_str());
        return doc;
    }

    file.close();

    return doc;
}
