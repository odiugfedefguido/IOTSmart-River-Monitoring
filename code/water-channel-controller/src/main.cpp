/*
 * GROUP MEMBERS
 * Chiara De Nardi
 * Federica Guiducci
 * Florian Knoch
 */

#include <Arduino.h>

#include "components/sensors/Button.h"
#include "components/actuators/Display.h"
#include "components/actuators/ServoMotor.h"
#include "components/actuators/Led.h"

#include "core/Scheduler.h"
#include "core/StateMachine.h"

#include "serial/MsgService.h"

#define BUTTON_PIN 4
#define LED_RED_PIN 8
#define LED_GREEN_PIN 7
#define SERVO_PIN 3

Display display;
Button button(BUTTON_PIN);
ServoMotor servo(SERVO_PIN);
Led ledGreen(LED_GREEN_PIN);
Led ledRed(LED_RED_PIN);

Scheduler scheduler;

void setup() {
  Serial.begin(9600);
  scheduler.init(10); // base period
  MsgService.init();

  ledGreen.setup();
  ledRed.setup();

  servo.setup();
  display.setup();
  display.showText(MSG_INIT);

  // TODO: Add tasks.
}

void loop() {
  scheduler.schedule();
}
