#include <Arduino.h>
//#include "components/actuators/Servo.h"
//#include "components/actuators/Display.h"
#include "components/actuators/Potentiometer.h"




#define PIN_POT A0
#define PIN_SERVO 3
//Servo myServo; //dichiarazione dell'oggetto servo
Potentiometer pot(PIN_POT);


void setup() {
  Serial.begin(9600);
}

void loop() {
  
  pot.print();
  delay(500);
}






