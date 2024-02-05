#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Your WiFi credentials
const char *ssid = "hotspot";
const char *password = "pfjrbqzsocuvuhebyk";

// MQTT server details
const char *mqttServer = "broker.mqtt-dashboard.com";
const int mqttPort = 1883;  
const char *mqttClientId = "esp32_client";

// MQTT topics
const char *waterLevelTopic = "esiot-2023-smart-river-monitoring-45983"; 
const char *frequencyTopic = "esiot-2023-smart-river-monitoring-58329"; 

// Pin configurations
const int ledPinG = 27;  // Green LED pin
const int ledPinR = 25;  // Red LED pin
const int triggerPin = 12; // Sonar trigger pin
const int echoPin = 13; // Sonar echo pin

// Frequencies for sending sonar data
const long F1 = 2000; // Frequency for normal state
const long F2 = 500;  // Frequency for other states
long currentFrequency = F1;

// WiFi and MQTT client instances
WiFiClient espClient;
PubSubClient client(espClient);

// Function to connect to WiFi
void connectToWiFi() {
  delay(10);

  // Displaying the SSID being connected to
  Serial.println(String("Connecting to ") + ssid);

  // Setting WiFi mode to station (client)  
  WiFi.mode(WIFI_STA);

  // Attempting to connect to the WiFi network with specified credentials
  WiFi.begin(ssid, password);
  
  // Waiting for the WiFi connection to be established
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// MQTT callback for handling incoming messages
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println(String("Message arrived on [") + topic + "] len: " + length );
  // Variable of the frequency taken from the ESP via MQTT
  char* frequency = (char*) payload;

  // It changes the frequency to send the data 
  if (frequency[1] == '1') {
    currentFrequency = F1;
  } else {
    currentFrequency = F2;
  }
}

// Function to reconnect to the MQTT broker
bool reconnectMQTT() {
  // Check if not currently connected to the MQTT broker
  if (!client.connected()) {
    Serial.print("Connecting to MQTT server...");

    // Attempting to connect to the MQTT broker with the client ID
    if (client.connect(mqttClientId)) {
      Serial.println("connected!");
      // Subscribe to the MQTT topic for receiving frequency updates
      client.subscribe(frequencyTopic);
      return true;
    } else {
      // Connection attempt failed, display the error code
      Serial.print("failed, error = ");
      Serial.println(client.state());
      return false;
    }
  }
  // Return true if already connected to the MQTT broker
  return true;
}

// Function to perform sonar measurement and send data to MQTT broker
double sonar() {
  // It sends an ultrasonic impuls to activate the sonar
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  // Measure the echo return time
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance based on the measured duration
  // The formula is: Distance = (speed of sound * time of travel) / 2
  // The speed of sound is approximately 343 meters per second
  float distance = (0.0343 * duration) / 2;
  
  return distance;
}

// Function to send sonar data to the MQTT broker
bool sendDataToRiver(double distance) {
  String payload = String(distance);
  Serial.println(String("Publishing message: ") + payload);
  // Attempting to publish the sonar data to the specified MQTT topic
  if (client.publish(waterLevelTopic, payload.c_str())){
    return true;
  } else {
    return false;
  }
}

// Function to read distance, handle MQTT communication, and control LEDs
void readDistance(){
  double distance = sonar();

  // The connection is OK and the network is OK
  if (reconnectMQTT() && sendDataToRiver(distance)) {
    digitalWrite(ledPinG, HIGH);
    digitalWrite(ledPinR, LOW);
    delay(currentFrequency); // It sends the data with the expected frequency
  } else {
    // There is a problem with the network or the connection
    Serial.println("Problem detected");
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
  
  // Connection to the wifi
  connectToWiFi();

  // Seed the random number generator with the microsecond value
  randomSeed(micros());

  // Connection to the MQTT broker and set up callback function for incoming messages
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}

void loop() {
  // Check if not connected to the MQTT broker and attempt reconnection
  if (!client.connected()) {
    reconnectMQTT();
  }
  // Maintain the MQTT connection and handle incoming messages
  client.loop();

  readDistance();
}
