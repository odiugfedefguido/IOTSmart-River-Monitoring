#include "Display.h"
#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

Display::Display() {
  // Eventuali inizializzazioni
}

void Display::set() {
  lcd.init();
  lcd.backlight();
  lcd.begin(20, 4);  // Inizializza il display con le dimensioni appropriate
}

void Display::print(int angle, char* state) {
  lcd.clear();
  
  lcd.setCursor(2, 0); // Imposta il cursore sulla terza colonna e sulla seconda riga.
  lcd.print("Angle: " + String(angle)); // Stampa il valore del displayValue sull'lcd

  lcd.setCursor(2, 1); // Imposta il cursore sulla terza colonna e sulla seconda riga.
  lcd.print(state); // Stampa il valore del displayValue sull'lcd
}


