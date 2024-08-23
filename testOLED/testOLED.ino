#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 16
Adafruit_SSD1306 display(OLED_RESET);
int value;
void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //สั่งให้จอ OLED เริ่มทำงานที่ Address 0x3C
  display.clearDisplay(); // ลบภาพในหน้าจอทั้งหมด
  display.setTextSize(1); // กำหนดขนาดตัวอักษร
  display.setTextColor(WHITE);
  display.setCursor(0,0); // กำหนดตำแหน่ง x,y ที่จะแสดงผล
  display.println(" KMUTNB ");
  display.setCursor(0,10);
  display.setTextSize(2);
  display.setTextColor(BLACK, WHITE); //กำหนดข้อความสีขาว ฉากหลังสีดำ
  display.println(" Myarduino");
  display.setCursor(0,32);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("128 x 64 Pixels 0.96");
  display.setCursor(0,48);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(" www.myarduino.net "); // แสดงผลข้อความ www.Myarduino.net
  display.display();
}
void loop() {

  val = analogRead(A0) ;

  Serial.print("Analog Value = ");
  Serial.println(val);


  display.clearDisplay(); // ลบภาพในหน้าจอทั้งหมด
  display.setTextSize(1); // กำหนดขนาดตัวอักษร
  display.setTextColor(WHITE);

  display.setCursor(0,0); // 
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(" Analog Value ");

  display.setCursor(0,32);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(val);

  delay(1000);
  
}
