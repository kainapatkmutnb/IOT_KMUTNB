#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define SCREEN_WIDTH 128 // ความกว้างของจอ OLED
#define SCREEN_HEIGHT 64 // ความสูงของจอ OLED

// ประกาศสำหรับจอ SSD1306 ที่เชื่อมต่อกับ I2C
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN D7     // ขาดิจิตอลที่เชื่อมต่อกับ DHT sensor

// เลือกชนิดของเซ็นเซอร์ที่ใช้งาน:
#define DHTTYPE    DHT22     // DHT 22 (AM2302)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  dht.begin();

  // ตรวจสอบการเชื่อมต่อจอ OLED
  if (!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
}

void loop() {
  delay(5000);

  // อ่านค่าอุณหภูมิและความชื้น
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // ล้างหน้าจอ
  OLED.clearDisplay();

  // แสดงค่าอุณหภูมิ
  OLED.setTextSize(1);
  OLED.setCursor(0, 0);
  OLED.print("Temperature: ");
  OLED.setTextSize(2);
  OLED.setCursor(0, 10);
  OLED.print(t);
  OLED.print(" ");
  OLED.setTextSize(1);
  OLED.cp437(true);
  OLED.write(167); // แสดงสัญลักษณ์องศา
  OLED.setTextSize(2);
  OLED.print("C");
  
  // แสดงค่าความชื้น
  OLED.setTextSize(1);
  OLED.setCursor(0, 35);
  OLED.print("Humidity: ");
  OLED.setTextSize(2);
  OLED.setCursor(0, 45);
  OLED.print(h);
  OLED.print(" %"); 
  
  OLED.display();
}
