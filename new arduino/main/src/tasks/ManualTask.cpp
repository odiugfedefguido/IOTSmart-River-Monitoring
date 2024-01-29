#include "ManualTask.h"
#include "Arduino.h"
#include "SystemState.h"

TaskManual::TaskManual(ServoMotor &servo, Display &display, Potentiometer &potentiometer)
    : Task(SystemState::MANUAL_STATE), myServo(servo), myDisplay(display), myPotentiometer(potentiometer) {}

void TaskManual::init(int period) {
    Task::init(period);
}

void TaskManual::tick() {

    // Leggi il valore del potenziometro
    int potValue = myPotentiometer.perPot();
    Serial.println("Pot: " + String(potValue));
    
    // Modifica il valore del display
    myDisplay.SetValue(potValue);
    myDisplay.print();

    // Muovi il servo in base al valore del potenziometro
    int servoAngle = map(potValue, 0, 100, 0, 180);
    Serial.println("Servo angle: " + String(servoAngle));
    myServo.write(servoAngle);
}
