#pragma once
#include <Preferences.h>
#include "config_data.h"

class ConfigStorage {
    Preferences preferences;

public:
    void begin();
    void saveConfig(const ConfigData& cfg);
    bool loadConfig(ConfigData& cfg);
    void end();
};
