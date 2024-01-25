#include "ManualTask.h"
#include "Arduino.h"

TaskControl::TaskControl(ServoMotor &servo, Display &display, Potentiometer &potentiometer)
    : Task(MANUAL_STATE), myServo(servo), myDisplay(display), myPotentiometer(potentiometer) {}

void TaskControl::init(int period) {
    Task::init(period);
}

void TaskControl::tick() {

    // Leggi il valore del potenziometro
    int potValue = myPotentiometer.perPot();
    
    // Modifica il valore del display
    myDisplay.SetValue(potValue);
    myDisplay.print();

    // Muovi il servo in base al valore del potenziometro
    int servoAngle = map(potValue, 0, 1023, 0, 180);
    myServo.write(servoAngle);
}
