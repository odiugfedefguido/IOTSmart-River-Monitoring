// Button.cpp
#include "Button.h"

Button::Button(int pin) : buttonPin(pin), lastButtonState(HIGH), lastDebounceTime(0), debounceDelay(50) {}

void Button::setup() {
    pinMode(buttonPin, INPUT);
}

void Button::update() {
    int reading = digitalRead(buttonPin);

    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != lastButtonState) {
            lastButtonState = reading;

            // Verifica se il pulsante è stato premuto
            if (lastButtonState == LOW) {
                // Puoi aggiungere azioni specifiche quando il pulsante è premuto
            }
        }
    }
}

bool Button::isPressed() {
    return lastButtonState == LOW;
}
