#include "ManualTask.h"
#include "Arduino.h"

// Constructor
TaskManual::TaskManual(ServoMotor &servo, Display &display, Potentiometer &potentiometer)
    : Task(), myServo(servo), myDisplay(display), myPotentiometer(potentiometer) {
    // Initialize TaskManual with references to ServoMotor, Display, and Potentiometer objects
}

// Method to initialize the task with a period
void TaskManual::init(int period) {
    Task::init(period); // Call the init method of the base class Task
}

// Method to execute the task
void TaskManual::tick() {
    // Read the angle from the potentiometer
    int angle = myPotentiometer.perPot();
    
    // Print the angle value via serial
    Serial.println("ANGLE " + String(angle));

    // Print the angle on the display with mode "MANUAL"
    myDisplay.print(angle, "MANUAL");

    // Set the angle of the servo motor
    myServo.write(angle);
}
