#include "config_storage.h"
#include "config_data.h"
#include "sensor/sensor_type.h"

void ConfigStorage::begin() {
    preferences.begin("config", false);
}

void ConfigStorage::saveConfig(const ConfigData& cfg) {
    preferences.putString("name", cfg.name);
    preferences.putULong("sleepInSec", cfg.deepSleepTimeInSec);
    preferences.putString("ip", cfg.ip.toString());
    preferences.putString("sensorType", SensorTypeHelper::sensorTypeToString(cfg.sensorType));
    preferences.putBool("oled", cfg.oled);
}

ConfigData* ConfigStorage::loadConfig() {
    if (!preferences.isKey("name")) {
        return nullptr;
    }
    String name = preferences.getString("name", "default-device");
    if (name == "default-device") {
        return nullptr;
    }

    ConfigData* cfg = new ConfigData();
    cfg->name = name;
    cfg->deepSleepTimeInSec =  preferences.getULong("sleepInSec", cfg->deepSleepTimeInSec);

    String ipStr = preferences.getString("ip", "");
    if (ipStr.length() > 0) {
        cfg->ip.fromString(ipStr);
    } else {
        cfg->ip = IPAddress(0,0,0,0);
    }

    // SensorType
    String sensorTypeStr = preferences.getString("sensorType", "");
    cfg->sensorType = SensorTypeHelper::sensorTypeFromString(sensorTypeStr.c_str());

    // OLED
    cfg->oled = preferences.getBool("oled", false);

    return cfg;
}

void ConfigStorage::end() {
    preferences.end();
}
