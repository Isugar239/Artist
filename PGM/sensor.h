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

  int tick() {
    int raw = analogRead(pin);
    
    if (calibrated) {
      int mapped = map(raw, blackValue, whiteValue, 255, 0);
      data = constrain(mapped, 255, 0);
    } else {
      data = map(raw, 0, 1023, 255, 0);
    }
    return data;
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
    while (true) {
      c.tick();
      
      if (data < 128) {
        break;
      }
    }
    c.gotoPos(c.getPos());
    // c.setPos(0);
    // while (c.tick()) {}
  }
};

