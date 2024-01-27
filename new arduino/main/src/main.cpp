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

bool buttonState = false;
bool lastButtonState = false;
bool debounceState = false;
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
    bool reading = button.read() == HIGH;

    // Verifica se lo stato del pulsante è cambiato
    if (reading != lastButtonState) {
        // Aggiorna il timestamp dell'ultimo cambio di stato
        lastDebounceTime = millis();
        debounceState = false;
    }

    // Verifica se è trascorso il periodo di debounce
    if (!debounceState && (millis() - lastDebounceTime) > debounceDelay) {
        // Verifica se lo stato attuale è diverso dallo stato precedente
        if (reading != buttonState) {
            buttonState = reading;

            // Cambia lo stato solo quando il pulsante passa da LOW a HIGH
            if (buttonState) {
                if(taskManual.isActive()){
                    taskManual.setActive(false);
                    taskAutomatic.setActive(true);
                    Serial.println("Switching to AUTOMATIC mode");
                } else {
                    taskAutomatic.setActive(false);
                    taskManual.setActive(true);
                    Serial.println("Switching to MANUAL mode");
                }

                // Attendi un breve periodo per evitare debounce del pulsante
                delay(500);
            }
            Serial.println("manual state: " + String(taskManual.isActive()) + " automatic state: " + String(taskAutomatic.isActive()));
            debounceState = true;
        }
    }

    // Aggiorna lo stato precedente del pulsante
    lastButtonState = reading;

    // Esegui il task corrente se è attivo
    if (taskAutomatic.isActive()) {
        taskAutomatic.tick();
        Serial.println("automatic tick");
    } else if (taskManual.isActive()) {
        taskManual.tick();
        Serial.println("manual tick");
    }

    // Verifica se il pulsante è stato rilasciato
    if (!reading) {
        debounceState = false;
    }
}
