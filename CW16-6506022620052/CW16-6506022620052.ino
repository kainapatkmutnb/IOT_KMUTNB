//----------------------------------------Include the NodeMCU ESP8266 Library
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "DHT.h"
//----------------------------------------

//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTTYPE DHT22   // DHT 22 (AM2302), AM2321

const int DHTPin = D7;
#define ON_Board_LED 2  // Defining an On Board LED, used for indicators when the process of connecting to a wifi router

//----------------------------------------WiFi credentials
const char* ssid = "B415"; // SSID of the WiFi network
const char* password = "appletv415"; // WiFi password
//----------------------------------------

//----------------------------------------Host & httpsPort
const char* host = "script.google.com";
const int httpsPort = 443;
//----------------------------------------

// Initialize DHT sensor
DHT dht(DHTPin, DHTTYPE);
WiFiClientSecure client; // Create a WiFiClientSecure object

// Timers auxiliary variables
unsigned long previousMillis = 0; // Store last time measurement was done
const long interval = 3000; // Interval between measurements

String GAS_ID = "AKfycbwG47p7ag7rtdFj3nuHOa6bfuCcWBTnghmi_ZfKcL_yBcwTTN0AXNqmeoRXAhDlzzk-"; // Spreadsheet script ID

//============================================ void setup
void setup() {
  Serial.begin(9600); // Start serial communication
  dht.begin(); // Initialize DHT sensor

  pinMode(ON_Board_LED, OUTPUT); // Set the on-board LED pin as OUTPUT
  digitalWrite(ON_Board_LED, HIGH); // Turn on the LED

  connectToWiFi(); // Connect to WiFi

  client.setInsecure(); // Set insecure mode for SSL
}

// Connect to WiFi
void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  // Blink LED while connecting
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
    Serial.print(".");
  }

  digitalWrite(ON_Board_LED, HIGH); // Turn off the LED once connected
  Serial.println("\nConnected to WiFi!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

//============================================ void loop
void loop() {
  unsigned long currentMillis = millis();

  // Publish new temperature and humidity data every 3 seconds
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    float humidity = dht.readHumidity();
    float temperatureC = dht.readTemperature();
    float temperatureF = dht.readTemperature(true);

    if (isnan(humidity) || isnan(temperatureC) || isnan(temperatureF)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    float heatIndexC = dht.computeHeatIndex(temperatureC, humidity, false);
    String humidityStr = String(humidity, 2);
    String temperatureCStr = String(temperatureC, 2);
    String temperatureFStr = String(temperatureF, 2);
    String heatIndexCStr = String(heatIndexC, 2);

    Serial.print("Humidity: ");
    Serial.print(humidityStr);
    Serial.print(" %\t Temperature: ");
    Serial.print(temperatureCStr);
    Serial.print(" *C ");
    Serial.print(temperatureFStr);
    Serial.print(" *F\t Heat index: ");
    Serial.print(heatIndexCStr);
    Serial.println(" *C");

    sendData(temperatureC, humidity);
  }
}

// Send data to Google Script
void sendData(float temperature, float humidity) {
  Serial.println("==========");
  Serial.print("Connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpsPort)) {
    Serial.println("Connection failed");
    return;
  }

  String url = "/macros/s/" + GAS_ID + "/exec?temp=" + String(temperature, 2) + "&humi=" + String(humidity, 2);
  Serial.print("Requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("Request sent");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("Headers received");
      break;
    }
  }

  String response = client.readStringUntil('\n');
  if (response.startsWith("{\"state\":\"success\"")) {
    Serial.println("Data successfully sent!");
  } else {
    Serial.println("Data send failed");
  }
  Serial.print("Reply: ");
  Serial.println(response);
  Serial.println("Closing connection");
  Serial.println("==========");
}