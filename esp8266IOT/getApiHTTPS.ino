//#include ".\config.h"
//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>

void setupCerto() {
  // put your setup code here, to run once:
  Serial.begin(9600);
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

}

void loopCerto() {
  // put your main code here, to run repeatedly:
  WiFiClientSecure client;
  HTTPClient http;

  client.setInsecure(); // Disabling certificate verification

  http.begin(client, "https://node-deploy-api-tomate.onrender.com/users");

  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.println("Error on HTTP request");
  }

  http.end();

}
