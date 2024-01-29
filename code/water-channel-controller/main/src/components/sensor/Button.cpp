#include "Button.h"

Button::Button(int pin) : buttonPin(pin), lastButtonState(false), buttonState(false) {}

void Button::setup() {
    pinMode(buttonPin, INPUT);
}

void Button::update() {
    lastButtonState = buttonState;
    buttonState = digitalRead(buttonPin);
}

bool Button::isPressed() {
    return !lastButtonState && buttonState;
}

int Button::read() {
    return digitalRead(buttonPin);
}
