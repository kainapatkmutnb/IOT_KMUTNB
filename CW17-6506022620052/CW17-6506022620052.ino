#include <Wire.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include "DHT.h"
#include <BH1750FVI.h>
#include <time.h>

#define DHTPIN D7
#define DHTTYPE DHT22
#define LEDPIN D6  // Pin for LED

char FIREBASE_HOST[] = "fir-dht-2024-default-rtdb.asia-southeast1.firebasedatabase.app";
char FIREBASE_AUTH[] = "6l1u5vjuRUGWY85ZM8iPMw5JVuCr4eqHhmmk95cr";

char WIFI_SSID[] = "309_2.4G";
char WIFI_PASSWORD[] = "3721J8917";

FirebaseData firebaseData;
DHT dht(DHTPIN, DHTTYPE);
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);  // Create BH1750FVI object

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  dht.begin();
  LightSensor.begin();  // Initialize BH1750FVI

  pinMode(LEDPIN, OUTPUT);    // Set LED pin as OUTPUT
  digitalWrite(LEDPIN, LOW);  // Start with LED off

  configTime(7 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  while (!time(nullptr)) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nTime synced!");
}

String getFormattedTime() {
  time_t now = time(nullptr);
  struct tm* timeinfo = localtime(&now);
  char buffer[20];
  strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S", timeinfo);
  return String(buffer);
}

String generateUniqueId() {
  time_t now = time(nullptr);
  struct tm* timeinfo = localtime(&now);
  char buffer[20];
  strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", timeinfo);  // Format: YYYYMMDDHHMMSS
  String id = String(buffer);
  return id;
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float lux = LightSensor.GetLightIntensity();  // Read light level in lux

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    String timestamp = getFormattedTime();
    String logId = generateUniqueId();
    String logPath = "/logs/" + logId;  // Create a new log path

    // Send data to Firebase
    if (Firebase.setFloat(firebaseData, logPath + "/temperature", temperature)) {
      Serial.println("Temperature data sent successfully.");
    } else {
      Serial.print("Error sending temperature: ");
      Serial.println(firebaseData.errorReason());
    }

    if (Firebase.setFloat(firebaseData, logPath + "/humidity", humidity)) {
      Serial.println("Humidity data sent successfully.");
    } else {
      Serial.print("Error sending humidity: ");
      Serial.println(firebaseData.errorReason());
    }

    // Send lux data to Firebase
    if (Firebase.setFloat(firebaseData, logPath + "/lux", lux)) {
      Serial.println("Light data sent successfully.");
    } else {
      Serial.print("Error sending light: ");
      Serial.println(firebaseData.errorReason());
    }

    if (Firebase.setString(firebaseData, logPath + "/time", timestamp)) {
      Serial.println("Timestamp data sent successfully.");
    } else {
      Serial.print("Error sending timestamp: ");
      Serial.println(firebaseData.errorReason());
    }

    // Control LED based on temperature
    if (temperature > 25.0) {                              // If temperature is higher than 25°C
      digitalWrite(LEDPIN, HIGH);                          // Turn on LED
      Firebase.setBool(firebaseData, "/ledStatus", true);  // Update LED status in Firebase
    } else {
      digitalWrite(LEDPIN, LOW);                            // Turn off LED
      Firebase.setBool(firebaseData, "/ledStatus", false);  // Update LED status in Firebase
    }

    // Display data in Serial Monitor
    Serial.println("\n-------------------------------");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");
    Serial.print("Timestamp: ");
    Serial.println(timestamp);

    delay(5000);
  }
}