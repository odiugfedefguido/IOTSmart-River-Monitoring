// TaskAutomatic.h
#ifndef TASK_AUTOMATIC_H
#define TASK_AUTOMATIC_H

#include "Task.h"
#include "components/actuators/Servo.h"
#include "components/actuators/Display.h"
#include "components/actuators/Potentiometer.h"

class TaskAutomatic : public Task {
public:
    TaskAutomatic(ServoMotor& servo, Display& display, Potentiometer& potentiometer);
    void init(int period) override;
    void tick() override;

private:
    ServoMotor& myServo;
    Display& myDisplay;
    Potentiometer& myPotentiometer;

    // Aggiungi altre variabili di stato o parametri specifici
};

#endif  // TASK_AUTOMATIC_H
