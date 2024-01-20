#include "Display.h"
#include "Arduino.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);


void Display::setup() 
{
  /* Wiring: SDA => A4, SCL => A5 */
  /* I2C address of the LCD: 0x27 */
  /* Number of columns: 20 rows: 4 */
  lcd.init();
  lcd.backlight();
}

void Display::showText(Message message) 
{
  lcd.clear();
  lcd.backlight();


  switch (message)
  {
    case MSG_INIT:
      lcd.setCursor(0, 0);
      lcd.print("Initializing ...");
      break;
    case MSG_MANUAL:
      lcd.setCursor(4, 0);
      lcd.print("Manual ");
      break;
    case MSG_AUTOMATIC:
      lcd.setCursor(1, 0);
      lcd.print("Automatic");
      break;
  }
}

void Display::showText(int percentual) 
{
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(percentual);
}

void Display::turnOff() {
  lcd.clear();
  lcd.noBacklight();
}