#ifndef SENSOR_H
#define SENSOR_H

#include "Connectable.h"

class Sensor: public Connectable {
public:
    virtual ~Sensor() = default;
    virtual void handleTicks() = 0;
};

#endif