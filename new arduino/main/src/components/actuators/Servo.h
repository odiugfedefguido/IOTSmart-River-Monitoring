#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include <Servo.h>

class ServoMotor {
public:
    ServoMotor(int pin);
    void attach();
    void write(int angle);
    void detach();

private:
    int servoPin;
    Servo myServo;
};

#endif  // SERVO_MOTOR_H
