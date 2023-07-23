#include "storage.h"

Preferences preferences;

void setupStorage()
{
    preferences.begin("loadshedding", false);
    Serial.println("Storage setup complete.");
}

void resetStorage()
{
    Serial.println("Resetting storage...");
    preferences.clear();
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

int32_t readLong(char const *key)
{
    int32_t value = preferences.getLong(key, -1);
    Serial.println("Read " + String(key) + ": " + value);
    return value;
}

void writeLong(char const *key, int32_t value)
{
    preferences.putLong(key, value);
    Serial.println("Write " + String(key) + ": " + value);
}