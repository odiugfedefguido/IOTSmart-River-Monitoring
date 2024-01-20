#include "Led.h"
#include "Arduino.h"

Led::Led(int pin) : pinLed(pin)
{
  // Empty.
}

void Led::setup()
{
  pinMode(pinLed, OUTPUT);
  turnOff();
}

void Led::turnOn()
{
  digitalWrite(pinLed, HIGH);
}

void Led::turnOff()
{
  digitalWrite(pinLed, LOW);
}

