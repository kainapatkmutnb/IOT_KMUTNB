#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <DHT.h>
#include <time.h>
#include <BH1750.h>
#include <Wire.h>

#define FIREBASE_HOST "fir-dht-2024-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "6l1u5vjuRUGWY85ZM8iPMw5JVuCr4eqHhmmk95cr"

#define WIFI_SSID "309_2.4G"
#define WIFI_PASSWORD "3721J8917"

#define DHTPIN D7
#define DHTTYPE DHT22
#define LEDPIN D6

int timezone = 7;
char ntp_server1[20] = "ntp.ku.ac.th";
char ntp_server2[20] = "fw.eng.ku.ac.th";
char ntp_server3[20] = "time.uni.net.th";
int dst = 0;

DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;
FirebaseData firebaseData;

void setup() {
  Serial.begin(9600);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  Wire.begin();
  lightMeter.begin();

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("...");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  configTime(timezone * 3600, dst, ntp_server1, ntp_server2, ntp_server3);
  Serial.println("Waiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Now: " + NowString());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true); // Reconnect to Wi-Fi automatically
  dht.begin();
}

void loop() {
  // Read temp & Humidity for DHT22
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float lux = lightMeter.readLightLevel();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(500);
    return;
  }

  // Print a line separator before logging data
  Serial.println("-----------------------------------------------------------------");

  // Create a path to log data in Firebase
  String logPath = "/logDHT/" + generateUniqueId();
  
  // Send temperature to Firebase
  if (Firebase.setFloat(firebaseData, logPath + "/temperature", t)) {
    Serial.println("Temperature logged successfully.");
  } else {
    Serial.println("Failed to log temperature: " + firebaseData.errorReason());
  }

  // Send humidity to Firebase
  if (Firebase.setFloat(firebaseData, logPath + "/humidity", h)) {
    Serial.println("Humidity logged successfully.");
  } else {
    Serial.println("Failed to log humidity: " + firebaseData.errorReason());
  }

  // Send light intensity to Firebase
  if (Firebase.setFloat(firebaseData, logPath + "/light", lux)) {
    Serial.println("Light logged successfully.");
  } else {
    Serial.println("Failed to log light: " + firebaseData.errorReason());
  }

  // Send timestamp to Firebase
  if (Firebase.setString(firebaseData, logPath + "/time", NowString())) {
    Serial.println("Timestamp logged successfully.");
  } else {
    Serial.println("Failed to log timestamp: " + firebaseData.errorReason());
  }

  // Print sensor readings in a formatted way
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C\t");
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");

  // Print a line separator after logging data
  Serial.println("-----------------------------------------------------------------");

  delay(10000); // Delay before next reading
}

String NowString() {
  time_t now = time(nullptr);
  struct tm* newtime = localtime(&now);
  
  String tmpNow = "";
  tmpNow += String(newtime->tm_year + 1900);
  tmpNow += "-";
  tmpNow += String(newtime->tm_mon + 1);
  tmpNow += "-";
  tmpNow += String(newtime->tm_mday);
  tmpNow += " ";
  tmpNow += String(newtime->tm_hour);
  tmpNow += ":";
  tmpNow += String(newtime->tm_min);
  tmpNow += ":";
  tmpNow += String(newtime->tm_sec);
  return tmpNow;
}

String generateUniqueId() {
  time_t now = time(nullptr);
  struct tm* timeinfo = localtime(&now);
  char buffer[20];
  strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", timeinfo);  // Format: YYYYMMDDHHMMSS
  String id = String(buffer);
  return id;
}