#include <Wire.h>
#include <Arduino.h>

#include "oled/oled_display.h"

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
  delay(1000);

  // Wire.begin(I2C_SDA, I2C_SCL);
  
  // bool status = bme.begin(BME280_I2C_ADDR);
  // if (!status) {
  //   Serial.println("Nem sikerült inicializálni a BME280 szenzort!");
  //   while (1);
  // }
  // Serial.println("BME280 inicializálva.");

  pinMode(LED_PIN, OUTPUT);

  // oled.begin();
  // oled.setFont(u8g2_font_osb26_tf);

  delay(50);
  Serial.println("setup...");
}

void loop() {

  // u8g2.setFont(u8g2_font_ncenB08_tr);
  // u8g2.setFont(u8g2_font_spleen32x64_mf);

  // u8g2.drawStr(0, 20, "Hello World");
  // u8g2.drawStr(0, 10, "Line 1");
  // u8g2.drawStr(0, 20, "Line 2");
  // u8g2.drawStr(0, 30, "Line 3");
  // u8g2.drawStr(0, 40, "Line 4");
  // u8g2.drawStr(0, 50, "Line 5");

  // oled.setText("33.6", 0, 40);
  // oled.show();

  // if (!mySensor.beginI2C(Wire)) {
  //   Serial.println("BME280 nem indul");
  // }
  //   Serial.println("BME280 inicializálva.");
  //   float temperature = mySensor.readTempC();
  //   float humidity = mySensor.readFloatHumidity();
  //   float pressure = mySensor.readFloatPressure() / 100.0F; // hPa-ba

    // Serial.print("Hőmérséklet: ");
    // Serial.print(temperature);
    // Serial.print(" °C, Páratartalom: ");
    // Serial.print(humidity);
    // Serial.print(" %, Légnyomás: ");
    // Serial.print(pressure);
    // Serial.println(" hPa");

    delay(1000);
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);


  // // --- Init BME280 ---
  // if (!bme.begin(0x76)) {
  //   Serial.println("BME280 not found!");
  //  // esp_deep_sleep_start();
  // }

  // --- Force-mode, lowest power ---
  // bme.setSampling(
  //   Adafruit_BME280::MODE_FORCED,
  //   Adafruit_BME280::SAMPLING_X1,   // temperature
  //   Adafruit_BME280::SAMPLING_X1,   // pressure
  //   Adafruit_BME280::SAMPLING_X1,   // humidity
  //   Adafruit_BME280::FILTER_OFF
  // );

  // --- Let ESP32 settle thermally ---
  delay(300);   // critical if waking from deep sleep

  // --- Throw away first reading ---
  // bme.takeForcedMeasurement();
  delay(100);

  // // --- Actual measurement ---
  // bme.takeForcedMeasurement();

  // float temperature = bme.readTemperature();
  // float humidity    = bme.readHumidity();
  // float pressure    = bme.readPressure() / 100.0F;

  // Serial.printf("T=%.2f °C  H=%.2f %%  P=%.2f hPa\n",
  //               temperature, humidity, pressure);

  Serial.println("Looping...");
  delay(10000);
  Serial.println("Looping...");


}
