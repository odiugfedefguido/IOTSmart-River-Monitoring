#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define PIN_POT A0
Servo myServo; //dichiarazione dell'oggetto servo



LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);


void setup() {
  Serial.begin(9600);  // Inizializza la comunicazione seriale a 9600 bps
  //lcd
  lcd.init();
  lcd.backlight();

  // Inizializzazione del servo su pin 3
  myServo.attach(3); // Sostituisci 3 con il numero del tuo pin

  // Inizializza la comunicazione seriale
  Serial.begin(9600);
}

void loop() {
  
  int n = PerPot(); //percentuale di apertura
  
  SetLCD();
  PrintLCD(n);  
  MoveServo(n);

  // Aggiorna ogni 500 millisecondi
  delay(500);
}

//ritorna il valore del potenziometro
int PotValue(){
  int valorePotenziometro = analogRead(PIN_POT);  // Leggi il valore del potenziometro

  // Stampa il valore sulla porta seriale
  Serial.print("Valore Potenziometro: ");
  Serial.println(valorePotenziometro);
  return valorePotenziometro;
}

//ritorna il valore del potenziometro in percentuale
int PerPot(){

  Serial.println(PotValue()/10);
  return PotValue()/10;


}

//setta in display LCD
void SetLCD(){
  
  //lcd
  lcd.setCursor(2, 1); // Set the cursor on the third column and first row.
}

//Stampa sul display LCD
void PrintLCD(int percentuale){
  // Pulisci il display
  lcd.clear();
  lcd.print(percentuale); //stampa il valore del potenziometro nell'lcd
}

//muovo il servo in base alla percentuale
void MoveServo(int percentuale){
  
  // Assicurati che l'angolo sia compreso tra 0 e 180
  percentuale = constrain(percentuale, 0, 180);

  // Muovi il servo all'angolo desiderato
  myServo.write(percentuale);

  // Puoi anche stampare il valore su seriale a scopo di debug
  Serial.print("Servo Angolo: ");
  Serial.println(percentuale);
}
