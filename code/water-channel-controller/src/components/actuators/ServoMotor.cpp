#include "ServoMotor.h"
#include "Arduino.h"

ServoMotor::ServoMotor(int pin) : GATE_PIN(pin) {
  // Empty
}

void ServoMotor::setup()
{
  servo.attach(GATE_PIN);
}

void ServoMotor::write(int angle)
{
  servo.write(angle);
}

void ServoMotor::detach()
{
  servo.detach();
}

int ServoMotor::read() {
  return servo.read();
}

void ServoMotor::openGate()
{
  /*int currentValue = servo.read();
  if (currentValue > 0)
  {
    servo.write(currentValue - 10);
  }*/
  servo.write(0);
}

void ServoMotor::closeGate()
{
  /*int currentValue = servo.read();
  if (currentValue < 2000)
  {
    servo.write(currentValue + 10);
  }*/
  servo.write(2000);
}
