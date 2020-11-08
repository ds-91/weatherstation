#include "CurrentData.h"
#include "Arduino.h"
#include "ESP8266HTTPClient.h"

void CurrentData::update(float temperature, float humidity, float pressure) {
    // Here we will send the updated data to the server
    HTTPClient http;
    String json = "{\"temperature\":" + String(temperature) + 
                    ", \"humidity\":" + String(humidity) + 
                    ", \"pressure\":" + String(pressure) + "}";

    http.begin("http://10.0.0.165:5000/add");
    
    http.addHeader("Content-Type", "application/json");

    int response = http.POST(json);

    Serial.print("HTTP Response: ");
    Serial.println(response);
    String payload = http.getString();
    Serial.println(payload);

    http.end();
}