#include <Wire.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include "DHT.h"
#include <time.h>

#define DHTPIN D7
#define DHTTYPE DHT22
#define LEDPIN D6  // กำหนดพินสำหรับ LED

char FIREBASE_HOST[] = "fir-dht-2024-default-rtdb.asia-southeast1.firebasedatabase.app";
char FIREBASE_AUTH[] = "6l1u5vjuRUGWY85ZM8iPMw5JVuCr4eqHhmmk95cr";

char WIFI_SSID[] = "B415";
char WIFI_PASSWORD[] = "appletv415";

FirebaseData firebaseData;
DHT dht(DHTPIN, DHTTYPE);

int logIndex = 0; // ตัวแปรสำหรับเก็บ index ล่าสุด

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
  
  pinMode(LEDPIN, OUTPUT);  // กำหนดพิน LED เป็น OUTPUT
  digitalWrite(LEDPIN, LOW); // เริ่มต้น LED ปิด
  
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

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    String timestamp = getFormattedTime();
    String logPath = "/logs/" + String(logIndex);  // สร้าง path สำหรับ log ใหม่
    
    // ส่งข้อมูลไปยัง Firebase
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
    
    if (Firebase.setString(firebaseData, logPath + "/time", timestamp)) {
      Serial.println("Timestamp data sent successfully.");
    } else {
      Serial.print("Error sending timestamp: ");
      Serial.println(firebaseData.errorReason());
    }

    // ควบคุมสถานะ LED
    if (temperature > 25.0) { // ถ้าอุณหภูมิสูงกว่า 25°C
      digitalWrite(LEDPIN, HIGH); // เปิด LED
      Firebase.setBool(firebaseData, "/ledStatus", true); // อัปเดตสถานะ LED ใน Firebase
    } else {
      digitalWrite(LEDPIN, LOW); // ปิด LED
      Firebase.setBool(firebaseData, "/ledStatus", false); // อัปเดตสถานะ LED ใน Firebase
    }

    // แสดงข้อมูลใน Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
    Serial.print("Timestamp: ");
    Serial.println(timestamp);
    
    logIndex++; // เพิ่ม index สำหรับ log ถัดไป
    delay(5000);
  }
}