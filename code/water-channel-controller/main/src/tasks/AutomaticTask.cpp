// TaskAutomatic.cpp
#include "AutomaticTask.h"
#include "SystemState.h"

TaskAutomatic::TaskAutomatic(ServoMotor& servo, Display& display, Potentiometer& potentiometer)
    : Task(SystemState::AUTOMATIC_STATE), myServo(servo), myDisplay(display), myPotentiometer(potentiometer) {

}

void TaskAutomatic::init(int period) {
    Task::init(period);

}

void TaskAutomatic::tick() {

    int potValue = myPotentiometer.perPot(); //questo è sbagliato //lo riceve in input da fuori
    myServo.write(potValue);

    
    myDisplay.SetValue(potValue);
    myDisplay.print();

    
}
