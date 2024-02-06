#include "DashboardTask.h"
#include "StateMachine.h"
#include "Arduino.h"

// Constructor
TaskDashboard::TaskDashboard(ServoMotor &servo, Display &display)
    : Task(), myServo(servo), myDisplay(display) {
    // Initialize TaskDashboard with references to ServoMotor and Display objects
}

// Method to initialize the task with a period
void TaskDashboard::init(int period) {
    Task::init(period); // Call the init method of the base class Task
}

// Method to execute the task
void TaskDashboard::tick() {
    // Check if there is data available on the serial port
    while (Serial.available() > 0) {
        // Read the instruction message from the serial input until a newline character is encountered
        String instructionMessage = Serial.readStringUntil('\n');
        Serial.println(instructionMessage); // Print the received instruction message

        // Check if the instruction message is to switch to automatic mode
        if (instructionMessage == "DASHBOARD") {
            // Transition to the automatic state
            StateMachine::transitionTo(AUTOMATIC_STATE);
        } else {
            // Extract the value from the instruction message and convert it to an integer
            int automaticValue = instructionMessage.substring(instructionMessage.indexOf(' ') + 1).toInt();
            
            // Print the value on the display with the mode as "DASHBOARD"
            myDisplay.print(automaticValue, "DASHBOARD");

            // Set the value on the servo motor
            myServo.write(automaticValue);
        }
    }
}
