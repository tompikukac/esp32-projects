#pragma once

// #include <stdint.h>

class DeepSleep {
public:
    DeepSleep();
    void sleep(uint32_t minutes = 10, uint32_t seconds = 0); 
    // void sleep(uint32_t minutes, uint32_t seconds);
};