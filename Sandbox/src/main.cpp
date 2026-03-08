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

TemperatureSensor* sensorSHT40 = createSensor(SensorType::SHT40, Wire);
TemperatureSensor* sensor680 = createSensor(SensorType::BME680, Wire);
// TemperatureSensor* sensor = createSensor(SensorType::SHT40);


void setup() {
 Serial.begin(115200);
  delay(1000);

  // Wire.begin(I2C_SDA, I2C_SCL);
  
  // bool status = bme.begin(BME280_I2C_ADDR);
  // if (!status) {
  //   Serial.println("Nem sikerült inicializálni a BME280 szenzort!");
  //   while (1);
  // }
  // Serial.println("BME280 inicializálva.");

  pinMode(LED_PIN, OUTPUT);

  oled.begin();
  oled.setFont(u8g2_font_timB18_tn);
  // oled.setFont(u8g2_font_ncenB08_tr);

  delay(50);
  Serial.println("setup...");
}

void loop() {

   if (sensor680 && sensor680->begin()) {

    if(sensor680->isStarted()) {
      Serial.println("Szenzor sikeres.");
    } else {
      Serial.println("Szenzor sikertelen.");
    }

sensorSHT40->begin();



    TemperatureData dataSHT40 = sensorSHT40->read();  
    Serial.println(dataSHT40.toString());
    
    
    TemperatureData data680 = sensor680->read();
    Serial.println(data680.toString());

    String tempSHT40 = String(dataSHT40.temperature, 2);
    String humSHT40 = String(dataSHT40.humidity, 2);
    String temp680 = String(data680.temperature, 2);

    Serial.println("#############  SHT40:" + tempSHT40);
    Serial.println("############# BME680:" + temp680);

    oled.setText(tempSHT40, 0, 30);
    oled.show();
    digitalWrite(LED_PIN, HIGH);
    delay(5000);
    oled.setText(humSHT40+"a", 0, 30);
    oled.show();
    digitalWrite(LED_PIN, LOW);
    // oled.setText(humidityStr, 0, 40);
   } else {
    Serial.println("Szenzor inicializálása sikertelen!");
    oled.setText("Sensor error", 0, 30);
    oled.show();
   }
  

  

  delay(100);


  Serial.println("Looping...");
  delay(5000);

  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
  Serial.println("Looping...");


}
