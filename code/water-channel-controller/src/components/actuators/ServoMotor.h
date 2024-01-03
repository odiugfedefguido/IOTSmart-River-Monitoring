#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include "../../lib/ServoTimer2.h"

class ServoMotor
{
public:
  ServoMotor(int pin);
  void setup();
  void write(int angle);
  void detach();
  void openGate();
  void closeGate();
  int read();

private: 
  int GATE_PIN;
  ServoTimer2 servo;
};

#endif