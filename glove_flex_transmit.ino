#include <nRF24L01.h>
#include <SPI.h>
#include <RF24.h>
#include "Wire.h"

RF24 radio(8, 10); // CE, CSN pins on the transceiver module
                                   
const uint64_t pipe = 0xE8E8F0F0E1LL; // Pipe address for communication

int flexPin = A0;
int flexValue;

void setup() {
  Serial.begin(9600); 		// Start the serial communication
  Wire.begin();
  radio.begin(); 		// Start the transceiver module
  radio.openWritingPipe(pipe); 	// Set address of receiving module
}

void loop() {
  flexValue = analogRead(flexPin); // Read the flex sensor value
  Serial.println(flexValue);
  boolean test = radio.write(&flexValue, sizeof(flexValue)); // Send value to receiver
  Serial.println(test); // print 0 if no connection to reciever, 1 if there is
  delay(100); // Wait for 100ms before sending the next value
}
