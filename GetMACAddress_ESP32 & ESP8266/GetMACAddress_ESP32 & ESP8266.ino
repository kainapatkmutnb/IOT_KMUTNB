#include <WiFi.h>

void setup()
{
    Serial.begin(9600);
    WiFi.begin(); // เริ่มการเชื่อมต่อ WiFi
    delay(1000);  // รอให้ WiFi เชื่อมต่อ

    // ดึง MAC Address และแสดงบน Serial Monitor
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
}

void loop()
{
    // ไม่มีการทำงานใน loop
}