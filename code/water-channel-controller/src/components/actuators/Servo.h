#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include <Servo.h>

// Class declaration for ServoMotor
class ServoMotor {
public:
    // Constructor
    ServoMotor(int pin);

    // Method to attach the servo motor to a pin
    void attach();

    // Method to set the angle of the servo motor
    void write(int angle);

    // Method to detach the servo motor from the pin
    void detach();

private:
    int servoPin;   // Pin number of the servo motor
    Servo myServo;  // Servo object
};

#endif  // SERVO_MOTOR_H
