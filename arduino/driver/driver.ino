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

const char* ssid = "florida15";
const char* pass = "RemyBellaCoco3";
const uint8_t VIB_PIN = 14;

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

  Serial.println("Connection established!");
  pinMode(VIB_PIN, INPUT);
  dht.begin();
  bmp.begin();

  data.registerObserver(&current); 
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(true);
  float pressure = bmp.readPressure() / PASCALS_TO_IN_HG;
  int vibration = digitalRead(VIB_PIN);

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  }

  if (isnan(pressure)) {
    Serial.println("Failed to read from BMP sensor!");
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    data.setState(temperature, humidity, pressure, vibration);
  }

  delay(SENSOR_READ_DELAY_MS);
}
