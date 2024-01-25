// Task.cpp
#include "Task.h"
#include "StateMachine.h"

Task::Task(SystemState activeState) : activeState(activeState) {
    active = false;
}

void Task::init(int period) {
    myPeriod = period;
    periodic = true;  
    active = true;
    timeElapsed = 0;
}

void Task::init() {
    timeElapsed = 0;
    periodic = false;
    active = true;
    completed = false;
}

bool Task::updateAndCheckTime(int basePeriod) {
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod) {
        timeElapsed = 0;
        return true;
    } else {
        return false; 
    }
}

void Task::setCompleted() {
    completed = true;
    active = false;
}

bool Task::isCompleted() {
    return completed;
}

bool Task::isPeriodic() {
    return periodic;
}

bool Task::isActive() {
    return active && (StateMachine::getCurrentState() == activeState);
}

void Task::setActive(bool active) {
    timeElapsed = 0;
    this->active = active;
}
