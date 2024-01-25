#include <Arduino.h>
#include "components/actuators/Servo.h"
#include "components/actuators/Display.h"
#include "components/actuators/Potentiometer.h"




#define PIN_POT A0
#define PIN_SERVO 3

ServoMotor servo(PIN_SERVO);
Potentiometer pot(PIN_POT);
Display display;


void setup() {
  Serial.begin(9600);
  display.set();
  servo.attach();
}

void loop() {
  
  display.SetValue(pot.perPot());
  int perrr= pot.perPot();
  servo.write(perrr);
  display.print();
  pot.print();
  delay(500);
}






