#ifndef TASK_DASHBOARD_H
#define TASK_DASHBOARD_H


#include "components/actuators/Servo.h"
#include "components/actuators/Display.h"
#include "Task.h"

class TaskDashboard : public Task {
public:
    TaskDashboard(ServoMotor &servo, Display &display);
    void init(int period);
    void tick();

private:
    ServoMotor &myServo;
    Display &myDisplay;
};

#endif  
