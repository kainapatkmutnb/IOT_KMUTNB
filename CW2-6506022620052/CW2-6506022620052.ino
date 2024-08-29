#include "DHT.h"

#define DHTPIN 7
#define DHTTYPE DHT22

const int greenLED = 13;
const int yellowLED = 12;
const int redLED = 11;
int count = 0;
float lastTemp = 0.0;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

void blinkLED(int pin) {
  digitalWrite(pin, HIGH);
  delay(700);
  digitalWrite(pin, LOW);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  if (count == 0) {
    blinkLED(greenLED);
    blinkLED(yellowLED);
    blinkLED(redLED);
  } else {
    if (t > lastTemp) {
      blinkLED(greenLED);
      blinkLED(yellowLED);
      blinkLED(redLED);
    } else {
      blinkLED(redLED);
      blinkLED(yellowLED);
      blinkLED(greenLED);
    }
  }

  lastTemp = t;
  count++;
  delay(5000);
}