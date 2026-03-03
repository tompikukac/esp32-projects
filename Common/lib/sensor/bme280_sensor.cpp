#include "bme280_sensor.h"

BME280Sensor::BME280Sensor(TwoWire& wire)
  : wire(wire) {}

bool BME280Sensor::beginImpl() {
  wire.begin(5, 6);  // SDA=GPIO5, SCL=GPIO6

 

  return true;
}

TemperatureData BME280Sensor::readImpl() {
  Serial.print("BME280Sensor: ");
 
  TemperatureData data;


  data.temperature = bme.readTemperature();
  data.humidity    = bme.readHumidity();
  // data.pressure    = bme.readPressure() / 100.0F; // hPa
  float seaLevel = bme.readPressure() / pow(1.0 - (100 / 44330.0), 5.255);
  data.pressure    = seaLevel / 100.0F; // hPa


  return data;
}
