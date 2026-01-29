#include "config_data.h"

ConfigData::ConfigData()
    : name("default-device"), deepSleepTimeInSec(599) {}

bool ConfigData::parse(const String& jsonStr) {
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, jsonStr);
    if (error) {
        return false;
    }

    if (doc.containsKey("name")) {
        name = String(doc["name"].as<const char*>());
    }

    if (doc.containsKey("deepSleepTimeInSec")) {
        deepSleepTimeInSec = doc["deepSleepTimeInSec"].as<unsigned long>();
    }
    return true;
}

String ConfigData::toString() const {
    return "name: " + name + ", deepSleepTimeInSec: " + String(deepSleepTimeInSec);
}
