#include "Potentiometer.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin) : POT_PIN(pin) {
  // Empty
}

void Potentiometer::setup()
{
  pinMode(POT_PIN, INPUT);
}

int Potentiometer::read()
{
  return analogRead(POT_PIN); //legge il valore del potenziometro
}

int Potentiometer::perPot() //converte il valore del potenziometro in percentuale
{
  if (read() > 1000) {
    return 180;
  } else if (read() < 0) {
    return 0;
  } else {
    return map(read(), 0, 1000, 0, 180);
  }
  
}

void Potentiometer::print() //stampa il valore del potenziometro in percentuale
{
  //Serial.println(perPot());
}