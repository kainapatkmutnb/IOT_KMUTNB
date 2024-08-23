#define ledPin D7
#define pirPin 12 // Input for HC-S501

int pirValue = 0; // Place to store read PIR Value
int motionDetected = 0;

void getPirValue(void);

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  getPirValue();
  delay(3000);
}

void getPirValue(void) {
  pirValue = digitalRead(pirPin);

  if (pirValue) {
    Serial.print("Motion Detected, PIR Value: ");
  } else {
    Serial.print("No Motion, PIR Value: ");
  }

  Serial.println(pirValue);

  digitalWrite(ledPin, pirValue);
}