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
    if (pressCount == 1) {
      digitalWrite(greenLED, HIGH);
      digitalWrite(yellowLED, HIGH);
      digitalWrite(redLED, HIGH);
      Serial.println("LED ON");
    } else if (pressCount == 2) {
      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, LOW);
      Serial.println("LED OFF");
      pressCount = 0;
    } 


    delay(200);
    }
  }
