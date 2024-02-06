#include "Display.h"
#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Create an instance of LiquidCrystal_I2C with the appropriate address and dimensions
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

// Constructor
Display::Display() {
  // Any initializations (if needed)
}

// Method to set up the display
void Display::set() {
  lcd.init();         // Initialize the LCD
  lcd.backlight();    // Turn on the backlight
  lcd.begin(20, 4);   // Initialize the display with the appropriate dimensions
}

// Method to print values on the display
void Display::print(int angle, char* state) {
  lcd.clear();  // Clear the display
  
  // Set the cursor position for printing the angle value
  lcd.setCursor(2, 0);  
  // Print the angle value on the LCD
  lcd.print("Angle: " + String(angle));

  // Set the cursor position for printing the state value
  lcd.setCursor(2, 1);
  // Print the state value on the LCD
  lcd.print(state);
}
