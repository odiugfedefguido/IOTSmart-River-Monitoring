/*#include "Display.h"
#include "Arduino.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

Display::Display() {
  // Eventuali inizializzazioni
}

void Display::set(int value) {
  void Display::set() {
  lcd.init();
  lcd.backlight();
  lcd.begin(20, 4);  // Inizializza il display con le dimensioni appropriate
}

}

void Display::SetValue(int value){
  displayValue = value;
  //lcd
  lcd.setCursor(2, 1); // Set the cursor on the third column and first row.
}

void Display::print() {
 void Display::print() {
  lcd.clear();
  lcd.setCursor(2, 1); // Imposta il cursore sulla terza colonna e sulla seconda riga.
  lcd.print(displayValue); // Stampa il valore del displayValue sull'lcd
}

}
*/