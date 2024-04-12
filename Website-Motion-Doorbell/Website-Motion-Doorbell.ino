#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "homepage.h"
#include <Arduino.h>

// WiFi credentials
const char* ssid = "Iphone";
const char* password = "12345678";

// Web server
WebServer server(80);

// Motion sensor and LED pins
#define MOTION_SENSOR_PIN  32
#define LED_PIN            17

// Doorbell button and speaker pins
const int doorbellButtonPin = 12;
const int speakerPin = 25;

// Variables for motion detection
int motionStateCurrent = LOW;
int motionStatePrevious = LOW;
String motionStatus = "No Motion Detected";
unsigned long lastMotionTime = 0;

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Initialize mDNS
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  
  // Setup routes for web server
  server.on("/", handleRoot);
  server.on("/motion-status", HTTP_GET, handleMotionStatus);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
  server.begin();
  
  // Initialize motion sensor and LED
  pinMode(MOTION_SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // Initialize doorbell button and speaker
  pinMode(doorbellButtonPin, INPUT_PULLUP);
  pinMode(speakerPin, OUTPUT);
}



void detectMotion() {
  motionStatePrevious = motionStateCurrent;
  motionStateCurrent = digitalRead(MOTION_SENSOR_PIN);
  unsigned long debounceTime = 2000;
  
  if (motionStatePrevious == LOW && motionStateCurrent == HIGH) {
    if (millis() - lastMotionTime > debounceTime) {
      Serial.println("Motion detected");
      digitalWrite(LED_PIN, HIGH);
      motionStatus = "Motion Detected";
      lastMotionTime = millis();
    }
  } else if (motionStatePrevious == HIGH && motionStateCurrent == LOW) {
    Serial.println("Motion stopped");
    digitalWrite(LED_PIN, LOW);
    motionStatus = "No Motion Detected";
  }
}

void handleRoot() {
  String message = homePage;
  server.send(200, "text/html", message);
}

void handleMotionStatus() {
  server.send(200, "text/plain", "updateMotionStatus('" + motionStatus + "');");
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void checkDoorbell() {
  if (digitalRead(doorbellButtonPin) == LOW) {
    Serial.println("Doorbell pressed!");
    playDoorbellSound();
  }
}

void playDoorbellSound() {
  tone(speakerPin, 500, 250);  // Ding
  delay(300);  // Pause between ding and dong
  tone(speakerPin, 800, 500);  // Dong
  delay(500);  // Pause before repeating
  noTone(speakerPin);  // Stop the tone
}

void loop() {
  server.handleClient();
  delay(2);
  detectMotion();
  checkDoorbell();
}
