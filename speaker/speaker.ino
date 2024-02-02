#include <Arduino.h>

// Define doorbell button pin
const int doorbellButtonPin = 12;

// Define speaker pin
const int speakerPin = 25;


void setup() {
  Serial.begin(115200);

  // Initialize doorbell button
  pinMode(doorbellButtonPin, INPUT_PULLUP);

  // Initialize speaker
  pinMode(speakerPin, OUTPUT);

}
void loop() {
  // Check if the doorbell button is pressed
  if (digitalRead(doorbellButtonPin) == LOW) {
    Serial.println("Doorbell pressed!");

    // Play a sound on the speaker
    playDoorbellSound();

    // You can add additional actions here when the doorbell is pressed
  }

  // Add your existing code here
}

void playDoorbellSound() {
  // Play a simple tone on the speaker
  tone(speakerPin, 1000, 1000);  // Adjust frequency and duration as needed
  delay(1000);  // Add a delay between tones
  noTone(speakerPin);  // Stop the tone
}
