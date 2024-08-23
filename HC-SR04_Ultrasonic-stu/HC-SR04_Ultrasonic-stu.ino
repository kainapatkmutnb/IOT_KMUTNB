int trig = D2;
int echo = D1;

float duration;
int distance;
float height;
int door_Height = 200;

void setup() 
{
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() 
{
  digitalWrite(trig, LOW);        
  delayMicroseconds(2);              
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);           
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = (duration / 2) / 29.1;
  height = door_Height - distance;

  float heightInches = height * 0.393701;
  int feet = int(heightInches) / 12;
  int inches = int(heightInches) % 12;
  float heightCm = feet * 30.48 + inches * 2.54;

  Serial.print("ฟุตและนิ้ว: ");
  Serial.print(feet);
  Serial.print("' ");
  Serial.print(inches);
  Serial.println("\"");
  Serial.print("เซนติเมตร: ");
  Serial.print(heightCm, 2);
  Serial.println(" cm");

  delay(1000); 
}
