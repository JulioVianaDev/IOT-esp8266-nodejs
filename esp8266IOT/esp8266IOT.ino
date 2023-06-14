#include ".\config.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

bool stateLedApi;
unsigned long lastTimeSensor = 0;
unsigned long timerDelaySensor = 10000;
unsigned long lastTimeLed = 0;
unsigned long timerDelayLed = 10;
void setup() {
  Serial.begin(115200);
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
  pinMode(D8,OUTPUT);
  http.end();
}

void loop() {
  WiFiClientSecure client;
  HTTPClient http;

  client.setInsecure(); // Disabling certificate verification
  
  if ((millis() - lastTimeLed) > timerDelayLed) {
    http.begin(client, "https://teste-iot-professor.onrender.com/led/state-led");
    int httpCode = http.GET();
    String payload = http.getString();
    //Serial.println(payload);
    // Stream& input;
  
    StaticJsonDocument<54> doc;
    
    DeserializationError error = deserializeJson(doc, payload);
    
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }
    
    bool state = doc["state"]; // true
    Serial.print(state);
    digitalWrite(D8,state);
    lastTimeLed = millis();
  }
  if((millis()-lastTimeSensor > timerDelaySensor)){
    http.begin(client, "https://teste-iot-professor.onrender.com/sensor/acesso");
    http.addHeader("Content-Type", "application/json");
    StaticJsonDocument<100> SensorDocument;
    SensorDocument["nome"] = "Serializando o json";
    SensorDocument["value"] = 10;
    char bufferDoJsonEmString[100];
    serializeJson(SensorDocument, bufferDoJsonEmString);
    int httpResponseCode = http.POST(bufferDoJsonEmString);
    String ResponseServer = http.getString();
    Serial.println(ResponseServer);
    lastTimeSensor = millis();
  }
}
