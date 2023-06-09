//Bibliotecas
#include ".\config.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
//Variaveis do led

bool stateLedApi;
unsigned long lastTimeLed = 0;
unsigned long timerDelayLed = 10;

//Sensor ultrassonico
unsigned long lastTimeSensor = 0;
unsigned long timerDelaySensor = 50;

const int trigPin = D6;
const int echoPin = D5;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034

long duration;
float distanceCm;
float distanceInch;


void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to Wi-Fi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  //Para iniciar o WIFI passamos as variaveis que estão no arquivo config.h
  WiFi.begin(ssid, password);
  // Enquanto o wifi não conectar printar pontinho
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  // Função get na api para testar se está funcionando ou não a api
  //Iniciando o client 
  WiFiClientSecure client;
  //criando um http client pros metodos(GET,POST,PATCH,PUT,DELETE)
  HTTPClient http;
  //Como a api é https precisamos desativar as verificações
  client.setInsecure(); // Disabling certificate verification
  //Iniciando a conexão com a api usando  url
  http.begin(client, "https://teste-iot-professor.onrender.com/api");
  //Pegando o códgo http da requisição( 200,404 ETC)
  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.println("Error on HTTP request");
  }
  //Acendendo o led
  pinMode(D8,OUTPUT);
  http.end();
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
  WiFiClientSecure client;
  HTTPClient http;

  client.setInsecure(); // Disabling certificate verification
  //fazendo o led piscar assincrono ao sensor
  if ((millis() - lastTimeLed) > timerDelayLed) {
    http.begin(client, "https://teste-iot-professor.onrender.com/led/state-led");
    int httpCode = http.GET();
    String payload = http.getString();
    //Serial.println(payload);
    // Stream& input;
    //iniciando um documento pra armazenar o json
    StaticJsonDocument<54> doc;
    //transformando o json em um arquivo legivel
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }
    //Após o documento ser um json salvando o state que recebe dentro de uma booleana para acender o led
    bool state = doc["state"]; // true
    //Serial.print(state);
    digitalWrite(D8,state);
    //reiniciando o cronometro
    lastTimeLed = millis();
  }
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  
  if((millis()-lastTimeSensor > timerDelaySensor)){
    http.begin(client, "https://teste-iot-professor.onrender.com/sensor/acesso");
    http.addHeader("Content-Type", "application/json");
    StaticJsonDocument<100> SensorDocument;
    SensorDocument["nome"] = "Serializando o json";
    SensorDocument["value"] = distanceCm;
    if(distanceCm < 90 and distanceCm > 30){
      char bufferDoJsonEmString[100];
      serializeJson(SensorDocument, bufferDoJsonEmString);
      int httpResponseCode = http.POST(bufferDoJsonEmString);
      String ResponseServer = http.getString();
      //Serial.println(ResponseServer);
    }
    lastTimeSensor = millis();
  }
} 
