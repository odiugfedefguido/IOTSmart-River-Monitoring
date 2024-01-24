#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

//tuo wifi da hotspot
const char *ssid = "tuo nome hotspot";
const char *password = "tua pw";

//mqtt di un server web
const char *mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;  // Porta del server MQTT

const char *mqttClientId = "esp32_client";
const char *topic = "water_level"; //mqtt topic

const int ledPinG = 27;  // Pin del LED verde
const int ledPinR = 25;  // Pin del LED rosso
const int triggerPin = 12; // Pin del trigger del sonar
const int echoPin = 13; // Pin dell'echo del sonar
const long F1 = 10000; // Frequenza con cui si inviano i dati del sonar in stato normale
const long F2 = 20000; // frequenza con cui si inviano i dati del sonar negli altri stati

// Definizione degli stati del sistema
enum SystemState {
  NORMAL,
  ALARM_TOO_LOW,
  PRE_ALARM_TOO_HIGH,
  ALARM_TOO_HIGH,
  ALARM_TOO_HIGH_CRITIC
};

SystemState currentState = NORMAL;

WiFiClient espClient;
PubSubClient client(espClient);

void connectToWiFi() {
  delay(10);

  Serial.println(String("Connecting to ") + ssid);  

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

/* MQTT subscribing callback */
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println(String("Message arrived on [") + topic + "] len: " + length );
}

bool reconnectMQTT() {
  // Connessione al server MQTT
  if (!client.connected()) {
    Serial.print("Connessione al server MQTT...");
    if (client.connect(mqttClientId)) {
      Serial.println("connesso!");
      return true;
    } else {
      Serial.print("fallito, errore = ");
      Serial.println(client.state());
      return false;
    }
  }
  return true;
}

double sonar() {
  // Invia un impulso ultrasonico
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Misura il tempo di ritorno dell'eco
  long duration = pulseIn(echoPin, HIGH);

  // Calcola la distanza in base alla durata misurata
  // La formula è: Distanza = (velocità del suono * tempo di viaggio) / 2
  // La velocità del suono è di circa 343 metri al secondo
  float distance = (0.0343 * duration) / 2;

  return distance;
}

bool sendDataToRiver(double distance) {
  // Invia i dati al server MQTT
  String payload = String(distance);
  Serial.println(String("Publishing message: ") + payload);
  if(client.publish(topic, payload.c_str())){
    return true;
  }else{
    return false;
  }
}

void whenNormal(){
  double distance = sonar();
  Serial.println("Normal state");

  if (reconnectMQTT() && sendDataToRiver(distance)) {
    // La connessione di rete è attiva e i dati sono stati inviati correttamente
    digitalWrite(ledPinG, HIGH);
    digitalWrite(ledPinR, LOW);

    // Invia dati solo se sono trascorsi almeno F1 secondi dall'ultimo invio
    sendDataToRiver(distance);
    Serial.println("message sent");
    delay(F1); //invia i dati con una frequenza f1
  }else{
    // Problemi di connessione o invio dati2
    Serial.println("problema rilevato");
    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinR, HIGH);
    delay(1000);
  }
}

void whenNOTnormal(){
  double distance = sonar();
  Serial.println("not normal state");

  if (reconnectMQTT() && sendDataToRiver(distance)) {
    // La connessione di rete è attiva e i dati sono stati inviati correttamente
    digitalWrite(ledPinG, HIGH);
    digitalWrite(ledPinR, LOW);

    // Invia dati solo se sono trascorsi almeno F1 secondi dall'ultimo invio
    sendDataToRiver(distance);
    Serial.println("message sent");
    delay(F2); //invia i dati con una frequenza f2
  }else{
    // Problemi di connessione o invio dati
    Serial.println("problema rilevato");
    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinR, HIGH);
    delay(1000);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinR, OUTPUT);

  // Connessione alla rete WiFi
  connectToWiFi();

  randomSeed(micros());
  // Connessione al server MQTT
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  if (currentState == NORMAL){
    whenNormal();
  } else if(currentState == ALARM_TOO_LOW || currentState == PRE_ALARM_TOO_HIGH ||
              currentState == ALARM_TOO_HIGH || currentState == ALARM_TOO_HIGH_CRITIC) {
    whenNOTnormal();
  }
}
