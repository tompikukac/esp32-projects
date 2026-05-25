#include "bme280_sensor.h"
#include "temperature_sensor calibration.h"

BME280Sensor::BME280Sensor(TwoWire& wire)
  : wire(wire) {}


uint8_t readRegister(uint8_t reg) {
    Wire.beginTransmission(0x76);   // vagy 0x77
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(0x76, 1);
    return Wire.read();
}

uint32_t getUniqueID() {
    uint32_t hash = 2166136261UL;

    for (int i = 0; i < 26; i++) {
        uint8_t v = readRegister(0x88 + i);
        hash ^= v;
        hash *= 16777619UL;
    }

    return hash;
}

bool BME280Sensor::beginImpl() {
  wire.begin(5, 6);  // SDA=GPIO5, SCL=GPIO6
  if (!bme.begin(0x76, &wire)) {  // change to 0x77 if needed
    return false;
  }
  bme.setSampling(
    Adafruit_BME280::MODE_NORMAL,
    Adafruit_BME280::SAMPLING_X8,   // temperature
    Adafruit_BME280::SAMPLING_X8,   // pressure
    Adafruit_BME280::SAMPLING_X8,   // humidity
    Adafruit_BME280::FILTER_X4,
    Adafruit_BME280::STANDBY_MS_125
  );

  uint32_t id = getUniqueID();
  TemperatureData off = getCalibration(id);
  setOffsets(off);

  return true;
}

TemperatureData BME280Sensor::readImpl() {
  
  TemperatureData data;

  float t = bme.readTemperature();
  if (!isnan(t)) {
    data.temperature = t;
  }

  float h = bme.readHumidity();
  if (!isnan(h)) {
    data.humidity = h;
  }

  float p = bme.readPressure();
  if (!isnan(p)) {
    data.pressure = (p / pow(1.0 - (100 / 44330.0), 5.255)) / 100.0; // sea level (100m)
  }

  return data;
}
