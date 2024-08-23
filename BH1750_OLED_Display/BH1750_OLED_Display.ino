#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET -1
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int BH1750address = 0x23;
byte buff[2];

void setup() {
  Wire.begin();
  
  Serial.begin(9600); // Initialize serial communication
  
  if (!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Initialize the OLED
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  
  // Display title and subtitle
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
    
    // Display on OLED
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
    
    // Show value in Serial Monitor
    Serial.println(String(val) + " lx");
  }
  
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
  Wire.write(0x10); // Continuously H-Resolution Mode
  Wire.endTransmission();
}