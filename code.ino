#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Configuración WiFi
const char* ssid = "anita";
const char* password = "cinemanteca";
int i = 0;
// Configuración ThingSpeak
const char* server = "api.thingspeak.com";
const char* apiKey = "QI610JADU9ROMZTT";

// Pin del sensor DS18B20
const int sensorPin = 4;

// Configuración de OneWire y DallasTemperature
OneWire oneWire(sensorPin);
DallasTemperature sensors(&oneWire);

// Variables para el tiempo y el envío de datos
unsigned long lastTime = 0;
boolean sendData = false; // Variable para controlar el envío de datos a ThingSpeak
float temperatureC = 0.0; // Variable global para almacenar la temperatura en Celsius

void setup() {
  Serial.begin(115200);
  
  // Configuración del pin del sensor DS18B20
  sensors.begin();

  // Conexión a WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void loop() {
  if (millis() - lastTime >= 15000) { // Envía datos cada 15 segundos
    sensors.requestTemperatures();
    temperatureC = sensors.getTempCByIndex(0); // Lee la temperatura en Celsius
    Serial.print("Temperatura: ");
    Serial.print(temperatureC);
    Serial.println(" °C");
    lastTime = millis();
    sendData = true; // Habilitar el envío de datos a ThingSpeak
  }

  if (sendData) {
    sendToThingSpeak(); // Enviar datos a ThingSpeak
    sendData = false; // Deshabilitar el envío de datos hasta el siguiente intervalo
  }
  respiro()
}

void sendToThingSpeak() {
  WiFiClient client;
  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field3=";
    postStr += String(temperatureC);
    postStr += "\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + String(apiKey) + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    Serial.println("Datos enviados a ThingSpeak");
  }
  client.stop();
}
void respiro(){ 


  for(i = 15 ; i <= 255; i+=1)
  { 
    analogWrite(11, i);
    if (i > 150) {
      delay(4);
    }
    if ((i > 125) && (i < 151)) {
      delay(5);
    }
    if (( i > 100) && (i < 126)) {
      delay(7);
    }
    if (( i > 75) && (i < 101)) {
      delay(10);
    }
    if (( i > 50) && (i < 76)) {
      delay(14);
    }
    if (( i > 25) && (i < 51)) {
      delay(18);
    }
    if (( i > 1) && (i < 26)) {
      delay(19);
    }
  }
  for(i = 255; i >=15; i-=1)
  {
    analogWrite(11, i);
    if (i > 150) {
      delay(4);
    }
    if ((i > 125) && (i < 151)) {
      delay(5);
    }
    if (( i > 100) && (i < 126)) {
      delay(7);
    }
    if (( i > 75) && (i < 101)) {
      delay(10);
    }
    if (( i > 50) && (i < 76)) {
      delay(14);
    }
    if (( i > 25) && (i < 51)) {
      delay(18);
    }
    if (( i > 1) && (i < 26)) {
      delay(19);
    }
  }
  delay(970);
}
