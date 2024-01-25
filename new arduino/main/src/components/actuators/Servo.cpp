#include "Servo.h"
#include "Arduino.h"

ServoMotor::ServoMotor(int pin) : servoPin(pin) {
    // Empty constructor
}

void ServoMotor::attach() {
    myServo.attach(servoPin);
}

void ServoMotor::write(int angle) {
    myServo.write(angle);
}

void ServoMotor::detach() {
    myServo.detach();
}
