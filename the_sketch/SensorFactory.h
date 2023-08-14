#ifndef SENSOR_FACTORY_H
#define SENSOR_FACTORY_H

#include <vector>
#include <memory>
#include "Sensor.h"

namespace SensorFactory {

std::vector<std::unique_ptr<Sensor>> createSensorsFromJson(const char* json);
float calculateWheelLength(float radius);

} // namespace SensorFactory

#endif
