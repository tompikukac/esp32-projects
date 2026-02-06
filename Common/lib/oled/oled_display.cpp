#include "oled_display.h"

OledDisplay::OledDisplay()
  : u8g2(U8G2_R0, U8X8_PIN_NONE, 6, 5),
    bufferText(nullptr),
    bufferX(0),
    bufferY(0)
{
}

void OledDisplay::begin() {
  u8g2.begin();
}

void OledDisplay::setFont(const uint8_t* font) {
  u8g2.setFont(font);
}

void OledDisplay::setText(const char* text, int x, int y) {
  bufferText = text;
  bufferX = x;
  bufferY = y;
}

void OledDisplay::show() {
  u8g2.clearBuffer();
  if (bufferText) {
    u8g2.drawStr(bufferX, bufferY, bufferText);
  }
  u8g2.sendBuffer();
}
