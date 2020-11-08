#include "SensorData.h"
#include "CurrentData.h"
#include "DHT.h"
#include "Arduino.h"

#include <ESP8266WiFi.h>
#include <Adafruit_BMP085.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define SENSOR_READ_DELAY_MS 300000 // 5 minutes 300000
#define PASCALS_TO_IN_HG 3377

const char* ssid = "REMOVED";
const char* pass = "REMOVED";

SensorData data;
CurrentData current;

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;

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
  bmp.begin();

  data.registerObserver(&current); 
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(true);
  float pressure = bmp.readPressure() / PASCALS_TO_IN_HG;

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (isnan(pressure)) {
    Serial.println("Failed to read from BMP sensor!");
    return;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    data.setState(temperature, humidity, pressure);
  }

  delay(SENSOR_READ_DELAY_MS);
}
