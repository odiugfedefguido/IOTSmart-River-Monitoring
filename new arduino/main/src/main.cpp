#include <Arduino.h>
//#include "components/actuators/Servo.h"
#include "components/actuators/Display.h"
#include "components/actuators/Potentiometer.h"




#define PIN_POT A0
#define PIN_SERVO 3
//Servo myServo; //dichiarazione dell'oggetto servo
Potentiometer pot(PIN_POT);
Display display;


void setup() {
  Serial.begin(9600);
  display.set();
}

void loop() {
  
  display.SetValue(pot.perPot());
  display.print();
  pot.print();
  delay(500);
}






