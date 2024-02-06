// TaskAutomatic.h
#ifndef TASK_AUTOMATIC_H
#define TASK_AUTOMATIC_H

#include "Task.h"
#include "components/actuators/Servo.h"
#include "components/actuators/Display.h"

// Class declaration for TaskAutomatic, which is a subclass of Task
class TaskAutomatic : public Task {
public:
    // Constructor
    TaskAutomatic(ServoMotor& servo, Display& display);

    // Method to initialize the task with a period
    void init(int period) override;

    // Method to execute the task
    void tick() override;

private:
    ServoMotor& myServo;   // Reference to the servo motor object
    Display& myDisplay;     // Reference to the display object
};

#endif  // TASK_AUTOMATIC_H
