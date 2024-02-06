#include "Potentiometer.h"
#include "Arduino.h"

// Constructor
Potentiometer::Potentiometer(int pin) : POT_PIN(pin) {
  // Empty constructor body
}

// Method to set up the potentiometer
void Potentiometer::setup() {
  pinMode(POT_PIN, INPUT);
}

// Method to read the value of the potentiometer
int Potentiometer::read() {
  return analogRead(POT_PIN); // Read the value of the potentiometer
}

// Method to convert the value of the potentiometer to percentage
int Potentiometer::perPot() {
  if (read() > 1000) {
    return 180; // If the value is greater than 1000, return 180 (maximum angle)
  } else if (read() < 0) {
    return 0;   // If the value is less than 0, return 0 (minimum angle)
  } else {
    // Map the potentiometer value to a range between 0 and 180 degrees
    return map(read(), 0, 1000, 0, 180);
  }
}

