#include "ManualTask.h"
#include "Arduino.h"

TaskManual::TaskManual(ServoMotor &servo, Display &display, Potentiometer &potentiometer)
    : Task(), myServo(servo), myDisplay(display), myPotentiometer(potentiometer) {}

void TaskManual::init(int period) {
    Task::init(period);
}

void TaskManual::tick() {
    int angle = myPotentiometer.perPot();
    
    Serial.println("ANGLE " + String(angle));
    myDisplay.print(angle, "MANUAL");
    myServo.write(angle);
}
