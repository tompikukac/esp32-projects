#include <Wire.h>
#include <Arduino.h>

#include "oled/oled_display.h"
#include "sensor/temperature_sensor.h"
#include "sensor/sensor_factory.h"

OledDisplay oled;
// WifiControllerB* wifi;
// WifiControllerB wifi;
// #include <Adafruit_BME280.h>
// #include <Adafruit_BME280.h>

// #include "esp_sleep.h"

// #define I2C_SDA 4
// #define I2C_SCL 5
// #define BME280_I2C_ADDR 0x76

// U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 6, /* data=*/ 5);

#define LED_PIN 8


void setup() {
 Serial.begin(115200);
  delay(3000);
  Serial.println("setup...");

  pinMode(LED_PIN, OUTPUT);

  delay(50);
  Serial.println("setup end");
}

void loop() {

  TemperatureSensor* sensor1 = createSensor(SensorType::BME680, Wire);
  TemperatureSensor* sensor2 = createSensor(SensorType::SHT40, Wire);
  TemperatureSensor* sensor3 = createSensor(SensorType::BME280, Wire);
  
  // SENSOR
  if (!sensor1 || !sensor1->begin()) {
    Serial.println("ERROR!!!");
  } else {
    Serial.println("SUCCESS 1!!!");
    TemperatureData data = sensor1->read();

    Serial.println(data.toString());
  }

  if (!sensor2 || !sensor2->begin()) {
    Serial.println("ERROR 2!!!");
  } else {
    Serial.println("SUCCESS 2!!!");
    TemperatureData data = sensor2->read();
    Serial.println(data.toString());
  }

  if (!sensor3 || !sensor3->begin()) {
    Serial.println("ERROR 3!!!");
  } else {
    Serial.println("SUCCESS 3!!!");
    TemperatureData data = sensor3->read();
    Serial.println(data.toString());
  }

  TemperatureData data1;
  TemperatureData data2;
  TemperatureData data3;
  for (int i = 0; i <= 35; i++) {
    data1 = sensor1->read();
    data2 = sensor2->read();
    data3 = sensor3->read();
    Serial.println(data1.temperature);
    Serial.println(data2.temperature);
    Serial.println(data3.temperature);
    Serial.println("-");
    Serial.println(data1.humidity);
    Serial.println(data2.humidity);
    Serial.println(data3.humidity);
    Serial.println("-");
    Serial.println(data1.pressure);
    Serial.println(data3.pressure);
    Serial.println("-----");
    Serial.println(data2.temperature-data3.temperature);
    Serial.println(data2.humidity-data3.humidity);
    Serial.println(data1.pressure-data3.pressure);

    Serial.println("-----");
    delay(3000);
  }


  delay(15000);

}
