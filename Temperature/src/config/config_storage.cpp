#include "config_storage.h"

void ConfigStorage::begin() {
    preferences.begin("config", false);
}

void ConfigStorage::saveConfig(const ConfigData& cfg) {
    preferences.putString("name", cfg.name);
    preferences.putULong("sleepInSec", cfg.deepSleepTimeInSec);
}

bool ConfigStorage::loadConfig(ConfigData& cfg) {
    if (!preferences.isKey("name")) {
        return false; // no saved config
    }
    String name = preferences.getString("name", cfg.name);
    if (name == "default-device") {
        return false; // default config, treat as no saved config
    }
    cfg.name = name;
    cfg.deepSleepTimeInSec = preferences.getULong("sleepInSec", cfg.deepSleepTimeInSec);
    return true;
}

void ConfigStorage::end() {
    preferences.end();
}
