/*#include "Servo.h"
#include "Arduino.h"

ServoMotor::ServoMotor(int pin) : GATE_PIN(pin) {
  // Empty
}

void ServoMotor::setup()
{
  servo.attach(GATE_PIN);
}



void MoveServo(int percentuale){
  // Assicurati che l'angolo sia compreso tra 0 e 180
  percentuale = constrain(percentuale, 0, 180);

  // Muovi il servo all'angolo desiderato
  myServo.write(percentuale);

  // Puoi anche stampare il valore su seriale a scopo di debug
  Serial.print("Servo Angolo: ");
  Serial.println(percentuale);
} */
