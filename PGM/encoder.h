#pragma once
#include <Arduino.h>

class Encoder {
private:
  int pinA;
  int pinB;
  int pinBtn;
  bool prevA;
  bool prevBtn;

public:
  int dir;
  bool clicked;

  Encoder(int a, int b, int btn)
    : pinA(a), pinB(b), pinBtn(btn), prevA(false), prevBtn(false), dir(0), clicked(false)
  {
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    pinMode(pinBtn, INPUT_PULLUP);
    prevA = digitalRead(pinA);
    prevBtn = digitalRead(pinBtn);
  }

  void tick() {
    bool currA = digitalRead(pinA);
    bool currB = digitalRead(pinB);
    bool currBtn = digitalRead(pinBtn);
    
    dir = 0;
    clicked = false;
    
    if (prevA != currA) {
      dir = (currB ^ currA) ? 1 : -1; // xor`им сигнал
      prevA = currA;
    }
    
    if (currBtn == LOW && prevBtn == HIGH) {
      clicked = true;
    }
    prevBtn = currBtn;
  }
};

