#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1 
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int analogInPin = A0;  
const int analogOutPin = 9; 

int sensorValue = 0;  
int outputValue = 0;  

void setup() {
  Serial.begin(9600);
  
  if (!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
  } else {
    Serial.println("KMUTNB Start Work !!!");
  }
}

void loop() {
  sensorValue = analogRead(analogInPin);
  outputValue = map(sensorValue, 13, 1024, 0, 255);
  analogWrite(analogOutPin, outputValue);

  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  OLED.clearDisplay();
  OLED.setTextColor(WHITE, BLACK);  
  OLED.setCursor(0, 0); 
  OLED.setTextSize(2); 
  OLED.println("KMUTNB");

  OLED.setTextSize(1);
  OLED.print("Analog Value:");
  OLED.setCursor(0, 32); 
  OLED.setTextSize(2); 
  OLED.println(sensorValue);
  
  OLED.setCursor(0, 50);
  OLED.setTextSize(2);
  OLED.print("Output:");
  OLED.println(outputValue);
  
  OLED.display(); 

  delay(1000);
}
