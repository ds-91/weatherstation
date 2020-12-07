#pragma once

class Observer {
public:
	virtual void update(float temperature, float humidity, float pressure, int vibration) = 0;
};