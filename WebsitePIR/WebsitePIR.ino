#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "homepage.h"

//const char* ssid = "VODAFONE-GOLD";
//const char* password = "voda123456";

const char* ssid = "Iphone";
const char* password = "12345678";


WebServer server(80);

#define MOTION_SENSOR_PIN  32
#define LED_PIN            17

int motionStateCurrent  = LOW;
int motionStatePrevious = LOW;
String motionStatus = "No Motion Detected";
unsigned long lastMotionTime = 0; // Variable to store the timestamp of the last motion

void detectMotion() {
  motionStatePrevious = motionStateCurrent;
  motionStateCurrent  = digitalRead(MOTION_SENSOR_PIN);

  // Set a debounce time (in milliseconds) to ignore subsequent triggers for a short period
  unsigned long debounceTime = 2000; // Adjust this value based on your needs

  if (motionStatePrevious == LOW && motionStateCurrent == HIGH) {
    // Check if enough time has passed since the last motion detection
    if (millis() - lastMotionTime > debounceTime) {
      Serial.println("Motion detected");
      digitalWrite(LED_PIN, HIGH);
      motionStatus = "Motion Detected";
      lastMotionTime = millis(); // Update the timestamp of the last motion
    }
  } else if (motionStatePrevious == HIGH && motionStateCurrent == LOW) {
    Serial.println("Motion stopped");
    digitalWrite(LED_PIN, LOW);
    motionStatus = "No Motion Detected";
  }
}

void handleRoot() {
  String message = homePagePart1;
  server.send(200, "text/html", message);
}

void handleMotionStatus() {
  // Respond to AJAX request with the current motion status
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

void setup(void) {
  Serial.begin(115200);
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

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/motion-status", HTTP_GET, handleMotionStatus); // New route for AJAX motion status request
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);

  server.begin();

  pinMode(MOTION_SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  delay(1000);
  printf("********************");
  printf("Camera System Online");
  printf("********************\n");
}

void loop(void) {
  server.handleClient();
  delay(2);
  detectMotion();
  
  // Send motion status to the webpage using server.send() with an asynchronous call
  server.send(200, "text/plain", "updateMotionStatus('" + motionStatus + "');");
}
