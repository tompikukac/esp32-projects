#include <Arduino.h>
#include "esp32_c3_zero_led.cpp"

#include "wifi/wifi_controller.h"
#include "deepsleep.cpp"
#include "config.cpp"
#include "internet/internet_services.cpp"
#include "config_storage.cpp"
#include "bme280_sensor.h"
#include "secret.h"
#include "influxdb_controller.cpp"

#define CONFIG_ROOT "https://raw.githubusercontent.com/tompikukac/esp32-projects/main/config/devices/"

InfluxController influx("http://192.168.1.111:8086", "szlab", "esp32", "your-influxdb-token");

Esp32C3ZeroLed statusLed(10);

WifiController* wifi;
InternetServices net;
Config config;
DeepSleep deepSleep;
ConfigStorage storage;
BME280Sensor sensor(4, 5);

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("TEMPERATURE");
  
  statusLed.begin();
  statusLed.setBrightness(4);
  statusLed.setColor(Colors::Blue);  
delay(2000);
  Serial.println("WiFi connecting...");
  wifi = new WifiController();

  if (wifi->connect()) {
    Serial.println("WiFi connected!");
    Serial.println(WiFi.localIP());
    Serial.println(wifi->getDeviceId());

    storage.begin();
    if (!storage.loadConfig(config)) {
      // Load configuration
      Serial.println("Reading default configuration...");
      String defaultJson = net.getConfig(String(CONFIG_ROOT) + "default.json");
      config.parse(defaultJson);
      Serial.println("Reading specific configuration...");
      String configJson = net.getConfig(CONFIG_ROOT + wifi->getDeviceId() + ".json");
      Serial.println("Config JSON: " + configJson);
      config.parse(configJson);

      if(config.name != "default-device") {
          Serial.println("Saving configuration...");
          storage.saveConfig(config);
      }

    } else {
      Serial.println("Configuration loaded from storage.");
    }

    storage.end();

    if (!sensor.begin()) {
      Serial.println("BME280 init failed!");
      statusLed.setColor(Colors::Red);  
      deepSleep.sleepInSec(10);
    }
    Serial.println("BME280 ready");
    
    Serial.println(config.toString());

  } else {
      Serial.println("WiFi connection failed");
      statusLed.setColor(Colors::Red);  
      deepSleep.sleepInSec(10);
  }
  statusLed.setColor(Colors::Lime);  
}

// void sendToInflux(const BME280Data& data) {
//   if (WiFi.status() != WL_CONNECTED) {
//     Serial.println("WiFi not connected");
//     return;
//   }

//   HTTPClient http;
//   String url = String(influxHost) + "/api/v2/write?org=" + influxOrg + "&bucket=" + influxBucket + "&precision=s";
//   http.begin(url);
//   http.addHeader("Authorization", String("Token ") + influxToken);
//   http.addHeader("Content-Type", "text/plain");

//   String body = "environment,name=esp32 temperature=" + String(data.temperature, 2) +
//                 ",humidity=" + String(data.humidity, 2) +
//                 ",pressure=" + String(data.pressure, 2);

//   int httpResponseCode = http.POST(body);

//   if (httpResponseCode > 0) {
//     Serial.printf("InfluxDB response code: %d\n", httpResponseCode);
//   } else {
//     Serial.printf("Error sending to InfluxDB: %s\n", http.errorToString(httpResponseCode).c_str());
//   }

//   http.end();
// }

void loop() {
  Serial.println("LOOP...");
  statusLed.setColor(Colors::Olive);
  delay(1500); 
  statusLed.setColor(Colors::Green);
  delay(1500);
  Serial.println("...LOOP");

  BME280Data data = sensor.read();
  Serial.printf("T: %.2f C, H: %.2f %%, P: %.2f hPa\n",
                data.temperature, data.humidity, data.pressure);
 
  influx.send(data);


  delay(15000);


  statusLed.setColor(Colors::Blue);
  delay(500); 
  statusLed.setColor(Colors::Green);
  delay(500); 
  statusLed.off();
  // deepSleep.sleepInSec(10);
  // deepSleep.sleepInSec(config.deepSleepTimeInSec);
}
