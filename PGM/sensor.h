#pragma once
#include <Arduino.h>
#include "cart.h"

class Sensor {
private:
  int pin;
  int whiteValue;
  int blackValue;

public:
  int data;
  bool calibrated;

  Sensor(int p = 15)
    : pin(p), whiteValue(0), blackValue(0), calibrated(false), data(128)
  {
    pinMode(pin, INPUT);
    whiteValue = analogRead(pin);
  }

  void tick() {
    int raw = analogRead(pin);
    
    if (calibrated) {
      int mapped = map(raw, blackValue, whiteValue, 0, 255);
      data = constrain(mapped, 0, 255);
    } else {
      data = map(raw, 0, 1023, 0, 255);
    }
  }

  void calibrateWhite() {
    whiteValue = analogRead(pin);
  }

  void calibrateBlack() {
    blackValue = analogRead(pin);
    calibrated = true;
  }

  void align(cart& c) {
    c.setPos(1000);
    while (c.tick()) {
      tick();
      if (data < 128) {
        break;
      }
    }
    c.setPos(0);
    while (c.tick()) {}
  }
};

