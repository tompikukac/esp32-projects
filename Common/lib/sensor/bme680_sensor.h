#pragma once
#include <Wire.h>
#include <Adafruit_BME680.h>
#include "temperature_sensor.h"  // include header, not .cpp

class BME680Sensor : public TemperatureSensor {
public:
  explicit BME680Sensor(TwoWire& wire);

protected:
  bool beginImpl() override;
  TemperatureData readImpl() override;

private:
  TwoWire& wire;
  Adafruit_BME680 bme;
};
