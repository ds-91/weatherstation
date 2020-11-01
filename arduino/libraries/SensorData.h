#include "Subject.h"
#include "Observer.h"

class SensorData : public Subject {
private:
	float temperature = 0.0;
	float humidity = 0.0;
	// Temporary array storage because Arduino doesn't support vectors...
	Observer *observer;

public:
	void setState(float temperature, float humidity);
	void registerObserver(Observer *o);
	void unregisterObserver(Observer *o);
	void notifyObservers() override;
};