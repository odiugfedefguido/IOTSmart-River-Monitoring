// Task.h
#ifndef TASK_H
#define TASK_H

#include "Arduino.h"

// Class representing a generic task
class Task {
public:
    // Constructor
    Task();

    // Method to initialize the task with a period (in milliseconds)
    virtual void init(int period);

    // Method to initialize the task without a period (for non-periodic tasks)
    virtual void init();

    // Abstract method to execute the task (must be implemented by subclasses)
    virtual void tick() = 0;

    // Method to update the time elapsed and check if the task should execute
    bool updateAndCheckTime(int basePeriod);

    // Method to mark the task as completed
    void setCompleted();

    // Method to check if the task has been completed
    bool isCompleted();

    // Method to check if the task is periodic
    bool isPeriodic();

    // Method to check if the task is active
    bool isActive();

    // Method to set the active state of the task
    virtual void setActive(bool active);

private:
    int myPeriod;       // Period of the task (in milliseconds)
    int timeElapsed;    // Time elapsed since last execution of the task
    bool active;        // Flag indicating if the task is active
    bool periodic;      // Flag indicating if the task is periodic
    bool completed;     // Flag indicating if the task has been completed
};

#endif  // TASK_H
