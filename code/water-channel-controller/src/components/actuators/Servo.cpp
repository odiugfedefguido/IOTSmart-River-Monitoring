#include "Servo.h"
#include "Arduino.h"

// Constructor
ServoMotor::ServoMotor(int pin) : servoPin(pin) {
    // Empty constructor body
}

// Method to attach the servo motor to a pin
void ServoMotor::attach() {
    myServo.attach(servoPin);
}

// Method to set the angle of the servo motor
void ServoMotor::write(int angle) {
    myServo.write(angle);
}

// Method to detach the servo motor from the pin
void ServoMotor::detach() {
    myServo.detach();
}
