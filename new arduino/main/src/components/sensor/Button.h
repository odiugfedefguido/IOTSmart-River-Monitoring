// Button.h
#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"

class Button {
public:
    Button(int pin);
    void setup();
    void update();
    bool isPressed();

private:
    int buttonPin;
    int lastButtonState;
    unsigned long lastDebounceTime;
    unsigned long debounceDelay;
};

#endif  // BUTTON_H
