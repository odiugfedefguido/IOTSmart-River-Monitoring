#include "Arduino.h"
#include "tasks/AutomaticTask.h"
#include "tasks/ManualTask.h"
#include "components/sensor/Button.h"

#define BUTTON_PIN 2
#define SERVO_PIN 9
// Aggiungi altri pin o definizioni se necessario

Button button(BUTTON_PIN);

ServoMotor myServo(SERVO_PIN);  // Sostituisci 9 con il pin del tuo servo
Display myDisplay;              // Assumi che Display sia una classe con un'implementazione adeguata
Potentiometer myPotentiometer(A0);  // Assumi che Potentiometer sia una classe con un'implementazione adeguata

TaskAutomatic taskAutomatic(myServo, myDisplay, myPotentiometer);
TaskManual taskManual(myServo, myDisplay, myPotentiometer);

void setup() {
    // Inizializza il pulsante
    button.setup();

    // Inizializza i task
    taskAutomatic.init(1000);  // Periodo di 1000 millisecondi (1 secondo)
    taskManual.init(1000);     // Periodo di 1000 millisecondi (1 secondo)
}

void loop() {
    // Aggiorna lo stato del pulsante
    button.update();

    // Verifica se il pulsante è stato premuto
    if (button.isPressed()) {
        // Cambia lo stato quando il pulsante è premuto
        if (taskAutomatic.isActive()) {
            taskAutomatic.setActive(false);  // Disattiva il task automatico
            taskManual.setActive(true);       // Attiva il task manuale
        } else {
            taskManual.setActive(false);      // Disattiva il task manuale
            taskAutomatic.setActive(true);    // Attiva il task automatico
        }

        // Attendi un breve periodo per evitare debounce del pulsante
        delay(100);
    }

    // Esegui il task corrente se è attivo
    if (taskAutomatic.isActive()) {
        taskAutomatic.tick();
    } else if (taskManual.isActive()) {
        taskManual.tick();
    }
}
