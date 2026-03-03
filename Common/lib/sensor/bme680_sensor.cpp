#include "bme680_sensor.h"

BME680Sensor::BME680Sensor(TwoWire& wire)
  : wire(wire) {}

bool BME680Sensor::beginImpl() {
  wire.begin(5, 6);  // SDA=GPIO5, SCL=GPIO6

  if (!bme.begin(0x77, &wire)) {  // change to 0x77 if needed
    return false;
  }

  // Basic oversampling configuration
  // bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  // bme.setGasHeater(320, 150);  // 320°C for 150 ms

  bme.setTemperatureOversampling(BME680_OS_1X);
  // bme.setHumidityOversampling(BME680_OS_1X);
  // bme.setPressureOversampling(BME680_OS_1X);
  // bme.setIIRFilterSize(BME680_FILTER_SIZE_0);
  bme.setGasHeater(0, 0);

  return true;
}

TemperatureData BME680Sensor::readImpl() {
  Serial.print("BME680Sensor: ");
  for (int i = 0; i <= 15; i++) {
    bme.performReading();
    Serial.print(bme.temperature);
    Serial.print(" : ");
    delay(1000);
  }

  TemperatureData data;  // defaults to NaN

  if (!bme.performReading()) {
    // measurement failed → return all-NaN
    return data;
  }

  if (!isnan(bme.temperature)) {
    data.temperature = bme.temperature;
  }

  if (!isnan(bme.humidity)) {
    data.humidity = bme.humidity;
  }

  if (!isnan(bme.pressure)) {
    data.pressure = bme.pressure;
  }

  // read GAS data
  bme.setGasHeater(320, 150);
  bme.performReading();


Serial.print("Temperature: ");
Serial.print(data.temperature);
Serial.println(" °C");

Serial.print("Humidity: ");
Serial.print(data.humidity);
Serial.println(" %");

Serial.print("Pressure: ");
Serial.print(data.pressure / 100.0);  // Pa → hPa
Serial.println(" hPa");
float seaLevel = bme.readPressure() / pow(1.0 - (100 / 44330.0), 5.255);
Serial.print(seaLevel / 100.0);
Serial.println(" hPa");

Serial.print("Gas resistance: ");
Serial.print(bme.gas_resistance / 1000.0);  // Ohm → kOhm
Serial.println(" kOhm");

Serial.println();




  return data;
}
