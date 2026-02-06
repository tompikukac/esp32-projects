#include <Wire.h>
#include <Adafruit_SHT4x.h>
#include "temperature_sensor.cpp"

class SHT40Sensor : public TemperatureSensor {
public:
  bool begin() override {
    return sht.begin();
  }

  TemperatureData read() override {
    TemperatureData data;
    sensors_event_t temp, humidity;
    sht.getEvent(&humidity, &temp);
    data.temperature = temp.temperature;
    data.humidity = humidity.relative_humidity;
    return data;
  }

private:
  Adafruit_SHT4x sht;
};
