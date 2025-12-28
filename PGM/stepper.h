#include <GyverStepper2.h>

GStepper2<STEPPER2WIRE> left_stepper(128, 2, 4);
GStepper2<STEPPER2WIRE> right_stepper(128, 3, 5);


void setup() {
  Serial.begin(115200);
  left_stepper.setRunMode(FOLLOW_POS);   // режим следования к целевй позиции
  left_stepper.setMaxSpeed(1.8*360);         // установка макс. скорости в шагах/сек
  left_stepper.setAcceleration(500);     
  right_stepper.setRunMode(FOLLOW_POS);   
  right_stepper.setMaxSpeed(1.8*360);        
  right_stepper.setAcceleration(500);     // установка ускорения в шагах/сек/сек

}
val = 0;
void loop() {
  left_stepper.tick();
  right_stepper.tick();

  left_stepper.setTarget(val);
  right_stepper.setTarget(val);
  while(left_stepper.rick() && right_stepper.tick()){
  Serial.print("left: ");
  Serial.print(left_stepper.getCurrent());
  Serial.print("right: ");
  Serial.println(right_stepper.getCurrent());}
}
