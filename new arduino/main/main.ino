#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myServo; //dichiarazione dell'oggetto servo

const int potPin = A0;  // Il pin analogico a cui è collegato il potenziometro

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
  int valorePotenziometro = analogRead(potPin);  // Leggi il valore del potenziometro

  // Stampa il valore sulla porta seriale
  Serial.print("Valore Potenziometro: ");
  Serial.println(valorePotenziometro);

  int percentuale = valorePotenziometro/10;
  Serial.println(percentuale);
  //lcd
  lcd.setCursor(2, 1); // Set the cursor on the third column and first row.
  // Pulisci il display
  lcd.clear();
  lcd.print(percentuale); //stampa il valore del potenziometro nell'lcd
  //valore potenziometro da 0 a 100+
  
   // Assicurati che l'angolo sia compreso tra 0 e 180
  percentuale = constrain(percentuale, 0, 180);

  // Muovi il servo all'angolo desiderato
  myServo.write(percentuale);

  // Puoi anche stampare il valore su seriale a scopo di debug
  Serial.print("Servo Angolo: ");
  Serial.println(percentuale);

  // Aggiorna ogni 500 millisecondi
  delay(500);
}
