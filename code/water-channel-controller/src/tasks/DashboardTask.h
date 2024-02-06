#ifndef TASK_DASHBOARD_H
#define TASK_DASHBOARD_H

// Include necessary header files
#include "components/actuators/Servo.h"
#include "components/actuators/Display.h"
#include "Task.h"

// Class declaration for TaskDashboard, which is a subclass of Task
class TaskDashboard : public Task {
public:
    // Constructor
    TaskDashboard(ServoMotor &servo, Display &display);

    // Method to initialize the task with a period
    void init(int period);

    // Method to execute the task
    void tick();

private:
    ServoMotor &myServo;     // Reference to the servo motor object
    Display &myDisplay;       // Reference to the display object
};

#endif  // TASK_DASHBOARD_H
