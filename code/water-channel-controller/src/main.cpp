#include "Arduino.h"
#include "tasks/AutomaticTask.h"
#include "tasks/ManualTask.h"
#include "components/sensor/Button.h"

#define BUTTON_PIN 2
#define SERVO_PIN 3

Button button(BUTTON_PIN);

ServoMotor myServo(SERVO_PIN);
Display myDisplay;
Potentiometer myPotentiometer(A0);

TaskAutomatic taskAutomatic(myServo, myDisplay);
TaskManual taskManual(myServo, myDisplay, myPotentiometer);

bool buttonState = false;
bool lastButtonState = false;
bool debounceState = false;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 100;

void setup() {
    button.setup();
    Serial.begin(9600);

    myServo.attach();
    myDisplay.set();

    taskAutomatic.init(1000);
    taskManual.init(1000);
}

void loop() {
    // Leggi lo stato corrente del pulsante
    bool isButtonPressed = button.read() == HIGH;

    if (isButtonPressed && !lastButtonState) {
        // button is pressed

        if (taskManual.isActive()){
            taskAutomatic.setActive(true);
            taskManual.setActive(false);
            Serial.println("Switching to AUTOMATIC mode");
            Serial.println("AUTOMATIC"); // Invia comando via seriale alla dashboard
        } else {
            taskAutomatic.setActive(false);
            taskManual.setActive(true);
            Serial.println("Switching to MANUAL mode");
            Serial.println("MANUAL"); 
            Serial.println("ANGLE " + String(myPotentiometer.perPot())); // Invia comando con percentuale via seriale
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

    // Esegui il task corrente se è attivo
    if (taskAutomatic.isActive()) {
        taskAutomatic.tick();
        
        // Leggi la seriale per eventuali comandi dalla dashboard in modalità automatica
        while (Serial.available() > 0) {
            String comandoAutomatico = Serial.readStringUntil('\n');
            Serial.println(comandoAutomatico);
            // Estrai il valore dalla stringa e convertilo in intero
            int valoreAutomatico = comandoAutomatico.substring(comandoAutomatico.indexOf(' ') + 1).toInt();

            // Imposta il valore ricevuto nella classe TaskAutomatic
            taskAutomatic.setReceivedValue(valoreAutomatico);        
        }

        // Serial.println("automatic tick");
    } else if (taskManual.isActive()) {
        taskManual.tick();
        // Serial.println("manual tick");
        Serial.println("ANGLE " + String(myPotentiometer.perPot())); // Invia la percentuale attuale via seriale
    }
}
