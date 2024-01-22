#include <Arduino.h>

const int ledPin1 = 27;  // Pin del primo LED
const int ledPin2 = 25;  // Pin del secondo LED

void setup() {
  pinMode(ledPin1, OUTPUT);  // Imposta il pin del primo LED come output
  pinMode(ledPin2, OUTPUT);  // Imposta il pin del secondo LED come output
}

void loop() {
  // Accende il primo LED e spegne il secondo
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, LOW);
  delay(1000);  // Attendi 1 secondo

  // Accende il secondo LED e spegne il primo
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, HIGH);
  delay(1000);  // Attendi 1 secondo
}
