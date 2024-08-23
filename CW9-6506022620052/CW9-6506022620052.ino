#include <ESP8266WiFi.h>
#include "AXWIFI.h"

const char* ssid = "kainapxt";
const char* password = "22223333";

int greenLED = D7;
int yellowLED = D6;
int redLED = D5;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.begin();  // Starts the Server
  Serial.println("Server started");
  Serial.print("IP Address of network: ");
  Serial.println(WiFi.localIP());
  Serial.print("Copy and paste the following URL: http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  while (!client.available()) {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  client.flush();

  int greenValue = LOW;
  int yellowValue = LOW;
  int redValue = LOW;

  if (request.indexOf("/GREENLED=ON") != -1) {
    digitalWrite(greenLED, HIGH); 
    greenValue = HIGH;
  }
  if (request.indexOf("/GREENLED=OFF") != -1) {
    digitalWrite(greenLED, LOW);  
    greenValue = LOW;
  }
  if (request.indexOf("/YELLOWLED=ON") != -1) {
    digitalWrite(yellowLED, HIGH);  
    yellowValue = HIGH;
  }
  if (request.indexOf("/YELLOWLED=OFF") != -1) {
    digitalWrite(yellowLED, LOW);  
    yellowValue = LOW;
  }
  if (request.indexOf("/REDLED=ON") != -1) {
    digitalWrite(redLED, HIGH);  
    redValue = HIGH;
  }
  if (request.indexOf("/REDLED=OFF") != -1) {
    digitalWrite(redLED, LOW);  
    redValue = LOW;
  }

  //*------------------HTML Page Code---------------------*//

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html; charset=UTF-8");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta charset=\"UTF-8\">");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
  client.println("<title>CW9 : Web Server Control 3 LED</title>");
  client.println("<style>");
  client.println("body { font-size: 16px; font-family: 'Arial', sans-serif; background-color: #f4f4f4; color: #333; margin: 0; padding: 0; }");
  client.println(".container { display: flex; flex-direction: column; align-items: center; justify-content: center; min-height: 100vh; padding: 20px; }");
  client.println("h1 { color: #333; font-size: 24px; margin-bottom: 20px; }");
  client.println("img { width: 100%; height: auto; max-width: 600px; border-radius: 15px; box-shadow: 0 4px 8px rgba(0,0,0,0.2); margin-bottom: 20px; }");
  client.println(".controls { display: flex; flex-direction: column; align-items: center; gap: 10px; }");
  client.println(".btn-4 { background-color: #000; color: #fff; font-size: 16px; padding: 10px 20px; border: 2px solid #fff; border-radius: 50px; cursor: pointer; transition: background-color 0.3s ease; text-transform: uppercase; }");
  client.println(".btn-4:hover { background-color: #333; }");
  client.println(".status { font-size: 18px; margin-bottom: 20px; }");
  client.println("@media (max-width: 600px) {");
  client.println("  body { font-size: 14px; }");
  client.println("  .btn-4 { font-size: 14px; padding: 8px 16px; }");
  client.println("  img { width: 90%; }");
  client.println("}");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");

  client.println("<div class=\"container\">");
  client.println("<h1>กายณภัทร สุวรรณโชติ</h1>");
  client.println("<img src=\"https://scontent-bkk1-2.xx.fbcdn.net/v/t39.30808-6/369867322_3591864757736320_4207498372721926902_n.jpg?_nc_cat=106&ccb=1-7&_nc_sid=a5f93a&_nc_eui2=AeE3TlN5Uvnwsrrd1TWDzfnlUh4uUU9waZxSHi5RT3BpnOnYawiiDxy6cqtIhpWBZddoOyxKrcwAZzT-1BhphCK-&_nc_ohc=5R4RSYaY9mcQ7kNvgHWawnQ&_nc_ht=scontent-bkk1-2.xx&oh=00_AYC2xbdp3crQATu5hs8HRquR_fSgF0ADn39OOVNqO2ncWw&oe=66B2284D\" alt=\"Image\">");
  client.println("<div class=\"status\">");
  client.print("Green LED is ");
  client.print(greenValue == HIGH ? "<span style='color: #28a745;'>ON</span>" : "<span style='color: #dc3545;'>OFF</span>");
  client.println("<br>");
  
  client.print("Yellow LED is ");
  client.print(yellowValue == HIGH ? "<span style='color: #ffc107;'>ON</span>" : "<span style='color: #dc3545;'>OFF</span>");
  client.println("<br>");
  
  client.print("Red LED is ");
  client.print(redValue == HIGH ? "<span style='color: #dc3545;'>ON</span>" : "<span style='color: #dc3545;'>OFF</span>");
  client.println("<br>");
  client.println("</div>");

  client.println("<div class=\"controls\">");
  client.println("<a href=\"/GREENLED=ON\"><button class=\"btn-4\">Turn Green ON</button></a>");
  client.println("<a href=\"/GREENLED=OFF\"><button class=\"btn-4\">Turn Green OFF</button></a><br>");
  
  client.println("<a href=\"/YELLOWLED=ON\"><button class=\"btn-4\">Turn Yellow ON</button></a>");
  client.println("<a href=\"/YELLOWLED=OFF\"><button class=\"btn-4\">Turn Yellow OFF</button></a><br>");
  
  client.println("<a href=\"/REDLED=ON\"><button class=\"btn-4\">Turn Red ON</button></a>");
  client.println("<a href=\"/REDLED=OFF\"><button class=\"btn-4\">Turn Red OFF</button></a><br>");
  
  client.println("</div>");
  client.println("</div>");
  client.println("</body>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
