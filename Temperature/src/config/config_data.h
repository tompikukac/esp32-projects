#pragma once
#include <ArduinoJson.h>

class ConfigData {
public:
    String name;
    unsigned long deepSleepTimeInSec;

    ConfigData();

    bool parse(const String& jsonStr);
    String toString() const;
};
