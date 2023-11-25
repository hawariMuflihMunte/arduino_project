#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const int phPin = A0; // Analog pin to which the pH sensor is connected
const int analogRange = 1023; // Analog range of the NodeMCU

const char* ssid = "W";
const char* password = "Jirajira";
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  connectToWiFi();

  server.on("/", HTTP_GET, []() {
    float phValue = readPhValue();

    String html = "<html><body>";
    html += "pH value: " + String(phValue, 2) + "<br>";
    html += "</body></html>";

    server.send(200, "text/html", html);
  });

  server.begin();
  Serial.println("HTTP server started.");
}

void loop() {
  server.handleClient();
  
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
  Serial.println("Local IP address");
  Serial.println(WiFi.localIP());
}

float readPhValue() {
  int rawValue = analogRead(phPin);
  float pHValue = map(rawValue, 0, analogRange, 0, 14); // Map the raw value to pH range

  return pHValue;
}

