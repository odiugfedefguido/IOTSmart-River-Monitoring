#include "TaskManual.h"
#include "components/actuators/Potentiometer.h"
#include "components/actuators/ServoMotor.h"
#include "components/actuators/Display.h"

/*

TaskManual::TaskManual(Potentiometer& potentiometer, ServoMotor& servoMotor, Display& display)
    : Task(MANUAL), potentiometer(potentiometer), servoMotor(servoMotor), display(display){
  // Inizializzazioni, se necessario
}

void TaskManual::setup() {
  // Configurazioni iniziali, se necessarie
}

void TaskManual::tick() {
  // Implementazione delle operazioni da eseguire ad ogni iterazione

  // Esempio: Leggi il valore dal potenziometro
  int potValue = potentiometer.readValue();

  //// Esempio: Aggiorna la posizione del motore servo in base al valore del potenziometro
  //int servoPosition = map(potValue, 0, 1023, 0, 180);
  //servoMotor.setPosition(servoPosition);

  // Esempio: Aggiorna il display con il valore del potenziometro
  display.showValue(potValue);
}
*/