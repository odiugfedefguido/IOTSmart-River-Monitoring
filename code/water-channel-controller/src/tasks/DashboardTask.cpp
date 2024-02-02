#include "DashboardTask.h"
#include "StateMachine.h"
#include "Arduino.h"

TaskDashboard::TaskDashboard(ServoMotor &servo, Display &display)
    : Task(), myServo(servo), myDisplay(display) {}

void TaskDashboard::init(int period) {
    Task::init(period);
}

void TaskDashboard::tick() {
    while (Serial.available() > 0) {
        String instructionMessage = Serial.readStringUntil('\n');
        Serial.println(instructionMessage);

        if (instructionMessage == "DASHBOARD") {
            StateMachine::transitionTo(AUTOMATIC_STATE);
        } else {
            // Estrai il valore dalla stringa e convertilo in intero
            int valoreAutomatico = instructionMessage.substring(instructionMessage.indexOf(' ') + 1).toInt();
            myDisplay.print(valoreAutomatico, "DASHBOARD");
            myServo.write(valoreAutomatico);   
        }            
    }
}
