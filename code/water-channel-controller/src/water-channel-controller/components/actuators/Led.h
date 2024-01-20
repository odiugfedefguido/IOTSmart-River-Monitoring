#ifndef LED_H
#define LED_H

class Led
{
public:
  Led(int pin);
  void turnOn();
  void turnOff();
  void setup();

private:
  int pinLed;
};

#endif
