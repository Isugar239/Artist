#pragma once
#include <FastLED.h>

class rgb {
private:
  CRGB* leds;
  int num;

public:
  rgb(uint8_t pin, int ledNum, int brightness = 50)
    : num(ledNum) {
    leds = new CRGB[num];
    FastLED.addLeds<WS2812, pin, GRB>(leds, num);
    FastLED.setBrightness(brightness);
    clear();
  }

  void clear() {
    for (int i = 0; i < num; i++) leds[i] = CRGB::Black;
    FastLED.show();
  }

  void red()    { setAll(CRGB::Red); }
  void green()  { setAll(CRGB::Green); }
  void blue()   { setAll(CRGB::Blue); }
  void yellow() { setAll(CRGB::Yellow); }
  void cyan()   { setAll(CRGB::Cyan); }
  void purple() { setAll(CRGB::Purple); }
  void white()  { setAll(CRGB::White); }
  void orange() { setAll(CRGB::Orange); }

private:
  void setAll(const CRGB& c) {
    for (int i = 0; i < num; i++) leds[i] = c;
    FastLED.show();
  }
};
