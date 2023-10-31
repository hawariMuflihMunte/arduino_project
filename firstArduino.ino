#include <ESP8266WiFi.h>

const int phPin = A0; // Analog pin to which the pH sensor is connected
const int analogRange = 1023; // Analog range of the NodeMCU

const char* ssid = "Galaxy A139754";
const char* password = "Jirajira";

void setup() {
  Serial.begin(115200);
  connectToWiFi();
}

void loop() {
  float phValue = readPhValue();
  Serial.print("pH Value: ");
  Serial.println(phValue, 2); // Print pH value with 2 decimal places
  delay(1000); // Read pH every second
}

void connectToWiFi() {
  Serial.println("Connecting to Wifi...");
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println("Connected to WiFi");
}

float readPhValue() {
  int rawValue = analogRead(phPin);
  float pHValue = map(rawValue, 0, analogRange, 0, 14); // Map the raw value to pH range

  return pHValue;
}

