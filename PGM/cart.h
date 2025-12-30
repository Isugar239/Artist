#pragma once
#include <GyverStepper2.h>

class cart {
public:
  GStepper2<STEPPER2WIRE> left;
  GStepper2<STEPPER2WIRE> right;

  cart(int res,
       int l_dir, int l_step,
       int r_dir, int r_step,
       int maxSpeed = 648,
       int maxAccel = 500)
    : left(res, l_dir, l_step),
      right(res, r_dir, r_step)
  {

    left.setMaxSpeed(maxSpeed);
    right.setMaxSpeed(maxSpeed);

    left.setAcceleration(maxAccel);
    right.setAcceleration(maxAccel);
  }

  void setPos(int pos) {
    left.setTarget(pos);
    right.setTarget(pos);
  }

  bool tick() {
    return left.tick() | right.tick();
  }

  void gotoPos(int pos) {
    this->setPos(pos);
    while (tick()) {}
  }
};
