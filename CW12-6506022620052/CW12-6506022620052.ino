#define BLYNK_TEMPLATE_ID "TMPL6zTPnuNWY"
#define BLYNK_TEMPLATE_NAME "BH1750"
#define BLYNK_AUTH_TOKEN "Q1H_nOA96TlstFUY-rMOICPeb1oRX-qG"

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BlynkSimpleEsp8266.h> // Include the Blynk library
#include <ESP8266WiFi.h> // Include the ESP8266 WiFi library

#define OLED_RESET -1
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


const char* ssid = "B415";
const char* password = "appletv415";


#define LIGHT_VPIN V0

int BH1750address = 0x23;
byte buff[2];

void setup() {
  
  Serial.begin(9600);

  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  
  if (!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  
  
  OLED.setTextSize(1);
  OLED.setCursor(0, 0);
  OLED.println(F("BH1750 Light Meter"));
  
  OLED.setTextSize(2);
  OLED.setCursor(0, 16);
  OLED.print(F("Light: "));
  
  OLED.display();
  
  BH1750_Init(BH1750address);
}

void loop() {
  uint16_t val = 0;
  delay(200);
  
  if (BH1750_Read(BH1750address) == 2) {
    val = ((buff[0] << 8) | buff[1]) / 1.2;
    
    
    OLED.clearDisplay();
    OLED.setTextSize(1);
    OLED.setCursor(0, 0);
    OLED.println(F("BH1750 Light Meter"));
    
    OLED.setTextSize(1);
    OLED.setCursor(0, 16);
    OLED.print(F("Light: "));
    OLED.print(val);
    OLED.print(F(" lx"));
    
    OLED.display();
    
    
    Serial.println(String(val) + " lx");
    
    
    Blynk.virtualWrite(LIGHT_VPIN, val);
  }
  
  Blynk.run(); 
  delay(150);
}

int BH1750_Read(int address) {
  int i = 0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  
  while (Wire.available()) {
    buff[i] = Wire.read();
    i++;
  }
  
  Wire.endTransmission();
  return i;
}

void BH1750_Init(int address) {
  Wire.beginTransmission(address);
  Wire.write(0x10); 
  Wire.endTransmission();
}
