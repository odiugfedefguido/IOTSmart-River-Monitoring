#include "AutomaticTask.h"
#include "StateMachine.h"

// Constructor
TaskAutomatic::TaskAutomatic(ServoMotor& servo, Display& display)
    : Task(), myServo(servo), myDisplay(display) {
    // Initialize TaskAutomatic with references to ServoMotor and Display objects
}

// Method to initialize the task with a period
void TaskAutomatic::init(int period) {
    Task::init(period); // Call the init method of the base class Task
}

// Method to execute the task
void TaskAutomatic::tick() {
    // Read serial input for commands from the dashboard in automatic mode
    while (Serial.available() > 0) {
        // Read the instruction message from the serial input until a newline character is encountered
        String instructionMessage = Serial.readStringUntil('\n');

        // Check if the instruction message is to switch to the dashboard state
        if (instructionMessage == "DASHBOARD") {
            // Transition to the dashboard state
            StateMachine::transitionTo(DASHBOARD_STATE);
        } else {
            // Extract the valve angle value from the instruction message and convert it to an integer
            int receivedValveAngle = instructionMessage.substring(instructionMessage.indexOf(' ') + 1).toInt();

            // Print the received valve angle and mode on the display
            myDisplay.print(receivedValveAngle, "AUTOMATIC");

            // Set the angle of the servo motor
            myServo.write(receivedValveAngle);
        }
    }
}

