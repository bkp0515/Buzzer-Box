// QuizBox Lite. Ben Pacheco 7/29/22
// Updated 1/21/23 by Ben Pacheco
// Setup neopixel strip
#include <Adafruit_NeoPixel.h>
#include "driver/rtc_io.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Set sleep wake button
#define BUTTON_PIN_BITMASK 0x004000000 // 2^26 in hex

// Setup pins for neopixels
#define neoPIN       19
#define NUMPIXELS 8

// Input the neopixel variables
Adafruit_NeoPixel pixels(NUMPIXELS, neoPIN, NEO_GRB + NEO_KHZ800);

// Set pins
const int b1 = 13;
const int b2 = 12;
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
// Create a structure for the clear handle. Stores info like what pin its on.
struct clr {
  const uint8_t clearPin; // Create a variable for the pin
  bool pressed; // Create a boolian to store weather the button is pressed.
};

clr clr1 = {22, false}; // Create the reader handle object

void IRAM_ATTR isr() { // Function for clearing the buzzer
  pixels.clear(); // Clear the pixels
  pixels.show();
}

void setup() {
  // Configure power switch
  rtc_gpio_pullup_dis(GPIO_NUM_26);
  rtc_gpio_pulldown_en(GPIO_NUM_26);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_26,1);
  // Start the neopixels
  pixels.begin();
  pixels.show();
  // initialize buttons
  pinMode(r1b, INPUT_PULLUP);
  pinMode(r2b, INPUT_PULLUP);
  pinMode(r3b, INPUT_PULLUP);
  pinMode(y1b, INPUT_PULLUP);
  pinMode(y2b, INPUT_PULLUP);
  pinMode(y3b, INPUT_PULLUP);
  pinMode(rb, INPUT_PULLUP);
  pinMode(ps, INPUT);
  // Play tone to indicate power on
  tone(b1, 1000);
  tone(b2, 1500);
  delay(500);
  noTone(b1);
  noTone(b2);
  // Connect the interrupt to the isr function
  attachInterrupt(clr1.clearPin, isr, FALLING);
  
}

void loop() {
  // Clear neopixels
  pixels.clear();
  pixels.show();
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
  if (pss == LOW){
    esp_deep_sleep_start(); // Put the microcontroller to sleep

  } else if (r2s == LOW){
    buzz(2);
  } else if (r3s == LOW){
    buzz(3);
  } else if (y1s == LOW){
    buzz(4);
  } else if (y2s == LOW){
    buzz(5);
  } else if (y3s == LOW){
    buzz(6);
  } else if (r1s == LOW){
    buzz(1); // Call buzz function
  }
}



void buzz(int x) {
  switch(x) {
    case 1 :
      // Red one
      pixels.clear(); // Clear any outstanding colors
      pixels.setPixelColor(0, pixels.Color(50, 0, 0)); // Set the first two leds red
      pixels.setPixelColor(1, pixels.Color(50, 0, 0));
      pixels.show(); // Display the pixels
      
      //tone(b1, 300); // Buzz
      digitalWrite(b2, HIGH);
      delay(500);
      digitalWrite(b2, LOW);
      //noTone(b1); // Stop Buzz
      delay(30000); // Thirty seccond timer
      tone(b1, 500, 100); // Indicate time
      delay(100);
      tone(b1, 500, 100);
      pixels.clear(); // Clear pixels
      pixels.show();
      break;
    case 2 :
      // Red two
      pixels.clear();
      pixels.setPixelColor(0, pixels.Color(50, 0, 0)); // Set the first two leds red
      pixels.setPixelColor(1, pixels.Color(50, 0, 0));
      pixels.setPixelColor(3, pixels.Color(50, 0, 0)); // Set the third and fourth leds red
      pixels.setPixelColor(4, pixels.Color(50, 0, 0));      
      pixels.show(); // Display the pixels

      tone(b1, 300); // Buzz
      delay(500);
      noTone(b1); // Stop Buzz
      delay(30000); // Thirty seccond timer
      tone(b1, 500, 100); // Indicate time
      delay(100);
      tone(b1, 500, 100);
      pixels.clear(); // Clear pixels
      pixels.show();
      break;
    case 3 :
      // Red three
      pixels.clear();
      pixels.setPixelColor(0, pixels.Color(50, 0, 0)); // Set the first two leds red
      pixels.setPixelColor(1, pixels.Color(50, 0, 0));
      pixels.setPixelColor(3, pixels.Color(50, 0, 0)); // Set the third and fourth leds red
      pixels.setPixelColor(4, pixels.Color(50, 0, 0));
      pixels.setPixelColor(6, pixels.Color(50, 0, 0)); // Set the sixth and seventh leds red
      pixels.setPixelColor(7, pixels.Color(50, 0, 0));             
      pixels.show(); // Display the pixels

      tone(b1, 300); // Buzz
      delay(500);
      noTone(b1); // Stop Buzz
      delay(30000); // Thirty seccond timer
      tone(b1, 500, 100); // Indicate time
      delay(100);
      tone(b1, 500, 100);
      pixels.clear(); // Clear pixels
      pixels.show();
      break;
    case 4 :
      // Yellow one
      pixels.clear(); // Clear any outstanding colors
      pixels.setPixelColor(0, pixels.Color(50, 50, 0)); // Set the first two leds yellow
      pixels.setPixelColor(1, pixels.Color(50, 50, 0));
      pixels.show(); // Display the pixels
      
      tone(b1, 300); // Buzz!
      delay(500);
      noTone(b1); // Stop buzz
      delay(30000); // Thirty seccond timer
      tone(b1, 500, 100); // Indicate time
      delay(100);
      tone(b1, 500, 100);
      pixels.clear(); // Clear pixels
      pixels.show();
      break;
    case 5 :
      // Yellow two
      pixels.clear();
      pixels.setPixelColor(0, pixels.Color(50, 50, 0)); // Set the first two leds yellow
      pixels.setPixelColor(1, pixels.Color(50, 50, 0));
      pixels.setPixelColor(3, pixels.Color(50, 50, 0)); // Set the third and fourth leds yellow
      pixels.setPixelColor(4, pixels.Color(50, 50, 0));      
      pixels.show(); // Display the pixels

      tone(b1, 300); // Buzz
      delay(500);
      noTone(b1); // Stop Buzz
      delay(30000); // Thirty Seccond timer
      tone(b1, 500, 100); // Indicate time
      delay(100);
      tone(b1, 500, 100);
      pixels.clear(); // Clear pixels
      pixels.show();
      break;
    case 6 :
      //Yellow Three
      pixels.clear();
      pixels.setPixelColor(0, pixels.Color(50, 50, 0)); // Set the first two leds yellow
      pixels.setPixelColor(1, pixels.Color(50, 50, 0));
      pixels.setPixelColor(3, pixels.Color(50, 50, 0)); // Set the third and fourth leds yellow
      pixels.setPixelColor(4, pixels.Color(50, 50, 0));
      pixels.setPixelColor(6, pixels.Color(50, 50, 0)); // Set the sixth and seventh leds yellow
      pixels.setPixelColor(7, pixels.Color(50, 50, 0));             
      pixels.show(); // Display the pixels

      tone(b1, 300); // Buzz
      delay(500);
      noTone(b1); // Stop Buzz
      delay(30000); // Thirty seccond timer
      tone(b1, 500, 100); // Indicate time
      delay(100);
      tone(b1, 500, 100);
      pixels.clear(); // Clear pixels
      pixels.show();
      break;
    exit;
  }
   
}
