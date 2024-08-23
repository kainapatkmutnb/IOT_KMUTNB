#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


const char* ssid = "kainapxt";
const char* password = "22223333";


WiFiClient client;
unsigned long myChannelNumber = 2614695;
const char* myWriteAPIKey = "SY28XK72IQO4MOB0";


#define DHTPIN D7
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);


unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

int num1;
String myStatus = "";

void setup() {
  Serial.begin(9600); 
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  dht.begin(); 
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {  
    if (WiFi.status() != WL_CONNECTED) {     
      Serial.print("Attempting To Connect");
      while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, password);
        delay(5000);
      }
      Serial.println("\nConnected."); 
    }

   
    num1 = random(10, 90);
    Serial.print("Random Number = ");
    Serial.println(num1);

    
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print("%  Temperature: ");
    Serial.print(t);
    Serial.println("°C");

    ThingSpeak.setField(1, num1); 
    ThingSpeak.setField(2, t); 
    ThingSpeak.setField(3, h); 
    ThingSpeak.setStatus(myStatus);
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if (x == 200) {
      Serial.println("Channel update successful.");
    } else {
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }

    lastTime = millis();
  }
}
