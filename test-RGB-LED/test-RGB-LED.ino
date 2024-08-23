int R = D5;
int G = D6;
int B = D7;
void setup() {
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  // กำหนด LED ดับ
  analogWrite(R, 0);
  analogWrite(G, 0);
  analogWrite(B, 0);
  delay(500);
  // กำหนด LED สีแดง
  analogWrite(R, 255);
  analogWrite(G, 0);
  analogWrite(B, 0);
  delay(500);
  // กำหนด LED สีเขียว
  analogWrite(R, 0);
  analogWrite(G, 0255);
  analogWrite(B, 0);
  delay(500);
  // กำหนด LED สีน้ำเงิน
  analogWrite(R, 0);
  analogWrite(G, 0);
  analogWrite(B, 255);
  delay(500);
  // กำหนด LED สีขาว
  analogWrite(R, 255);
  analogWrite(G, 255);
  analogWrite(B, 255);
  delay(500);
}
