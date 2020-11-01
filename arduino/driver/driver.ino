#include "SensorData.h"
#include "CurrentData.h"
#include "DHT.h"
#include "Arduino.h"

#include <ESP8266WiFi.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define SENSOR_READ_DELAY_MS 300000 // 5 minutes

const char* ssid = "REMOVED";
const char* pass = "REMOVED";

SensorData data;
CurrentData current;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  delay(1000);
  Serial.begin(9600);

  Serial.println("Setting up WiFi...");
  WiFi.enableInsecureWEP(true);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected established!");
  dht.begin();

  data.registerObserver(&current); 
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(true);

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    data.setState(temperature, humidity); 
  }

  delay(SENSOR_READ_DELAY_MS);
}
