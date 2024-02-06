#include "Button.h"

// Constructor
Button::Button(int pin) : buttonPin(pin), lastButtonState(false), buttonState(false) {}

// Method to set up the button
void Button::setup() {
    pinMode(buttonPin, INPUT);
}

// Method to update the button state
void Button::update() {
    lastButtonState = buttonState;
    buttonState = digitalRead(buttonPin);
}

// Method to check if the button is pressed
bool Button::isPressed() {
    // Return true if the button state transitioned from not pressed to pressed
    return !lastButtonState && buttonState;
}

// Method to read the state of the button pin (HIGH or LOW)
int Button::read() {
    return digitalRead(buttonPin);
}
