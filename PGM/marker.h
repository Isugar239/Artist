#include <Servo.h>
#include<stepper.h>
Class marker
{
private:
  int pin;
  int posUp;
  int posDown;

public:
  marker(int pin, int posUp, int posDown)
  {
    Servo marker;
    marker.attach(pin);
  };
  void down()
  {
    marker.write(posDown);
  }
  void up()
  {
    marker.write(posUp);
  }
  void drawLine(int start, int stop){

  }
};
