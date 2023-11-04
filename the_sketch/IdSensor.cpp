#include "IdSensor.h"

IdSensor::IdSensor(std::optional<int> pin, const std::string& sensor_type): Sensor(pin, sensor_type) {
  handle_ticks();
  set_data(saved_id);
}

std::string IdSensor::get_saved_id() {
 return saved_id;
}

void IdSensor::handle_ticks() {
  saved_id = EEPROMS::readFromEEPROM(id_addr, 64);
}