#pragma once
#include <Arduino.h>

class Stepper {
  /*НЕ ТРОГАТЬ, КЛАСС ДЛЯ cart*/
private:
  int dirPin;
  int stepPin;
  float stepsPerMm;
  
  long pos;
  long target;
  float speed;
  float maxSpeed;
  float accel;
  
  unsigned long lastTime;
  unsigned long delay;

public:
  Stepper(int res, int dir, int step, float stepsPerMm = 100.0)
    : dirPin(dir), stepPin(step), stepsPerMm(stepsPerMm),
      pos(0), target(0), speed(0), maxSpeed(100), accel(100),
      lastTime(0), delay(10000)
  {
    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    digitalWrite(stepPin, LOW);
  }
  

  void setMaxSpeed(float s) {
    maxSpeed = s;
  }

  void setAcceleration(float a) {
    accel = a;
  }
  
  void setTarget(long t) {
    target = t;
  }
  
  bool tick() {
    long dist = target - pos;
    if (dist == 0) {
      speed = 0;
      return false;
    }
    
    float maxV = sqrt(2.0 * accel * abs(dist)); 
    
    if (speed < maxSpeed && speed < maxV) { // еще разгонняемся
      speed = min(speed + accel * 0.0001, maxSpeed);
    } else if (maxV < speed) { // уже тормозим
      speed = max(speed - accel * 0.0001, maxV);
    } else { // верхушка трапеции
      speed = min(speed, maxV);
    }
    
    delay = speed > 0 ? (unsigned long)(1000000.0 / speed) : 1000000;
    
    unsigned long now = micros();
    if (now - lastTime >= delay) {
      digitalWrite(dirPin, dist > 0 ? HIGH : LOW);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(2);
      digitalWrite(stepPin, LOW);
      
      pos += (dist > 0 ? 1 : -1);
      lastTime = now;
    }
    
    return dist != 0;
  }
};

class cart {
private:
  int res;
  int l_dir, l_step;
  int r_dir, r_step;
  int maxSpeed;
  int maxAccel;
  
public:
  Stepper left;
  Stepper right;
  float stepsPerMm;

  cart(int res,
       int l_dir, int l_step,
       int r_dir, int r_step,
       int maxSpeed = 648,
       int maxAccel = 500,
       float stepsPerMm = 100.0)
    : res(res),
      l_dir(l_dir), l_step(l_step),
      r_dir(r_dir), r_step(r_step),
      maxSpeed(maxSpeed), maxAccel(maxAccel),
      left(res, l_dir, l_step, stepsPerMm),
      right(res, r_dir, r_step, stepsPerMm),
      stepsPerMm(stepsPerMm)
  {
    left.setMaxSpeed(maxSpeed);
    right.setMaxSpeed(maxSpeed);
    left.setAcceleration(maxAccel);
    right.setAcceleration(maxAccel);
  }

  void setPos(float mm) {
    long steps = (long)(mm * stepsPerMm);
    left.setTarget(steps);
    right.setTarget(steps);
  }

  bool tick() {
    return left.tick() | right.tick();
  }

  void gotoPos(float mm) {
    setPos(mm);
    while (tick()) {}
  }
};
