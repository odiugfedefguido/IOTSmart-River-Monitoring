#include "Arduino.h"
#include "tasks/AutomaticTask.h"
#include "tasks/ManualTask.h"
#include "tasks/DashboardTask.h"
#include "components/sensor/Button.h"
#include "tasks/StateMachine.h"

// Define pin numbers
#define BUTTON_PIN 2
#define SERVO_PIN 3

// Initialize components
Button button(BUTTON_PIN);
ServoMotor myServo(SERVO_PIN);
Display myDisplay;
Potentiometer myPotentiometer(A0);

// Initialize tasks
TaskAutomatic taskAutomatic(myServo, myDisplay);
TaskManual taskManual(myServo, myDisplay, myPotentiometer);
TaskDashboard taskDashboard(myServo, myDisplay);

// Variables for button state tracking
bool buttonState = false;
bool lastButtonState = false;
unsigned long debounceDelay = 100;

// Function prototypes
void checkForButtonPress();

void setup() {
    // Initialize button
    button.setup();

    // Initialize serial communication
    Serial.begin(9600);

    // Attach servo motor
    myServo.attach();

    // Set up display
    myDisplay.set();
}

void loop() {
    // Check for manual mode switch
    checkForButtonPress();

    // Schedule the appropriate task based on the current state
    if (StateMachine::getCurrentState() == AUTOMATIC_STATE) {
        taskAutomatic.tick();
    } else if (StateMachine::getCurrentState() == MANUAL_STATE) {
        taskManual.tick();
    } else {
        taskDashboard.tick();
    }
}

// Function to check for button press
void checkForButtonPress() {
    // Read current state of the button
    bool isButtonPressed = button.read() == HIGH;

    if (isButtonPressed && !lastButtonState) {
        // Button is pressed

        // Change state and notify the dashboard
        if (StateMachine::getCurrentState() == MANUAL_STATE) {
            Serial.println("AUTOMATIC");
            StateMachine::transitionTo(AUTOMATIC_STATE);
        } else if (StateMachine::getCurrentState() == AUTOMATIC_STATE) {
            Serial.println("MANUAL");
            Serial.println("ANGLE " + String(myPotentiometer.perPot())); // Send command with percentage via serial
            StateMachine::transitionTo(MANUAL_STATE);
        }

        // Update button state and debounce
        lastButtonState = isButtonPressed;
        delay(debounceDelay);

    } else if (!isButtonPressed && lastButtonState) {
        // Button is released
        lastButtonState = isButtonPressed;
        delay(debounceDelay);
    }

    // Wait for a short period to avoid button debounce
    delay(200);
}
