#pragma once
#include <Servo.h>
#include "cart.h"

class marker {
private:
  Servo marker;
  int posUp;
  int posDown;
  cart& robot;

public:
  marker(int pin, int up, int down, cart& c)
    : posUp(up), posDown(down), robot(c) {
    marker.attach(pin);
    marker.write(posUp);
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
