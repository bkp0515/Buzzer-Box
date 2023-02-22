// Quiz Box Mk. 3 Ben Pacheco 2/16/23
// Updated 2/21/23
////////////////////////////////////////////////////////////////////////////////////////////
// Library includes
#include <Adafruit_NeoPixel.h>
#include "driver/rtc_io.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

////////////////////////////////////////////////////////////////////////////////////////////
// Sleep function setup stuff
////////////////////////////////////////////////////////////////////////////////////////////

#define BUTTON_PIN_BITMASK 0x004000000 // 2^26 in hex define power switch pin
#define ps    26 // Power switch pin define

////////////////////////////////////////////////////////////////////////////////////////////
// End sleep function stuff
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
// Neopixel Setup Stuff
////////////////////////////////////////////////////////////////////////////////////////////

#define neoPIN    19 //Set pin for neopixels
#define NUMPIXELS 8  //Set number of neopixels

// Input the neopixel variables
Adafruit_NeoPixel pixels(NUMPIXELS, neoPIN, NEO_GRB + NEO_KHZ800);

////////////////////////////////////////////////////////////////////////////////////////////
// End Neopixel Setup
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
// Timer Setup
////////////////////////////////////////////////////////////////////////////////////////////
// Timer variables
volatile uint8_t isrCounter = 0;
volatile bool timerOn = false;
uint8_t pixelsOn = 0;

// Setup timer
hw_timer_t * timer = NULL;
hw_timer_t * speedTimer = NULL;

////////////////////////////////////////////////////////////////////////////////////////////
// End timer setup
////////////////////////////////////////////////////////////////////////////////////////////

// Define pins
#define b1    13 // Buzzer 1 (passive buzzer)
#define b2    12 // Buzzer 2 (active buzzer)
#define r1p   14 // Red 1 buzzer pin
#define r2p   15 // Red 2 buzzer pin
#define r3p   27 // Red 3 buzzer pin
#define y1p   4  // Yellow 1 buzzer pin
#define y2p   8  // Yellow 2 buzzer pin
#define y3p   36 // Yellow 3 buzzer pin
#define rp    22 // Reader pin

#define r1l   33 //Red 1 LED
#define r2l   32 //Red 2 LED
#define r3l   20 //Red 3 LED
#define y1l   21 //Yellow 1 LED
#define y2l   7  //Yellow 2 LED
#define y3l   5  //Yellow 3 LED


// Buzzer definition 
struct Buzzer {
  const uint8_t PIN; // 
  volatile uint64_t SPEED;
  bool pressed;
};

// Define buzzers
Buzzer handle1 = {r1p, 0, false};
Buzzer handle2 = {r2p, 0, false};
Buzzer handle3 = {r3p, 0, false};
Buzzer handle4 = {y1p, 0, false};
Buzzer handle5 = {y2p, 0, false};
Buzzer handle6 = {y3p, 0, false};
Buzzer handle7 = {rp , 0, false};

// Buzzer interrupt variables
volatile bool buzzed = false;
volatile uint8_t first = 0;

////////////////////////////////////////////////////////////////////////////////////////////
// Buzzer Interrupts
////////////////////////////////////////////////////////////////////////////////////////////
void ARDUINO_ISR_ATTR isrH1() { // Red 1
  if (!buzzed) {
    handle1.pressed = true;
    buzzed = true;
    first = 1;
    timerWrite(speedTimer, 0);
    timerStart(speedTimer);
  } else {
    handle1.SPEED = timerRead(speedTimer);
  }
}


void ARDUINO_ISR_ATTR isrH2() { // Red 2
  if (!buzzed) {
    handle2.pressed = true;
    buzzed = true;
    first = 2;
    timerWrite(speedTimer, 0);
    timerStart(speedTimer);
  } else {
    handle2.SPEED = timerRead(speedTimer);
  }
}

void ARDUINO_ISR_ATTR isrH3() { // Red 3
  if (!buzzed) {
    handle3.pressed = true;
    buzzed = true;
    first = 3;
    timerWrite(speedTimer, 0);
    timerStart(speedTimer);
  } else {
    handle3.SPEED = timerRead(speedTimer);
  }
}

void ARDUINO_ISR_ATTR isrH4() { // Yellow 1
  if (!buzzed) {
    handle4.pressed = true;
    buzzed = true;
    first = 4;
    timerWrite(speedTimer, 0);
    timerStart(speedTimer);
  } else {
    handle4.SPEED = timerRead(speedTimer);
  }
}

void ARDUINO_ISR_ATTR isrH5() { // Yellow 2
  if (!buzzed) {
    handle5.pressed = true;
    buzzed = true;
    first = 5;
    timerWrite(speedTimer, 0);
    timerStart(speedTimer);
  } else {
    handle5.SPEED = timerRead(speedTimer);
  }
}

void ARDUINO_ISR_ATTR isrH6() { // Yellow 3
  if (!buzzed) {
    handle6.pressed = true;
    buzzed = true;
    first = 6;
    timerWrite(speedTimer, 0);
    timerStart(speedTimer);
  } else {
    handle6.SPEED = timerRead(speedTimer);
  }
}

void ARDUINO_ISR_ATTR isrH7() { // Clear Handle
  if (!buzzed) {
    handle7.pressed = true;
    buzzed = true;
    first = 7;
    timerWrite(speedTimer, 0);
    timerStart(speedTimer);
  } else {
    handle7.SPEED = timerRead(speedTimer);
  }
}
////////////////////////////////////////////////////////////////////////////////////////
// Speed timer reset
////////////////////////////////////////////////////////////////////////////////////////

void ARDUINO_ISR_ATTR speedTimerInt() {
  timerStop(speedTimer); // Stop the speed timer upon interrupt
}



////////////////////////////////////////////////////////////////////////////////////////////
// Timer Function Stuff
////////////////////////////////////////////////////////////////////////////////////////////

// Timer interrupt function
void ARDUINO_ISR_ATTR onTimer() {
  if (isrCounter > 0) { // Check the number of times the ISR has been called

    isrCounter--;
  }
}

// Start timer function
void startTimer(uint8_t timeLenght, uint32_t color) { // Call to start a timer
  if (timerOn == false){ // Check if a timer is already started
    
    // Set all the pixels to the defined color
    for(int j = 0; j<pixels.numPixels(); j++){ 
      pixels.setPixelColor(j, color);
      pixels.show();
    } // End for

    // Configure timer
    timerOn = true; // Set flag to show a timer is running
    timerAlarmWrite(timer, (timeLenght * 1000000 / NUMPIXELS), true); // Set the interrupt lenght of the timer
    timerRestart(timer); // Start the timer from 0
    timerStart(timer);
    timerAlarmEnable(timer); // Allow timer interupt
    isrCounter = NUMPIXELS; // Set the counter to the number of pixels to begin countdown
    pixelsOn = NUMPIXELS; // Set the number of pixels currently on
    
  } // end if
  
} // end function

///////////////////////////////////////////////////////////////////////////////////////////
// End Timer Function Stuff
///////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
// Main Setup and Script
////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  // Configure power switch
  rtc_gpio_pullup_dis(GPIO_NUM_26);
  rtc_gpio_pulldown_en(GPIO_NUM_26);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_26,1);
  
  // Start the neopixels
  pixels.begin();
  // initialize buttons
  pinMode(r1p, INPUT_PULLUP);
  pinMode(r2p, INPUT_PULLUP);
  pinMode(r3p, INPUT_PULLUP);
  pinMode(y1p, INPUT_PULLUP);
  pinMode(y2p, INPUT_PULLUP);
  pinMode(y3p, INPUT_PULLUP);
  pinMode(rp,  INPUT_PULLUP);
  // Initalize LEDs
  pinMode(y1l, OUTPUT);
  pinMode(y2l, OUTPUT);
  pinMode(y3l, OUTPUT);
  pinMode(r1l, OUTPUT);
  pinMode(r2l, OUTPUT);
  pinMode(r3l, OUTPUT);
  pinMode(b2,  OUTPUT);

  // Connect interrupts to buzzers
  attachInterrupt(handle1.PIN, isrH1, FALLING);
  attachInterrupt(handle2.PIN, isrH2, FALLING);
  attachInterrupt(handle3.PIN, isrH3, FALLING);
  attachInterrupt(handle4.PIN, isrH4, FALLING);
  attachInterrupt(handle5.PIN, isrH5, FALLING);
  attachInterrupt(handle6.PIN, isrH6, FALLING);
  attachInterrupt(handle7.PIN, isrH7, FALLING);
  
  
  // Play tone to indicate power on
  tone(b1, 1500, 500);
  // Clear the neopixels
  pixels.clear();
  pixels.show();
  
  // Initialize timer 0 and 1 with an 80 prescaler and define autoreload
  timer = timerBegin(0, 80, true);
  speedTimer = timerBegin(1, 80, false);
  // Attach the interrupt function to the timer
  timerAttachInterrupt(timer, &onTimer, true);
  timerAttachInterrupt(speedTimer, &speedTimerInt, false);

  timerAlarmWrite(speedTimer, 5000000, false); // Set the speed timer limit
  
  //startTimer(5, pixels.Color(25, 25, 25));
}

void loop() {
  if (buzzed) {
    buzz(first);
  }
  
}

////////////////////////////////////////////////////////////////////////////////////////////
// End Main Setup and Script
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
// Buzz function
////////////////////////////////////////////////////////////////////////////////////////////

void buzz(uint8_t x) {
  switch(x) {
    case 1 :
      // Red one
      if (!timerOn){
        startTimer(30, pixels.Color(25, 0, 0));// Start the 30 seccond countdown
      } else { 
        if (pixelsOn > isrCounter) { // Check if pixel needs to be turned off
          pixelsOn--;
          pixels.setPixelColor(pixelsOn, pixels.Color(0, 0, 0));
          pixels.show();
        } else if (pixelsOn == 0){
          buzzed = false;
          timerOn = false;
          timerStop(timer);
        }
      }
  }
}
