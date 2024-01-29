#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
public:
    // Costruttore
    Button(int pin);

    // Metodo per inizializzare il pulsante
    void setup();

    // Metodo per aggiornare lo stato del pulsante
    void update();

    // Metodo per verificare se il pulsante è premuto
    bool isPressed();

    // Metodo per leggere lo stato del pin del pulsante (HIGH o LOW)
    int read();

private:
    int buttonPin;
    bool lastButtonState;
    bool buttonState;
};

#endif  // BUTTON_H
