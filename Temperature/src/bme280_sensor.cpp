#include "bme280_sensor.h"

BME280Sensor::BME280Sensor(uint8_t sda_pin, uint8_t scl_pin, uint8_t i2c_addr)
  : _sda(sda_pin), _scl(scl_pin), _addr(i2c_addr) {}

bool BME280Sensor::begin() {
  Wire.begin(_sda, _scl);
  return _bme.begin(_addr);
}

BME280Data BME280Sensor::read() {
  BME280Data data;
  data.temperature = _bme.readTemperature();
  data.humidity    = _bme.readHumidity();
  data.pressure    = _bme.readPressure() / 100.0F; // hPa
  return data;
}
