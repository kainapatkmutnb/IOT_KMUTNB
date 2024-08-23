#include <DHT.h>
#define DHTPIN D4     
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);

int R = D5;
int G = D6;
int B = D7;

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

void loop() {
  float humidity = dht.readHumidity();


  if (isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  
  if (humidity > 70) { // High humidity
    //setColor(255, 0, 0);  // Red
    setColor(0, 0, 255);  // Blue
  } else if (humidity > 40) { // Medium humidity
    //setColor(0, 0, 255);  // Blue
    setColor(0, 255, 0);  // Green
  } else { // Low humidity
    //setColor(0, 255, 0);  // Green
    setColor(255, 0, 0);  // Red
  }

  delay(1000);
}

void setColor(int red, int green, int blue) {
  analogWrite(R, red);
  analogWrite(G, green);
  analogWrite(B, blue);
}
