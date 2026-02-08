#include "sensor_factory.h"
#include "logger.h"

TemperatureSensor* createSensor(SensorType type, TwoWire& wire) {
  switch (type) {
    case SensorType::SHT30:
      logger.println("Creating SHT30 sensor...");
      return new SHT30Sensor(wire);
    case SensorType::SHT40:
      logger.println("Creating SHT40 sensor...");
      return new SHT40Sensor(wire);
    default:
      logger.println("Unsupported sensor type!");
      return nullptr;
  }
}
