#include "temperature_sensor.cpp"
#include "sht30_sensor.cpp"
#include "sht40_sensor.cpp"

enum class SensorType {
  SHT30,
  SHT40
};

TemperatureSensor* createSensor(SensorType type) {
  switch (type) {
    case SensorType::SHT30:
      return new SHT30Sensor();
    case SensorType::SHT40:
      return new SHT40Sensor();
    default:
      return nullptr;
  }
}
