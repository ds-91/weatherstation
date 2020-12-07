#include "Arduino.h"
#include "SensorData.h"

void SensorData::setState(float temperature, float humidity, float pressure, int vibration) {
    this->temperature = temperature;
    this->humidity = humidity;
    this->pressure = pressure;
    this->vibration = vibration;

    notifyObservers();
}

void SensorData::registerObserver(Observer *o) {
    observer = o;
}

void SensorData::unregisterObserver(Observer *o) {
    observer = nullptr;
}

void SensorData::notifyObservers() {
    observer->update(temperature, humidity, pressure, vibration);
}