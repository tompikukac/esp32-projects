#pragma once
#include <Arduino.h>
#include <cmath>

struct TemperatureData {
  float temperature = NAN;
  float humidity = NAN;
  float pressure = NAN; // hPA in sea level (100m)
  float gas_resistance = NAN; // kOhm
  bool isValid() const {
    return !isnan(temperature) || !isnan(humidity) || !isnan(pressure) || !isnan(gas_resistance);
  }

  TemperatureData operator+(const TemperatureData& other) const {
    TemperatureData result;

    result.temperature    = safeAdd(temperature,    other.temperature);
    result.humidity       = safeAdd(humidity,       other.humidity);
    result.pressure       = safeAdd(pressure,       other.pressure);
    result.gas_resistance = safeAdd(gas_resistance, other.gas_resistance);

    return result;
  }

  String toString() const {
    return "Temperature: " + String(temperature) + " °C, \n" +
           "Humidity: " + String(humidity) + " %, \n" +
           "Pressure: " + String(pressure) + " hPa, \n" + 
           "Gas resistance: " + String(gas_resistance) + " kOhm"; 
  }

  static float safeAdd(float a, float b) {
    if (isnan(a)) return NAN;
    if (isnan(b)) b = 0.0f;
    return a + b;
  }
};

class TemperatureSensor {
public:
  virtual ~TemperatureSensor() = default;

  bool begin();
  void setOffsets(TemperatureData offset);
  bool isStarted() const;
  TemperatureData read();

protected:
  virtual bool beginImpl() = 0;
  virtual TemperatureData readImpl() = 0;

private:
  bool started = false;
  TemperatureData offsetData;
};
