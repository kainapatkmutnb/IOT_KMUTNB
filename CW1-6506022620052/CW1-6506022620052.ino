const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = D5;  // Analog output pin that the LED is attached to

int sensorValue = 0;  // value read from the pot
int outputValue = 0;  // value output to the PWM (analog out)

void setup() {
  Serial.begin(9600);
  pinMode(analogOutPin, OUTPUT);
}

void loop() {
  sensorValue = analogRead(analogInPin);
  Serial.print("Analog Input = ");
  Serial.println(sensorValue);
  
  if (sensorValue > 500) {
    digitalWrite(analogOutPin, HIGH); 
  } else {
    digitalWrite(analogOutPin, LOW);  
  }
  delay(1000); 
  
}
