#ifndef TASK_MANUAL_H
#define TASK_MANUAL_H


#include "components/actuators/Servo.h"
#include "components/actuators/Display.h"
#include "components/actuators/Potentiometer.h"
#include "Task.h"

class TaskManual : public Task {
public:
    TaskManual(ServoMotor &servo, Display &display, Potentiometer &potentiometer);
    void init(int period);
    void tick();

private:
    ServoMotor &myServo;
    Display &myDisplay;
    Potentiometer &myPotentiometer;
};

#endif  
