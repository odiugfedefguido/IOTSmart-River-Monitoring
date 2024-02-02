// TaskAutomatic.h
#ifndef TASK_AUTOMATIC_H
#define TASK_AUTOMATIC_H

#include "Task.h"
#include "components/actuators/Servo.h"
#include "components/actuators/Display.h"

class TaskAutomatic : public Task {
public:
    TaskAutomatic(ServoMotor& servo, Display& display);
    void init(int period) override;
    void tick() override;
    void setReceivedValue(int value);

private:
    ServoMotor& myServo;
    Display& myDisplay;
    
    int receivedValue;
    
};

#endif  // TASK_AUTOMATIC_H
