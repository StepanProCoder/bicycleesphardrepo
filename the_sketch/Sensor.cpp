#include "Sensor.h"

std::string Sensor::get_sensor_type() const{
  return sensor_type;
}

std::string Sensor::get_data() const{
  return data;
}

void Sensor::set_sensor_type(const std::string& sensor_type) {
  this->sensor_type = sensor_type;
}

void Sensor::set_data(const std::string& data) {
  this->data = data;
}