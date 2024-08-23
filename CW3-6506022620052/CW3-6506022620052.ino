const int buttonPin = D0;    
const int greenLED = D4;    
const int yellowLED = D5;   
const int redLED = D6;      

int pressCount = 0;        

void setup() {
  Serial.begin(9600);
  
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);
}

void loop() {
  int sensorVal = digitalRead(buttonPin);
  if (sensorVal == LOW) { 
    pressCount++; 
    Serial.print("กดสวิตซ์ ");
    Serial.print(pressCount);
    Serial.println(" ครั้ง");
    if (pressCount >= 40) {
      digitalWrite(greenLED, HIGH);
      digitalWrite(yellowLED, HIGH);
      digitalWrite(redLED, HIGH);
    } else if (pressCount >= 30) {
      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, HIGH);
    } else if (pressCount >= 20) {
      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, HIGH);
      digitalWrite(redLED, LOW);
    } else if (pressCount >= 10) {
      digitalWrite(greenLED, HIGH);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, LOW);
    } else {
      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, LOW);
    }
    delay(200);
    if (pressCount >= 40) {
      pressCount = 0;
    }
  }
}