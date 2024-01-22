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
  return read()/10;
  
}

void Potentiometer::print() //stampa il valore del potenziometro in percentuale
{
  Serial.println(perPot());
}