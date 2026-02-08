#include "sht40_sensor.h"

SHT40Sensor::SHT40Sensor(TwoWire& wire)
  : wire(wire) {}

bool SHT40Sensor::beginImpl() {
  wire.begin(5, 6);  // SDA=GPIO5, SCL=GPIO6

  if (!sht.begin(&wire)) {
    return false;
  }

  sht.setPrecision(SHT4X_HIGH_PRECISION);
  sht.setHeater(SHT4X_NO_HEATER);

  return true;
}

TemperatureData SHT40Sensor::readImpl() {
  TemperatureData data;  // defaults to NaN

  sensors_event_t temp;
  sensors_event_t humidity;

  if (!sht.getEvent(&humidity, &temp)) {
    // measurement failed → return all-NaN
    return data;
  }

  if (!isnan(temp.temperature)) {
    data.temperature = temp.temperature;
  }

  if (!isnan(humidity.relative_humidity)) {
    data.humidity = humidity.relative_humidity;
  }

  return data;
}
