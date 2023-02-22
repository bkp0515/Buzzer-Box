//Quiz box test sequence. Ben Pacheco 7/28/22
//Define buzzer pins
const int b1 = 13;//Works
const int b2 = 12;//works
//Define led pins
const int y1l = 21;
const int y2l = 7;
const int y3l = 5;
const int r1l = 33;
const int r2l = 32;
const int r3l = 20;


void setup() {
  //Set led pins to output
  pinMode(y1l, OUTPUT);
  pinMode(y2l, OUTPUT);
  pinMode(y3l, OUTPUT);
  pinMode(r1l, OUTPUT);
  pinMode(r2l, OUTPUT);
  pinMode(r3l, OUTPUT);

}

void loop() {
  //Turn on the LEDs one at a time
  digitalWrite(y1l, HIGH);
  delay(500);
  digitalWrite(y2l, HIGH);
  delay(500);
  digitalWrite(y3l, HIGH);
  delay(500);
  digitalWrite(r1l, HIGH);
  delay(500);
  digitalWrite(r2l, HIGH);
  delay(500);
  digitalWrite(r3l, HIGH);
  delay(1500);
  digitalWrite(y1l, LOW);
  delay(500);
  digitalWrite(y2l, LOW);
  delay(500);
  digitalWrite(y3l, LOW);
  delay(500);
  digitalWrite(r1l, LOW);
  delay(500);
  digitalWrite(r2l, LOW);
  delay(500);
  digitalWrite(r3l, LOW);
  delay(500);
  tone(b1, 1000, 500);
  delay(500);
  tone(b2, 1000, 500);
  delay(500);
}
