#include "ManualTask.h"
#include "Arduino.h"

TaskManual::TaskManual(ServoMotor &servo, Display &display, Potentiometer &potentiometer)
    : Task(), myServo(servo), myDisplay(display), myPotentiometer(potentiometer) {}

void TaskManual::init(int period) {
    Task::init(period);
}

void TaskManual::tick() {

    // Leggi il valore del potenziometro
    int potValue = myPotentiometer.perPot();
    
    // Modifica il valore del display
    myDisplay.print(potValue, "MANUAL");

    // Muovi il servo in base al valore del potenziometro
    Serial.println("Servo angle: " + String(potValue));
    myServo.write(potValue);
}
