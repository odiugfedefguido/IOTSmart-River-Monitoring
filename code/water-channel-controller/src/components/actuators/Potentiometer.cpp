#include "Potentiometer.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin) : POT_PIN(pin) {
  // Empty
}

void Potentiometer::setup()
{
  pinMode(POT_PIN, INPUT);
}

int Potentiometer::read()
{
  return analogRead(POT_PIN);
}