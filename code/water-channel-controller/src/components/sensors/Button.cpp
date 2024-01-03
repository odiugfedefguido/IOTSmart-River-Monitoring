#include "Button.h"
#include "Arduino.h"

Button::Button(int pin) : pinButton(pin)
{
  pinMode(pinButton, INPUT);
}

bool Button::isPressed()
{
  return digitalRead(pinButton) == HIGH;
}

