#define MOTION_SENSOR_PIN  32  // ESP32 pin GPIO32 connected to the OUTPUT pin of motion sensor
#define LED_PIN            17  // ESP32 pin GPIO17 connected to LED's pin

int motionStateCurrent  = LOW; // current  state of motion sensor's pin
int motionStatePrevious = LOW; // previous state of motion sensor's pin

void setup() {
  Serial.begin(9600);                // initialize serial
  pinMode(MOTION_SENSOR_PIN, INPUT); // set ESP32 pin to input mode
  pinMode(LED_PIN, OUTPUT);          // set ESP32 pin to output mode
  delay(1000);
  printf("********************");
  printf("Camera System Online");
  printf("********************\n");
  printf("Live video available at http://192.168.1.10:81/stream\n");
}

void loop() {
  motionStatePrevious = motionStateCurrent;             // store old state
  motionStateCurrent  = digitalRead(MOTION_SENSOR_PIN); // read new state
  if (motionStatePrevious == LOW && motionStateCurrent == HIGH) { // pin state change: LOW -> HIGH
    Serial.println("Motion detected, Photo has been sent to webserver");
    digitalWrite(LED_PIN, HIGH); // turn on
  } else if (motionStatePrevious == HIGH && motionStateCurrent == LOW) { // pin state change: HIGH -> LOW
    Serial.println("Motion stopped");
    digitalWrite(LED_PIN, LOW);  // turn off
  }
}
