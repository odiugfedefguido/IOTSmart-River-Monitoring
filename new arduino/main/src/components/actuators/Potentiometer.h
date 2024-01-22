#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

class Potentiometer
{
public:
  Potentiometer(int pin);
  void setup();
  int read();
  int perPot();
  void print();

private:
  int POT_PIN;
  
  
};

#endif