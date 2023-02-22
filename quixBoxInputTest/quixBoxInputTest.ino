//Quiz Box input test. Ben Pacheco 1/18/23
//Define Pins
const int r1b = 27;
const int r2b = 15;
const int r3b = 14;
const int y1b = 36;
const int y2b = 8;
const int y3b = 4;
const int rb = 22;
const int ps = 26;

// Create variable for switches
int r1s = 0;
int r2s = 0;
int r3s = 0;
int y1s = 0;
int y2s = 0;
int y3s = 0;
int rs = 0;
int pss = 0;

void setup() {
  // initialize buttons
  pinMode(r1b, INPUT_PULLUP);
  pinMode(r2b, INPUT_PULLUP);
  pinMode(r3b, INPUT_PULLUP);
  pinMode(y1b, INPUT_PULLUP);
  pinMode(y2b, INPUT_PULLUP);
  pinMode(y3b, INPUT_PULLUP);
  pinMode(rb, INPUT_PULLUP);
  pinMode(ps, INPUT);

  // Inistialize serial connection to read out button
  Serial.begin(9600);
}

void loop() {
  // Read the buttons
 r1s = digitalRead(r1b);
 r2s = digitalRead(r2b);
 r3s = digitalRead(r3b);
 y1s = digitalRead(y1b);
 y2s = digitalRead(y2b);
 y3s = digitalRead(y3b);
 rs  = digitalRead(rb);
 pss = digitalRead(ps);
  // Check if the button is pressed
 if (r1s == 0){
  Serial.println("Red 1 is Pressed!"); //Print that the button is pressed
  while (r1s == 0){    //Wait till button is unpressed
    r1s = digitalRead(r1b);
  }
 }
 if (r2s == 0){
  Serial.println("Red 2 is Pressed!"); //Print that the button is pressed
  while (r2s == 0){    //Wait till button is unpressed
    r2s = digitalRead(r2b);
  }
 }
 if (r3s == 0){
  Serial.println("Red 3 is Pressed!"); //Print that the button is pressed
  while (r3s == 0){    //Wait till button is unpressed
    r3s = digitalRead(r3b);
  }
 }
 if (y1s == 0){
  Serial.println("Yellow 1 is Pressed!"); //Print that the button is pressed
  while (y1s == 0){    //Wait till button is unpressed
    y1s = digitalRead(y1b);
  }
 }
 if (y2s == 0){
  Serial.println("Yellow 2 is Pressed!"); //Print that the button is pressed
  while (y2s == 0){    //Wait till button is unpressed
    y2s = digitalRead(y2b);
  }
 }
 if (y3s == 0){
  Serial.println("Yellow 3 is Pressed!"); //Print that the button is pressed
  while (y3s == 0){    //Wait till button is unpressed
    y3s = digitalRead(y3b);
  }
 }
 if (rs == 0){
  Serial.println("Reader Button is Pressed!"); //Print that the button is pressed
  while (rs == 0){    //Wait till button is unpressed
    rs = digitalRead(rb);
  }
 }
 if (pss == 1){
  Serial.println("Power switch is on!"); //Print that the button is pressed
  while (pss == 1){    //Wait till button is unpressed
    pss = digitalRead(ps);
  }
 }
 delay(1);

}
