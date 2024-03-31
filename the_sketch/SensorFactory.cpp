#include "SensorFactory.h"

namespace SensorFactory {

std::vector<std::unique_ptr<Sensor>> createSensorsFromJson(const char* json) {
    std::vector<std::unique_ptr<Sensor>> sensors;

    sensors.push_back(std::make_unique<IdSensor>(std::optional<int>(), "id"));
    sensors.push_back(std::make_unique<GeoSensor>(std::optional<int>(), "geo"));

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, json);

    if (doc["hasSpeedometer"]) {
        int pin = doc["speedometerText"];
        float wheelRadius = doc["wheelRadius"];
        wheelRadius /= 100;
        std::string sensor_type = "Gerkon"; // Set the sensor type
        sensors.push_back(std::make_unique<Gerkon>(std::optional<int>(pin), calculateWheelLength(wheelRadius), sensor_type));
    }

    // Add more conditions for other sensor types when implemented

    return sensors;
}

float calculateWheelLength(float radius) {
    float circumference = 2 * M_PI * radius; 
    return circumference;
}

} // namespace SensorFactory
