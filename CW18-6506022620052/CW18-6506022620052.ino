#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// Uncomment the line for the DHT sensor type you're using
#define DHTTYPE DHT22  // DHT 22 (AM2302), AM2321
// #define DHTTYPE DHT11
// #define DHTTYPE DHT21 // DHT 21 (AM2301)

// Wi-Fi and MQTT server credentials
const char* ssid = "B415";
const char* password = "appletv415";
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;  // Use int type for port

// MQTT broker credentials
const char* MQTT_username = NULL;
const char* MQTT_password = NULL;

// Initialize WiFi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);

// GPIO pins for DHT sensor and LED
const int DHTPin = D7;  // GPIO 4 = D2 on ESP-12E NodeMCU board
const int ledPin = D6;  // GPIO 12 = D6 on ESP-12E NodeMCU board

// Initialize DHT sensor
DHT dht(DHTPin, DHTTYPE);

// Timing variables
unsigned long lastMeasure = 0;

// Function to connect to Wi-Fi
void setup_wifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

// MQTT callback function to handle received messages
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  Serial.println();

  String messageTemp;
  for (unsigned int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }
  Serial.println(messageTemp);

  // Control the LED based on the received message
  if (String(topic) == "kainapat/led") {
    if (messageTemp == "on") {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED turned On");
      Serial.println();
    } else if (messageTemp == "off") {
      digitalWrite(ledPin, LOW);
      Serial.println("LED turned Off");
      Serial.println();
    }
  }
}

// Function to reconnect to the MQTT broker and resubscribe to topics
void reconnect() {
  while (!client.connected()) {
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);  // Create a random client ID
    Serial.print("Attempting MQTT connection...");

    if (client.connect(clientId.c_str(), MQTT_username, MQTT_password)) {
      Serial.println("connected");
      client.subscribe("kainapat/led");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// Setup function to initialize GPIOs, start serial communication, and configure MQTT
void setup() {
  pinMode(ledPin, OUTPUT);
  dht.begin();
  Serial.begin(9600);  // Changed baud rate to 9600
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

// Main loop to keep the ESP8266 connected to the MQTT broker and publish sensor data
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();

  // Publish temperature and humidity every 5 seconds
  if (now - lastMeasure > 5000) {
    lastMeasure = now;

    float humidity = dht.readHumidity();
    float temperatureC = dht.readTemperature();  // Celsius

    if (isnan(humidity) || isnan(temperatureC)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // Publish sensor data
    client.publish("kainapat/temperature", String(temperatureC).c_str());
    client.publish("kainapat/humidity", String(humidity).c_str());

    Serial.printf("Temperature: %.2f °C\nHumidity: %.2f %%\n", temperatureC, humidity);
    Serial.println();
  }
}