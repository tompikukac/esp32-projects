#include "config_storage.h"

void ConfigStorage::begin() {
    preferences.begin("config", false);
}

void ConfigStorage::saveConfig(const ConfigData& cfg) {
    preferences.putString("name", cfg.name);
    preferences.putULong("sleepInSec", cfg.deepSleepTimeInSec);
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

    return cfg;
}

void ConfigStorage::end() {
    preferences.end();
}
