#include <ESP8266WiFi.h>
#include <espnow.h>
#include "DHT.h"

#define DHTPIN D7
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

uint8_t broadcastAddress[] = {0x68, 0xC6, 0x3A, 0xAC, 0x52, 0xD7};

typedef struct struct_message {
  float temperature;
  float humidity;
} struct_message;

struct_message myData;

unsigned long lastTime = 0;
unsigned long timerDelay = 50;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery Success");
  }
  else{
    Serial.println("Delivery Fail");
  }
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

  dht.begin();

  WiFi.mode(WIFI_STA);
  if(esp_now_init() != 0){
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);

  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
if((millis() - lastTime) > timerDelay) {

    myData.temperature = dht.readTemperature();
    myData.humidity = dht.readHumidity();

    if(isnan(myData.temperature) || isnan(myData.humidity)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

    lastTime = millis();
  }
  delay(1000);
}

