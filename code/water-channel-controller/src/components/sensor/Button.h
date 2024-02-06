#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

// Class for representing a button
class Button {
public:
    // Constructor
    Button(int pin);

    // Method to initialize the button
    void setup();

    // Method to update the button state
    void update();

    // Method to check if the button is pressed
    bool isPressed();

    // Method to read the state of the button pin (HIGH or LOW)
    int read();

private:
    int buttonPin;          // Pin number of the button
    bool lastButtonState;   // Previous state of the button
    bool buttonState;       // Current state of the button
};

#endif  // BUTTON_H

