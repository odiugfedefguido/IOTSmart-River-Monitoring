// TaskAutomatic.cpp
#include "AutomaticTask.h"
#include "SystemState.h"

TaskAutomatic::TaskAutomatic(ServoMotor& servo, Display& display, Potentiometer& potentiometer)
    : Task(SystemState::AUTOMATIC_STATE), myServo(servo), myDisplay(display), myPotentiometer(potentiometer) {
    // Inizializza altre variabili di stato o parametri specifici
}

void TaskAutomatic::init(int period) {
    Task::init(period);
    // Altre inizializzazioni specifiche
}

void TaskAutomatic::tick() {
    // Implementa il comportamento del task automatico

    // Esempio: muovi il servo in base al valore del potenziometro
    int potValue = myPotentiometer.perPot();
    myServo.write(potValue);

    // Esempio: aggiorna il display con informazioni pertinenti
    myDisplay.SetValue(potValue);
    myDisplay.print();

    // Altre azioni o logica specifica
}
