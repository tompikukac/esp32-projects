#pragma once

enum class SensorType {
  SHT30,
  SHT40,
  BME280,
  Unknown
};

struct SensorTypeHelper {
    static const char* sensorTypeToString(SensorType type) {
        switch(type) {
            case SensorType::SHT30: return "SHT30";
            case SensorType::SHT40: return "SHT40";
            case SensorType::BME280: return "BME280";
            default: return "Unknown";
        }
    }

    static SensorType sensorTypeFromString(const char* str) {
        if (!str) {
            return SensorType::Unknown;
        }
        if (strcmp(str, "SHT30") == 0) return SensorType::SHT30;
        if (strcmp(str, "SHT40") == 0) return SensorType::SHT40;
        if (strcmp(str, "BME280") == 0) return SensorType::BME280;
        return SensorType::Unknown;
    }
};