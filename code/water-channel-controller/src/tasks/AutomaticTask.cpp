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
    
    // TODO: delete this line
    // int servoAngle = map(receivedValue, 0, 100, 0, 180);
    Serial.println("RECEIVED: " + String(receivedValue));

    // TODO: Why is this not working?
    myServo.write(receivedValue);
}
