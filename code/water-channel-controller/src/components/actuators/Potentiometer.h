#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

// Class declaration for Potentiometer
class Potentiometer
{
public:
  // Constructor
  Potentiometer(int pin);

  // Method to set up the potentiometer
  void setup();

  // Method to read the value of the potentiometer
  int read();

  // Method to convert the value of the potentiometer to percentage
  int perPot();

private:
  int POT_PIN;  // Pin number of the potentiometer
};

#endif
