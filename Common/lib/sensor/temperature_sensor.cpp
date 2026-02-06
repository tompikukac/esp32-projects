#pragma once

struct TemperatureData {
  float temperature;
  float humidity;
};

class TemperatureSensor {
public:
  virtual ~TemperatureSensor() = default;
  virtual bool begin() = 0;
  virtual TemperatureData read() = 0;
};
