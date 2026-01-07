#pragma once
#include <Arduino.h>
#include <GyverStepper2.h>

class cart {
private:
  GStepper2<STEPPER2WIRE> left;
  GStepper2<STEPPER2WIRE> right;

  float stepsPerMm;
  int maxSpeed;
  int maxAccel;

public:
  cart(int res,
       int l_dir, int l_step,
       int r_dir, int r_step,
       int maxSpeed = 4000,
       int maxAccel = 500,
       float stepsPerMm = 25.0)
    : left(res, l_step, l_dir),
      right(res, r_step, r_dir),
      stepsPerMm(stepsPerMm),
      maxSpeed(maxSpeed),
      maxAccel(maxAccel)
  {
    left.reverse(-1);
    left.setMaxSpeed(maxSpeed);
    right.setMaxSpeed(maxSpeed);

    left.setAcceleration(maxAccel);
    right.setAcceleration(maxAccel);
  }

  void setPos(float mm) {
    long steps = mm * stepsPerMm;
    left.setTarget(steps);
    right.setTarget(steps);
  }

  bool tick() {
    bool l = left.tick();
    bool r = right.tick();
    return l || r;  
  }

  void gotoPos(float mm) {
    setPos(mm);
    unsigned long start = millis();
    while (tick() && millis() - start < 30000) {
      delay(1);
    }
  }
};
