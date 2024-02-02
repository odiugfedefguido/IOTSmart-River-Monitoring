#include "AutomaticTask.h"

TaskAutomatic::TaskAutomatic(ServoMotor& servo, Display& display)
    : Task(), myServo(servo), myDisplay(display), receivedValue(0) {

}

void TaskAutomatic::init(int period) {
    Task::init(period);

}

void TaskAutomatic::setReceivedValue(int value) {
    receivedValue = value;
}

void TaskAutomatic::tick() {
    myDisplay.print(receivedValue, "AUTOMATIC");

    Serial.println("RECEIVED: " + String(receivedValue));

    myServo.write(receivedValue);
}
