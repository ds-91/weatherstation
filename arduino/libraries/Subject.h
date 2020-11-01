#pragma once
#include "observer.h"

class Subject {
public:
	virtual void registerObserver(Observer *o) = 0;
	virtual void unregisterObserver(Observer *o) = 0;
	virtual void notifyObservers() = 0;
};