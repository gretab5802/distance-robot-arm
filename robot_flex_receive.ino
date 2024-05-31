#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>
#include <Stepper.h>

RF24 radio(8, 10); 			// CE, CSN pins on the transceiver module
                                   
const uint64_t pipe = 0xE8E8F0F0E1LL; 	// Pipe addresses for communication

const int stepsPerRevolution = 2038; 	// Defines the number of steps per rotation

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 3, 5, 6, 4);

int flexValue;

void setup() {
  Serial.begin(9600); 			// Start the serial communication
  radio.begin(); 			// Start the transceiver module
  radio.openReadingPipe(1, pipe); 	// Set address of receiving module
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&flexValue, sizeof(flexValue)); 		// Read from transmitter
    Serial.print("Flex Sensor Value Received: ");
    Serial.println(flexValue); 				// Print the received flex sensor value
    int servoPos = map(flexValue, 520, 790, 0, 13); 	// Map flex val to servo
    if (servoPos > 0) {
      if (servoPos > 13) {
        servoPos = 13;
      }
      myStepper.setSpeed(servoPos); 			// Set servo speed
      Serial.println(servoPos);
      myStepper.step(-stepsPerRevolution / 50);
    }
  }
  else {
    Serial.println("No Message Received"); 		// Print if no message is received
  }
}
