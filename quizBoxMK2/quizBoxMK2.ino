// Quiz Box Mk. 2 Ben Pacheco 9/27/22
// Setup neopixel strip
#include <Adafruit_NeoPixel.h>
#include "driver/rtc_io.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

// Set sleep wake button
#define BUTTON_PIN_BITMASK 0x004000000 // 2^26 in hex

// Setup pins for neopixels
#define neoPIN    19
#define NUMPIXELS 8

// Input the neopixel variables
Adafruit_NeoPixel pixels(NUMPIXELS, neoPIN, NEO_GRB + NEO_KHZ800);

// Define Input pins
const int b1 = 13; //Buzzer 1
const int b2 = 12; //Buzzer 2
const int r1b = 14; //Red 1 buzzer
const int r2b = 15; //Red 2 buzzer
const int r3b = 27; //Red 3 buzzer
const int y1b = 4; //Yellow 1 buzzer
const int y2b = 8; //Yellow 2 buzzer
const int y3b = 36; //Yellow 3 buzzer
const int rb = 22; //Reader handle
const int ps = 26; //Power switch

//Define led pins
const int r1l = 33; //Red 1 LED
const int r2l = 32; //Red 2 LED
const int r3l = 20; //Red 3 LED
const int y1l = 21; //Yellow 1 LED
const int y2l = 7; //Yellow 2 LED
const int y3l = 5; //Yellow 3 LED

// Create variables to store switch states
int r1s = 0;
int r2s = 0;
int r3s = 0;
int y1s = 0;
int y2s = 0;
int y3s = 0;
int rs = 0;
int pss = 0;

// Create variables for storing current time
unsigned long time_now = 0;
unsigned long lastTime = 0;

int z = 7;

void setup() {
  // Configure power switch
  rtc_gpio_pullup_dis(GPIO_NUM_26);
  rtc_gpio_pulldown_en(GPIO_NUM_26);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_26,1);
  // Start the neopixels
  pixels.begin();
  // initialize buttons
  pinMode(r1b, INPUT_PULLUP);
  pinMode(r2b, INPUT_PULLUP);
  pinMode(r3b, INPUT_PULLUP);
  pinMode(y1b, INPUT_PULLUP);
  pinMode(y2b, INPUT_PULLUP);
  pinMode(y3b, INPUT_PULLUP);
  pinMode(rb, INPUT_PULLUP);
  //initalize LEDs
  pinMode(y1l, OUTPUT);
  pinMode(y2l, OUTPUT);
  pinMode(y3l, OUTPUT);
  pinMode(r1l, OUTPUT);
  pinMode(r2l, OUTPUT);
  pinMode(r3l, OUTPUT);
  pinMode(b2, OUTPUT);
  // Play tone to indicate power on
  tone(b1, 1000);
  tone(b1, 1500);
  delay(500);
  noTone(b1);
  noTone(b1);
}

void loop() {
  // Clear neopixels
  pixels.clear();
  pixels.show();
  // Reset the pixel counter
  z = 7;
  // Read all the handels
  r1s = digitalRead(r1b);
  r2s = digitalRead(r2b);
  r3s = digitalRead(r3b);
  y1s = digitalRead(y1b);
  y2s = digitalRead(y2b);
  y3s = digitalRead(y3b);
  rs = digitalRead(rb);
  pss = digitalRead(ps);
  // If statement to check the buzzer states
  if (r1s == LOW){
    buzz(1); // Call buzz function
  } else if (r2s == LOW){
    buzz(2);
  } else if (r3s == LOW){
    buzz(3);
  } else if (pss == LOW){
    esp_deep_sleep_start(); // Put the microcontroller to sleep
  } else if (y1s == LOW){
    buzz(4);
  } else if (y2s == LOW){
    buzz(5);
  } else if (y3s == LOW){
    buzz(6);
  } 
}

void buzz(int x) {
  switch(x) {
    case 1 :
      //Red one
      timerStart(pixels.Color(25, 0, 0)); //Setup and start timer
      digitalWrite(r1l, HIGH); //Turn on red 1 LED
      digitalWrite(b2, HIGH); //Play buzzer tone
      delay(500);
      digitalWrite(b2, LOW);
      while(millis() < time_now + 30000 && rs != 0){ //Check clear and time
        rs = digitalRead(rb); //Update reader handle state
        timer30(); //Check if a pixel needs to be turned off
      }
      tone(b1, 500, 500); //Play tone to indicate end of time
      digitalWrite(r1l, LOW); //Turn off LED
      break;
    case 2 :
      //Red two
      timerStart(pixels.Color(25, 0, 0)); //Setup and start timer
      digitalWrite(r2l, HIGH); //Turn on red 2 LED
      digitalWrite(b2, HIGH); //Play buzzer tone
      delay(500);
      digitalWrite(b2, LOW);
      while(millis() < time_now + 30000 && rs != 0){
        rs = digitalRead(rb); //Update reader handle state
        timer30(); //Check if a pixel needs to be turned off
      }
      tone(b1, 500, 500); //Play tone to indicate end of time
      digitalWrite(r2l, LOW); //Turn off LED
      break;
    case 3 :
      //Red three
      timerStart(pixels.Color(25, 0, 0)); //Setup and start timer
      digitalWrite(r3l, HIGH); //Turn on red 3 LED
      digitalWrite(b2, HIGH); //Play buzzer tone
      delay(500);
      digitalWrite(b2, LOW);
      while(millis() < time_now + 30000 && rs != 0){
        rs = digitalRead(rb); //Update reader handle state
        timer30(); //Check if a pixel needs to be turned off
      }
      tone(b1, 500, 500); //Play tone to indicate end of time
      digitalWrite(r3l, LOW); //Turn off LED
      break;
    case 4 :
      //Yellow one
      timerStart(pixels.Color(25, 25, 0)); //Setup and start timer
      digitalWrite(y1l, HIGH); //Turn on yellow 1 LED
      digitalWrite(b2, HIGH); //Play buzzer tone
      delay(500);
      digitalWrite(b2, LOW);
      while(millis() < time_now + 30000 && rs != 0){
        rs = digitalRead(rb); //Update reader handle state
        timer30(); //Check if a pixel needs to be turned off
      }
      tone(b1, 500, 500); //Play tone to indicate end of time
      digitalWrite(y1l, LOW); //Turn off LED
      break;
    case 5 :
      //Yellow two
      timerStart(pixels.Color(25, 25, 0)); //Setup and start timer
      digitalWrite(y2l, HIGH); //Turn on yellow 2 LED      
      digitalWrite(b2, HIGH); //Play buzzer tone
      delay(500);
      digitalWrite(b2, LOW);
      while(millis() < time_now + 30000 && rs != 0){
        rs = digitalRead(rb); //Update reader handle state
        timer30(); //Check if a pixel needs to be turned off
      }
      tone(b1, 500, 500); //Play tone to indicate end of time
      digitalWrite(y2l, LOW); //Turn off LED
      break;
    case 6 :
      //Yellow three
      timerStart(pixels.Color(25, 25, 0)); //Setup and start timer
      digitalWrite(y3l, HIGH); //Turn on yellow 3 LED
      digitalWrite(12, HIGH); //Play buzzer tone
      delay(500);
      digitalWrite(12, LOW);
      while(millis() < time_now + 30000 && rs != 0){
        rs = digitalRead(rb); //Update reader handle state
        timer30(); //Check if a pixel needs to be turned off
      }
      tone(b1, 500, 500); //Play tone to indicate end of time
      digitalWrite(y3l, LOW); //Turn off LED
      break;
  }
}

void timer30() { //Call this function to check if a pixel needs to be turned off
  if(lastTime + 3750 < millis()){ //Check if 3.75 secconds have passed
    pixels.setPixelColor(z, pixels.Color(0, 0, 0)); //Turn off one pixel
    pixels.show(); //Update pixels to reflect one turned off
    lastTime = millis(); //Update the last time a pixel was turned off
    z--; //Update the pixel number we are on
  }
}

void timerStart(uint32_t color) { //Call this function to start a timer
  time_now = millis(); //Update time_now
  lastTime = millis(); //Update lastTime
  for(int j=0; j<pixels.numPixels(); j++) { // Set all the pixels to the color specified
    pixels.setPixelColor(j, color);
    pixels.show();
  }
}
