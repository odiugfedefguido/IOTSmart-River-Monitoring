#include "AutomaticTask.h"
#include "SystemState.h"

TaskAutomatic::TaskAutomatic(ServoMotor& servo, Display& display)
    : Task(SystemState::AUTOMATIC_STATE), myServo(servo), myDisplay(display), receivedValue(0) {

}

void TaskAutomatic::init(int period) {
    Task::init(period);

}

void TaskAutomatic::setReceivedValue(int value) {
    receivedValue = value;
}

void TaskAutomatic::tick() {


    
    myDisplay.SetValue(receivedValue);
    myDisplay.print();
    int servoAngle = map(receivedValue, 0, 100, 0, 180);

    myServo.write(receivedValue);

    
}
