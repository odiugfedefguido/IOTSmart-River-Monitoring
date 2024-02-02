#include "Arduino.h"
#include "tasks/AutomaticTask.h"
#include "tasks/ManualTask.h"
#include "tasks/DashboardTask.h"
#include "components/sensor/Button.h"
#include "tasks/StateMachine.h"

#define BUTTON_PIN 2
#define SERVO_PIN 3

Button button(BUTTON_PIN);

ServoMotor myServo(SERVO_PIN);
Display myDisplay;
Potentiometer myPotentiometer(A0);

TaskAutomatic taskAutomatic(myServo, myDisplay);
TaskManual taskManual(myServo, myDisplay, myPotentiometer);
TaskDashboard taskDashboard(myServo, myDisplay);

bool buttonState = false;
bool lastButtonState = false;
unsigned long debounceDelay = 100;

void checkForButtonPress();

void setup() {
    button.setup();
    Serial.begin(9600);

    myServo.attach();
    myDisplay.set();
}

void loop() {
    // check for switches into manual mode and back
    checkForButtonPress();

    // schedule the correct task for the current state
    if (StateMachine::getCurrentState() == AUTOMATIC_STATE) {
        taskAutomatic.tick();
    } else if (StateMachine::getCurrentState() == MANUAL_STATE) {
        taskManual.tick();
    } else {
        taskDashboard.tick();
    }
}

void checkForButtonPress() {
    // Leggi lo stato corrente del pulsante
    bool isButtonPressed = button.read() == HIGH;

    if (isButtonPressed && !lastButtonState) {
        // button is pressed

        // change state and notify the dashboard
        if (StateMachine::getCurrentState() == MANUAL_STATE) {
            Serial.println("AUTOMATIC");
            StateMachine::transitionTo(AUTOMATIC_STATE);
        } else if (StateMachine::getCurrentState() == AUTOMATIC_STATE) {
            Serial.println("MANUAL"); 
            Serial.println("ANGLE " + String(myPotentiometer.perPot())); // Invia comando con percentuale via seriale
            StateMachine::transitionTo(MANUAL_STATE);
        }
        
        lastButtonState = isButtonPressed;
        delay(debounceDelay);

    } else if (!isButtonPressed && lastButtonState) {
        // button is released
        lastButtonState = isButtonPressed;
        delay(debounceDelay);
    }

    // Attendi un breve periodo per evitare debounce del pulsante
    delay(200);
}