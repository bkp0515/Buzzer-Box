// Quizzing box faceplate test code. Power up and test the faceplate chip.
// Ben Pacheco, Created: 10/11/23

#include <Wire.h> // Add the Arduino I2c library to the code

void setup() {
  Wire.begin(); // Start the I2C communication

  Serial.begin(9600); // Start serial communication for reporting

  delay(500); // Wait for everything to power on 

  Wire.beginTransmission(33); // Begin a transmission to the device

  Wire.write(byte(0x03));  // Target configuration register

  Wire.write(byte(0x00)); // Set the config register to be all output or 0

  Wire.endTransmission(); // End the config transmission

  delay(500);
}

void loop() {


  Wire.beginTransmission(33); // Begin a new transmission to blink the leds
  
  Wire.write(byte(0x01)); // Target the output port register

  Wire.write(byte(0xFF)); // Set all outputs to high

  Wire.endTransmission();

  delay(1000);

  Wire.beginTransmission(33);

  Wire.write(byte(0x01)); 

  Wire.write(byte(0x00));

  Wire.endTransmission();

  delay(1000);

}
