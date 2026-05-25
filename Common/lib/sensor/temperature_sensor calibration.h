#pragma once
#include "temperature_sensor.h"
#include <cmath>

struct CalibrationEntry {
    uint32_t uniqueID;
    TemperatureData offset;
};

CalibrationEntry calTable[] = {
    { 3896736704, { 0.15,  9.0,  -0.5, NAN } },
    { 3049729653, { 0.05, -0.1, -0.38, NAN } }
};

const int calCount = sizeof(calTable) / sizeof(calTable[0]);

TemperatureData getCalibration(uint32_t id) {
    for (int i = 0; i < calCount; i++) {
        if (calTable[i].uniqueID == id) {
            return calTable[i].offset;
        }
    }
    return TemperatureData(); // default: minden NAN
}