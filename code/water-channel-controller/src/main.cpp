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
unsigned long debounceDelay = 100;

void setup() {
    button.setup();
    Serial.begin(9600);

    myServo.attach();
    myDisplay.set();

    taskAutomatic.setActive(true);
    taskManual.setActive(false);
}

void loop() {
    // Leggi lo stato corrente del pulsante
    bool isButtonPressed = button.read() == HIGH;

    if (isButtonPressed && !lastButtonState) {
        // button is pressed

        if (taskManual.isActive()){
            taskAutomatic.setActive(true);
            taskManual.setActive(false);
            Serial.println("AUTOMATIC"); // Invia comando via seriale alla dashboard
        } else if (taskAutomatic.isActive()) {
            taskAutomatic.setActive(false);
            taskManual.setActive(true);
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

    Serial.println("automatic = " + String(taskAutomatic.isActive()));
    Serial.println("manual = " + String(taskManual.isActive()));

    // Esegui il task corrente se è attivo
    if (taskAutomatic.isActive()) {
        taskAutomatic.tick();
        
        // Leggi la seriale per eventuali comandi dalla dashboard in modalità automatica
        while (Serial.available() > 0) {
            String comandoAutomatico = Serial.readStringUntil('\n');

            if (comandoAutomatico == "DASHBOARD") {
                taskAutomatic.setActive(false);
            }

            // Estrai il valore dalla stringa e convertilo in intero
            int valoreAutomatico = comandoAutomatico.substring(comandoAutomatico.indexOf(' ') + 1).toInt();

            // Imposta il valore ricevuto nella classe TaskAutomatic
            taskAutomatic.setReceivedValue(valoreAutomatico);        
        }
    } else if (taskManual.isActive()) {
        // manual mode
        taskManual.tick();
        Serial.println("ANGLE " + String(myPotentiometer.perPot())); // Invia la percentuale attuale via seriale
    } else {

        // dashboard mode
        while (Serial.available() > 0) {
            String comandoAutomatico = Serial.readStringUntil('\n');
            Serial.println(comandoAutomatico);

            if (comandoAutomatico == "DASHBOARD") {
                taskAutomatic.setActive(true);
            } else {
                // Estrai il valore dalla stringa e convertilo in intero
                int valoreAutomatico = comandoAutomatico.substring(comandoAutomatico.indexOf(' ') + 1).toInt();
                myDisplay.print(valoreAutomatico, "DASHBOARD");
                myServo.write(valoreAutomatico);   
            }            
        }
    }
}
