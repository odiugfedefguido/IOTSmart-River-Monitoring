#ifndef TASK_CONTROL_H
#define TASK_CONTROL_H


#include "components/actuators/Servo.h"
#include "components/actuators/Display.h"
#include "components/actuators/Potentiometer.h"
#include "Task.h"

class TaskControl : public Task {
public:
    TaskControl(ServoMotor &servo, Display &display, Potentiometer &potentiometer);
    void init(int period);
    void tick();

private:
    ServoMotor &myServo;
    Display &myDisplay;
    Potentiometer &myPotentiometer;
};

#endif  // TASK_CONTROL_H
