#include "ManualTask.h"
#include "Arduino.h"

TaskManual::TaskManual(ServoMotor &servo, Display &display, Potentiometer &potentiometer)
    : Task(MANUAL_STATE), myServo(servo), myDisplay(display), myPotentiometer(potentiometer) {}

void TaskManual::init(int period) {
    Task::init(period);
}

void TaskManual::tick() {

    // Leggi il valore del potenziometro
    int potValue = myPotentiometer.perPot();
    
    // Modifica il valore del display
    myDisplay.SetValue(potValue);
    myDisplay.print();

    // Muovi il servo in base al valore del potenziometro
    int servoAngle = map(potValue, 0, 1023, 0, 180);
    myServo.write(servoAngle);
}
