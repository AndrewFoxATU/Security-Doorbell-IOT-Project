const int led_pin = 26;
const int sensor_pin = 27;

const long interval = 5000;
unsigned long current_time = millis();
unsigned long last_trigger = 0;
boolean timer_on = false;

void IRAM_ATTR movement_detection() {
  Serial.println("Motion was detected");
  digitalWrite(led_pin, HIGH);
  timer_on = true;
  last_trigger = millis();
}

void setup() {
 
  Serial.begin(115200);
 
  pinMode(sensor_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensor_pin), movement_detection, RISING);
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
}

void loop() {

  current_time = millis();
  if(timer_on && (current_time - last_trigger > interval)) {
    Serial.println("Motion has stopped");
    digitalWrite(led_pin, LOW);
    timer_on = false;
  }
}


