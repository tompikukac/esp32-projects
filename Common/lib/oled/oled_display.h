#pragma once

#include <U8g2lib.h>

class OledDisplay {
public:
    OledDisplay();
    void begin();
    void setFont(const uint8_t* font);
    void setText(const char* text, int x = 0, int y = 0);
    void show();

private:
    U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2;
    const char* bufferText;
    int bufferX;
    int bufferY;
};
