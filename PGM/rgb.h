#pragma once
#include <FastLED.h>

template<uint8_t PIN, uint16_t MAX>
class rgb {
private:
  CRGB leds[MAX];
  uint16_t num;
  uint8_t brightness;

public:
  rgb(uint16_t ledNum, uint8_t bright = 50)
    : num(ledNum), brightness(bright) {}

  void begin() {
    FastLED.addLeds<WS2812, PIN, GRB>(leds, num);
    FastLED.setBrightness(brightness);
    clear();
  }

  void clear() {
    for (int i = 0; i < num; i++) leds[i] = CRGB::Black;
    FastLED.show();
  }

  void red()    { setAll(CRGB::Red); }
  void green()  { setAll(CRGB::Green); }
    void yellow()  { setAll(CRGB::Yellow); }
    void white()  { setAll(CRGB::White); }

private:
  void setAll(const CRGB& c) {
    for (int i = 0; i < num; i++) leds[i] = c;
    FastLED.show();
  }
};
