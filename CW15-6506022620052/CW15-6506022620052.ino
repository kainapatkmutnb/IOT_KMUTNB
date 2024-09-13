#include <TridentTD_LineNotify.h>
#include <DHT.h>
#include <ESP8266WiFi.h>

#define SSID        "B415"
#define PASSWORD    "appletv415"
#define LINE_TOKEN  "cBvBhcnRssd9dd7l3WyQeRWvbKgoGUoAHalG8VArUrH"

#define DHTPIN D7 
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

unsigned long previousMillis = 0;
const long interval = 120000;  

void setup() {
  Serial.begin(9600);
  dht.begin();  

  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n", SSID);
  while(WiFi.status() != WL_CONNECTED) { 
    Serial.print("."); 
    delay(400); 
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  

  LINE.setToken(LINE_TOKEN);  
}

void loop() {
  unsigned long currentMillis = millis();  

  float humidity = dht.readHumidity();  

  
  Serial.print("Current Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  if (humidity > 90) {
    if (currentMillis - previousMillis >= interval) {  
      previousMillis = currentMillis;  
      String message = "แจ้งเตือน: ความชื้นเกิน 90% (" + String(humidity) + "%)";
      
      
      LINE.notify(message);

      
      Serial.println("Notification sent to LINE.");
    } else {
      
      Serial.println("Humidity exceeds 90%, but waiting for interval to pass.");
    }
  } else {
    
    Serial.println("Humidity is within normal range.");
  }
  
  delay(5000);  
}