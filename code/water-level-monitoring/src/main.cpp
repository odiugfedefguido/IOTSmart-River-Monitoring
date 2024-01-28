#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

//tuo wifi da hotspot
const char *ssid = "hotspot";
const char *password = "pfjrbqzsocuvuhebyk";

//mqtt di un server web
const char *mqttServer = "broker.mqtt-dashboard.com";
const int mqttPort = 1883;  // Porta del server MQTT
const char *mqttClientId = "esp32_client";

//mqtt topics
const char *waterLevelTopic = "esiot-2023-smart-river-monitoring-45983"; 
const char *frequencyTopic = "esiot-2023-smart-river-monitoring-58329"; 

const int ledPinG = 27;  // Pin del LED verde
const int ledPinR = 25;  // Pin del LED rosso
const int triggerPin = 12; // Pin del trigger del sonar
const int echoPin = 13; // Pin dell'echo del sonar

const long F1 = 2000; // Frequenza con cui si inviano i dati del sonar in stato normale
const long F2 = 500; // frequenza con cui si inviano i dati del sonar negli altri stati
long currentFrequency = F1;

// Definizione degli stati del sistema

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
  char* frequency = (char*) payload;

  if (frequency[1] == '1') {
    currentFrequency = F1;
  } else {
    currentFrequency = F2;
  }
}

bool reconnectMQTT() {
  // Connessione al server MQTT
  if (!client.connected()) {
    Serial.print("Connessione al server MQTT...");
    if (client.connect(mqttClientId)) {
      Serial.println("connesso!");
      client.subscribe(frequencyTopic);
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
  if (client.publish(waterLevelTopic, payload.c_str())){
    return true;
  }else{
    return false;
  }
}

void readDistance(){
  double distance = sonar();

  if (reconnectMQTT() && sendDataToRiver(distance)) {
    // La connessione di rete è attiva e i dati sono stati inviati correttamente
    digitalWrite(ledPinG, HIGH);
    digitalWrite(ledPinR, LOW);
    delay(currentFrequency); //invia i dati con la frequenza prevista
  }else{
    // Problemi di connessione o invio dati
    Serial.println("problema rilevato");
    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinR, HIGH);
    delay(F2);
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

  readDistance();
}
