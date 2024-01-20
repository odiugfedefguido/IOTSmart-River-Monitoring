#ifdef __MANUAL_TASK__
#define __MANUAL_TASK__

#include "Task.h"

#include "../../src/components/actuators/Potentiometer.h"
#include "../../src/components/actuators/ServoMotor.h"
#include "../../src/components/actuators/Display.h"



class TaskManual : public Task{
public:
  TaskManual(Potentiometer& potentiometer, ServoMotor& servoMotor, Display& display);
  void setup();
  void tick();

private:   
  Potentiometer& potentiometer;
  ServoMotor& servoMotor;
  Display& display;
  
};

#endif