/*#include "Arduino.h"
#include "tasks/AutomaticTask.h"
#include "tasks/ManualTask.h"
#include "components/sensor/Button.h"

#define BUTTON_PIN 2
#define SERVO_PIN 9

Button button(BUTTON_PIN);

ServoMotor myServo(SERVO_PIN);
Display myDisplay;
Potentiometer myPotentiometer(A0);

TaskAutomatic taskAutomatic(myServo, myDisplay, myPotentiometer);
TaskManual taskManual(myServo, myDisplay, myPotentiometer);

bool buttonState = false;
bool lastButtonState = false;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
    button.setup();
    Serial.begin(9600);

    taskAutomatic.init(1000);
    taskManual.init(1000);
}

void loop() {
    // Leggi lo stato corrente del pulsante
    int reading = button.read();

    Serial.println(reading);
    // Verifica se lo stato del pulsante è cambiato
    if (reading != lastButtonState) {
        // Aggiorna il timestamp dell'ultimo cambio di stato
        lastDebounceTime = millis();
    }

    // Verifica se è trascorso il periodo di debounce
    if ((millis() - lastDebounceTime) > debounceDelay) {
        // Verifica se lo stato attuale è diverso dallo stato precedente
        if (reading != buttonState) {
            buttonState = reading;

            // Cambia lo stato solo quando il pulsante passa da rilasciato a premuto
            if (buttonState == HIGH) {
                if (taskAutomatic.isActive()) {
                    taskAutomatic.setActive(false);
                    taskManual.setActive(true);
                } else {
                    taskManual.setActive(false);
                    taskAutomatic.setActive(true);
                }

                // Attendi un breve periodo per evitare debounce del pulsante
                delay(100);
            }
        }
    }

    // Aggiorna lo stato precedente del pulsante
    lastButtonState = reading;

    // Esegui il task corrente se è attivo
    if (taskAutomatic.isActive()) {
        taskAutomatic.tick();
    } else if (taskManual.isActive()) {
        taskManual.tick();
    }
}
*/

#include "Arduino.h"
#include "tasks/AutomaticTask.h"
#include "tasks/ManualTask.h"
#include "components/sensor/Button.h"

#define BUTTON_PIN 2
#define SERVO_PIN 9

Button button(BUTTON_PIN);

ServoMotor myServo(SERVO_PIN);
Display myDisplay;
Potentiometer myPotentiometer(A0);

TaskAutomatic taskAutomatic(myServo, myDisplay, myPotentiometer);
TaskManual taskManual(myServo, myDisplay, myPotentiometer);

bool buttonWasPressed = false;

void setup() {
    button.setup();
    Serial.begin(9600);

    taskAutomatic.init(1000);
    taskManual.init(1000);
}

void loop() {
    button.update();

    Serial.println("Button state: " + String(button.read()));  // Stampa lo stato effettivo del pulsante

    if (button.read() == HIGH) {  // Controlla se il pulsante è premuto
        // Cambia lo stato solo quando il pulsante passa da rilasciato a premuto
        if (!buttonWasPressed) {
            buttonWasPressed = true;

            if (taskAutomatic.isActive()) {
                taskAutomatic.setActive(false);
                taskManual.setActive(true);
                Serial.println("Switching to MANUAL mode");
            } else {
                taskManual.setActive(false);
                taskAutomatic.setActive(true);
                Serial.println("Switching to AUTOMATIC mode");
            }

            // Attendi un breve periodo per evitare debounce del pulsante
            delay(100);
        }
    } else {
        buttonWasPressed = false;
    }

    if (taskAutomatic.isActive()) {
        taskAutomatic.tick();
    } else if (taskManual.isActive()) {
        taskManual.tick();
    }
}

