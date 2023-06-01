#include ".\config.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void setup() {
  Serial.begin(9600);
  delay(10);

  // Connect to Wi-Fi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  // Fetch the JSON data
  WiFiClientSecure client;
  HTTPClient http;

  client.setInsecure(); // Disabling certificate verification

  http.begin(client, "https://teste-iot-professor.onrender.com/api");

  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.println("Error on HTTP request");
  }

  http.end();
}

void loop() {
  WiFiClientSecure client;
  HTTPClient http;

  client.setInsecure(); // Disabling certificate verification

  http.begin(client, "https://teste-iot-professor.onrender.com/api");

  int httpCode = http.GET();
  String payload = http.getString();
  Serial.println(payload);
  delay(100);
}
