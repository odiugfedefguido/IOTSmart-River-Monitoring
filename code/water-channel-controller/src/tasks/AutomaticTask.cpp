#include "AutomaticTask.h"
#include "StateMachine.h"

TaskAutomatic::TaskAutomatic(ServoMotor& servo, Display& display)
    : Task(), myServo(servo), myDisplay(display) {

}

void TaskAutomatic::init(int period) {
    Task::init(period);

}

void TaskAutomatic::tick() {
    // Leggi la seriale per eventuali comandi dalla dashboard in modalità automatica
    while (Serial.available() > 0) {
        String instructionMessage = Serial.readStringUntil('\n');

        if (instructionMessage == "DASHBOARD") {
            StateMachine::transitionTo(DASHBOARD_STATE);
        } else {
            // Estrai il valore dalla stringa e convertilo in intero
            int receivedValveAngle = instructionMessage.substring(instructionMessage.indexOf(' ') + 1).toInt();    
            myDisplay.print(receivedValveAngle, "AUTOMATIC");
            myServo.write(receivedValveAngle);  
        }
    }
}
