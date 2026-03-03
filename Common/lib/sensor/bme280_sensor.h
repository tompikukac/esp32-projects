#pragma once
#include <Wire.h>
#include <Adafruit_BME280.h>
#include "temperature_sensor.h"  // include header, not .cpp

class BME280Sensor : public TemperatureSensor {
public:
  explicit BME280Sensor(TwoWire& wire);

protected:
  bool beginImpl() override;
  TemperatureData readImpl() override;

private:
  TwoWire& wire;
  Adafruit_BME280 bme;
};
