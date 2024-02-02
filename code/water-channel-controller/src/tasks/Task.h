// Task.h
#ifndef TASK_H
#define TASK_H

#include "Arduino.h"

class Task {
public:
    Task();
    virtual void init(int period);
    virtual void init();
    virtual void tick() = 0;
    bool updateAndCheckTime(int basePeriod);
    void setCompleted();
    bool isCompleted();
    bool isPeriodic();
    bool isActive();
    virtual void setActive(bool active);

private:
    int myPeriod;
    int timeElapsed;
    bool active;
    bool periodic;
    bool completed;
};

#endif  // TASK_H
