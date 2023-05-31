#include ".\config.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void setup() {
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

void loop() {
  // put your main code here, to run repeatedly:
  
}
