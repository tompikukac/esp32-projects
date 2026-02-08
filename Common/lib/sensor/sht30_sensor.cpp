#include "sht30_sensor.h"

SHT30Sensor::SHT30Sensor(TwoWire& wire, uint8_t address)
  : wire(wire), address(address) {}

bool SHT30Sensor::beginImpl() {
  wire.begin(5, 6);  // SDA=GPIO5, SCL=GPIO6

  if (!sht.begin(address)) {
    return false;
  }

  return true;
}

TemperatureData SHT30Sensor::readImpl() {
  TemperatureData data;

  float t = sht.readTemperature();
  float h = sht.readHumidity();

  if (!isnan(t)) {
    data.temperature = t;
  }
  if (!isnan(h)) {
    data.humidity = h;
  }

  return data;
}
