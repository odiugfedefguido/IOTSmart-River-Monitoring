#include <avr/sleep.h>
#include "SleepMode.h"

#include "../components/sensors/Pir.h"
#include "../components/actuators/Led.h"
#include "../components/sensors/Button.h"

void setupInterrupt(int pin) {
  attachInterrupt(digitalPinToInterrupt(pin), onWakeUp, RISING);
}

void enterSleepMode() {
  sei(); // set interrupts enabled
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
}

void onWakeUp() {
  // disable sleep
  sleep_disable();
}
