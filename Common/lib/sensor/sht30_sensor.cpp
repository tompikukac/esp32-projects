#include <Wire.h>
#include <Adafruit_SHT31.h>
#include "temperature_sensor.cpp"

class SHT30Sensor : public TemperatureSensor {
public:
  bool begin() override {
    Wire.begin(5, 6);  // SDA=GPIO5, SCL=GPIO6
    return sht.begin(0x44);
  }

  TemperatureData read() override {
    TemperatureData data;
    data.temperature = sht.readTemperature();
    data.humidity = sht.readHumidity();
    return data;
  }

private:
  Adafruit_SHT31 sht;
};
