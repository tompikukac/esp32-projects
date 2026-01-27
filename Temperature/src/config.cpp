#include <ArduinoJson.h>

class Config {
public:
    String name;
    unsigned long deepSleepTimeInSec = 600; 

    Config() : name("default-device") {}  // default érték

    bool parse(const String& jsonStr) {
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, jsonStr);
        if (error) {
            return false;
        }

        if (doc.containsKey("name")) {
            name = String(doc["name"].as<const char*>());
        }
        
        if (doc.containsKey("deepSleepTime")) {
            deepSleepTimeInSec = doc["deepSleepTime"].as<unsigned long>();
        }
        return true;
    }
};
