#include "SensorFactory.h"
#include "Gerkon.h"
#include "IdSensor.h"
#include <ArduinoJson.h>
#include <string>
#include <cmath>

namespace SensorFactory {

std::vector<std::unique_ptr<Sensor>> createSensorsFromJson(const char* json) {
    std::vector<std::unique_ptr<Sensor>> sensors;

    sensors.push_back(std::make_unique<IdSensor>(-1, "id"));

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, json);

    if (doc["hasSpeedometer"]) {
        int pin = doc["speedometerText"];
        float wheelRadius = doc["wheelRadius"];
        wheelRadius /= 100;
        std::string sensor_type = "Gerkon"; // Set the sensor type
        sensors.push_back(std::make_unique<Gerkon>(pin, calculateWheelLength(wheelRadius), sensor_type));
    }

    // Add more conditions for other sensor types when implemented

    return sensors;
}

float calculateWheelLength(float radius) {
    float circumference = 2 * M_PI * radius; 
    return circumference;
}

} // namespace SensorFactory
