#include "Task.h"

#include "../components/actuators/ServoMotor.h"
#include "../components/actuators/Potentiometer.h"
#include "../components/actuators/Display.h"




class TaskManual : public Task{
public:
  TaskManual(SystemState activeState, Potentiometer& potentiometer, ServoMotor& servoMotor, Display& display);
  void setup();
  void tick();

private:   
  Potentiometer& potentiometer;
  ServoMotor& servoMotor;
  Display& display;
  
};