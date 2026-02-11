#include "config_data.h"
#include "sensor/sensor_type.h"

ConfigData::ConfigData()
    : name("default-device"), deepSleepTimeInSec(599), ip(0, 0, 0, 0), sensorType(SensorType::SHT40), oled(false) {}

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

    if (doc.containsKey("ip")) {
        ip.fromString(doc["ip"].as<const char*>());
    }

    if (doc.containsKey("sensorType")) {
        const char* s = doc["sensorType"].as<const char*>();
        sensorType = SensorTypeHelper::sensorTypeFromString(s);
    }

    if (doc.containsKey("Oled")) {
        oled = doc["Oled"].as<bool>();
    }

    return true;
}

String ConfigData::toString() const {
    return "name: " + name + 
    ", deepSleepTimeInSec: " + String(deepSleepTimeInSec) + 
    ", ip: " + ip.toString()+ 
    ", sensorType: " + SensorTypeHelper::sensorTypeToString(sensorType)+ 
    ", Oled: " + String(oled ? "true" : "false");
}

bool ConfigData::hasStaticIP() const {
    return ip != IPAddress(0,0,0,0);
}
