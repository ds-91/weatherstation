#include "Arduino.h"
#include "SensorData.h"

void SensorData::setState(float temperature, float humidity, float pressure) {
    this->temperature = temperature;
    this->humidity = humidity;
    this->pressure = pressure;

    notifyObservers();
}

void SensorData::registerObserver(Observer *o) {
    // See observers array initializtion.
    //observers[0] = o;
    observer = o;
}

void SensorData::unregisterObserver(Observer *o) {
    // See observers array initializtion.
    //observers[0] = nullptr;
    observer = nullptr;
}

void SensorData::notifyObservers() {
    // Normally I would use a vector and iterate over that while calling
    // each observer's 'update' method.
    // See observers array initializtion.
    //this->observers[0]->update(this->temperature, this->humidity);
    observer->update(temperature, humidity, pressure);
}