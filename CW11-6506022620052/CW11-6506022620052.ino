#define BLYNK_TEMPLATE_ID "TMPL6GqdGPO9y"
#define BLYNK_TEMPLATE_NAME "newDHT"
#define BLYNK_AUTH_TOKEN "Cs8Q5nuOmFqsOF7CqcScVzJ8mu1egVuk"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

const char* ssid = "B415";
const char* password = "appletv415";

#define DHTPIN D6
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const int ledPin = D7;

BlynkTimer timer;

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  
  dht.begin();
  pinMode(ledPin, OUTPUT);
  
  timer.setInterval(10000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}

void sendSensorData() {
  float humidity = readHumidity();
  float temperature = readTemperature();
  
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  sendToBlynk(temperature, humidity);
  controlLED(temperature);
  printToSerial(temperature, humidity);
}

float readHumidity() {
  return dht.readHumidity();
}

float readTemperature() {
  return dht.readTemperature();
}

void sendToBlynk(float temperature, float humidity) {
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
}

void controlLED(float temperature) {
  if (temperature > 25) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void printToSerial(float temperature, float humidity) {
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\t");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}
