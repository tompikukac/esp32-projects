#pragma once
#include <ArduinoJson.h>
#include <IPAddress.h>
#include "sensor/sensor_type.h"

class ConfigData {
public:
    String name;
    unsigned long deepSleepTimeInSec;
    IPAddress ip;
    SensorType sensorType = SensorType::Unknown;
    bool oled;

    ConfigData();

    bool parse(const String& jsonStr);
    String toString() const;
    bool hasStaticIP() const;
};
