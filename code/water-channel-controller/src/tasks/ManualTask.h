#ifndef TASK_MANUAL_H
#define TASK_MANUAL_H

// Include necessary header files
#include "components/actuators/Servo.h"
#include "components/actuators/Display.h"
#include "components/actuators/Potentiometer.h"
#include "Task.h"

// Class declaration for TaskManual, which is a subclass of Task
class TaskManual : public Task {
public:
    // Constructor
    TaskManual(ServoMotor &servo, Display &display, Potentiometer &potentiometer);

    // Method to initialize the task with a period
    void init(int period);

    // Method to execute the task
    void tick();

private:
    ServoMotor &myServo;         // Reference to the servo motor object
    Display &myDisplay;           // Reference to the display object
    Potentiometer &myPotentiometer; // Reference to the potentiometer object
};

#endif  // TASK_MANUAL_H
