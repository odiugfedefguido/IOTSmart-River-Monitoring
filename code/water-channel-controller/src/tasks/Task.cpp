// Task.cpp
#include "Task.h"

// Constructor
Task::Task() {
    active = false;
}

// Method to initialize the task with a period (in milliseconds)
void Task::init(int period) {
    myPeriod = period;
    periodic = true;
    active = true;
    timeElapsed = 0;
}

// Method to initialize the task without a period (for non-periodic tasks)
void Task::init() {
    timeElapsed = 0;
    periodic = false;
    active = true;
    completed = false;
}

// Method to update the time elapsed and check if the task should execute
bool Task::updateAndCheckTime(int basePeriod) {
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod) {
        timeElapsed = 0;
        return true;
    } else {
        return false;
    }
}

// Method to mark the task as completed
void Task::setCompleted() {
    completed = true;
    active = false;
}

// Method to check if the task has been completed
bool Task::isCompleted() {
    return completed;
}

// Method to check if the task is periodic
bool Task::isPeriodic() {
    return periodic;
}

// Method to check if the task is active
bool Task::isActive() {
    return active;
}

// Method to set the active state of the task
void Task::setActive(bool active) {
    timeElapsed = 0;
    this->active = active;
}
