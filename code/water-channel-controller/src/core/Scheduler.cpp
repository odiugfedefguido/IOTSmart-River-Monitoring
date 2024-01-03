#include "Scheduler.h"
#include <TimerOne.h>

volatile bool timerFlag1;

void timerHandler(void){
  timerFlag1 = true;
}

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  timerFlag1 = false;
  long period = 1000l*basePeriod;
  Timer1.initialize(period);
  Timer1.attachInterrupt(timerHandler);
  nTasks = 0;
}

bool Scheduler::addTask(Task* task){
  if (nTasks < MAX_TASKS-1){
    taskList[nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false; 
  }
}
  
void Scheduler::schedule(){  
  while (!timerFlag1){}
  timerFlag1 = false;

  for (int i = 0; i < nTasks; i++){
    if (taskList[i]->isActive()){
      if (taskList[i]->isPeriodic()){
        if (taskList[i]->updateAndCheckTime(basePeriod)){
          taskList[i]->tick();
        }
      } else {
        taskList[i]->tick();
        if (taskList[i]->isCompleted()){
          taskList[i]->setActive(false);
        }
      }
    }
  }
}