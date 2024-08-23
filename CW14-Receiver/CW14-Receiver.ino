#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define BUTTON_PIN    2  // Define the pin for the button

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

typedef struct struct_message {
  float temperature;
  float humidity;
} struct_message;

struct_message myData;
bool dataReceived = false; // Flag to check if data is received
bool buttonPressed = false;

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);

  Serial.print("Temperature: ");
  Serial.println(myData.temperature);
  Serial.print("Humidity: ");
  Serial.println(myData.humidity);

  dataReceived = true; // Set the flag when data is received
}

void setup() {
  Serial.begin(115200);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("Initializing...");
  display.display();

  // Initialize ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);

  // Initialize button pin
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button pin as input with internal pull-up resistor
}

void loop() {
  bool currentButtonState = digitalRead(BUTTON_PIN) == LOW; // Button pressed when LOW

  if (currentButtonState && !buttonPressed) {
    // Button was just pressed
    buttonPressed = true;

    if (dataReceived) {
      // Clear display and show new data if available
      display.clearDisplay();
      display.setTextSize(1); // Set text size
      display.setTextColor(SSD1306_WHITE); // Set text color
      display.setCursor(0, 0); // Set cursor position
      display.print("Temp: ");
      display.print(myData.temperature);
      display.println(" C");
      display.print("Humidity: ");
      display.print(myData.humidity);
      display.println(" %");
      display.display(); // Update the display with new data

      dataReceived = false; // Reset flag after displaying
    }
  } else if (!currentButtonState && buttonPressed) {
    // Button was just released
    buttonPressed = false;
  }
}