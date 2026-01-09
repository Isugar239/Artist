#pragma once
#include <Servo.h>
#include "cart.h"

class marker {
private:
  Servo marker;
  int pin;
  int posUp;
  int posDown;
  cart& robot;

public:
  marker(int pin, int up, int down, cart& c)
    : pin(pin), posUp(up), posDown(down), robot(c) {
    // marker.write(posUp);
  }
  void begin(){
    marker.attach(pin);
  }
  void up() {
    marker.write(posUp);
  }

  void down() {
    marker.write(posDown);
  }

  void drawLine(int posStart, int posStop) {
    robot.gotoPos(posStart);
    this->down();
    robot.gotoPos(posStop);
    this->up();
  }
};
