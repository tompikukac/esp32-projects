#include <Arduino.h>
#include "deepsleep.h"

DeepSleep::DeepSleep() {

}
void DeepSleep::sleepInSec(uint32_t seconds) {
    const uint64_t sleepTimeUs = (uint64_t)seconds * 1000000ULL;
    Serial.flush();

    esp_sleep_enable_timer_wakeup(sleepTimeUs);
    esp_deep_sleep_start();
}

void DeepSleep::sleep(uint32_t minutes, uint32_t seconds) {
    // Sleep duration
    // const uint32_t minutes = 1;
    const uint32_t totalSeconds = minutes * 60 + seconds;
    // Human‑readable message
    Serial.printf("Entering deep sleep for %u minutes (%u seconds)...\n",minutes, seconds);
    sleepInSec(totalSeconds);
}