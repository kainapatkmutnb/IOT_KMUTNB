#include <ESP8266WiFi.h>
#include <espnow.h>

#define LED1 D7
#define LED2 D6
#define LED3 D5

#define LED_OFF LOW
#define LED_ON  HIGH

typedef struct struct_message {
  bool SW1;
  bool SW2;
} struct_message;

struct_message myData;

void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("SW1: ");
  Serial.println(myData.SW1 ? "ON" : "OFF");
  Serial.print("SW2: ");
  Serial.println(myData.SW2 ? "ON" : "OFF");
  Serial.println();

  // Initial LED control based on SW1 and SW2 status
  digitalWrite(LED1, myData.SW1 ? LED_ON : LED_OFF);
  digitalWrite(LED2, myData.SW2 ? LED_ON : LED_OFF);

  // If both SW1 and SW2 are pressed, override LED control
  if (myData.SW1 && myData.SW2) {
    digitalWrite(LED1, LED_OFF);
    digitalWrite(LED2, LED_OFF);
    digitalWrite(LED3, LED_ON);
  } else {
    // If not both are pressed, turn off LED3
    digitalWrite(LED3, LED_OFF);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // No need to do anything in loop, everything is handled in OnDataRecv
}
