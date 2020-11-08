#include "Observer.h"

class CurrentData : public Observer {
public:
    virtual void update(float temperature, float humidity, float pressure);
};