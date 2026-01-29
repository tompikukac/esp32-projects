#include <Arduino.h>
#include "deepsleep.h"

DeepSleep::DeepSleep() {

}
void DeepSleep::sleepInSec(uint32_t seconds) {
    uint64_t sleepTimeUs = (uint64_t)seconds * 1000000ULL;

    Serial.printf("Entering deep sleep for %u seconds...\n", seconds);
    Serial.flush();
    delay(50);   // optional, just for log visibility
    
    esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
    esp_sleep_enable_timer_wakeup(sleepTimeUs);
    esp_deep_sleep_start();
}

void DeepSleep::sleep(uint32_t minutes, uint32_t seconds) {
    const uint32_t totalSeconds = minutes * 60 + seconds;
    sleepInSec(totalSeconds);
}

void DeepSleep::lightSleepInSec(uint32_t seconds) {
    uint64_t sleepTimeUs = static_cast<uint64_t>(seconds) * 1000000ULL;

    Serial.printf("Entering light sleep for %u seconds...\n", seconds);
    Serial.flush();
    delay(100);

    esp_sleep_enable_timer_wakeup(sleepTimeUs);

    esp_light_sleep_start();

    Serial.println("Woke up from light sleep!");
}