#include "GeoSensor.h"

GeoSensor::GeoSensor(std::optional<int> pin, const std::string& sensor_type): Sensor(pin, sensor_type) {
  handle_ticks();
  set_data(geopoint_to_string(geo_point));
}

GeoPoint GeoSensor::get_current_geopoint() {
 return geo_point;
}

std::string GeoSensor::geopoint_to_string(GeoPoint geo_point) {
  return std::to_string(geo_point.latitude) + "," + std::to_string(geo_point.longitude);
}

void GeoSensor::handle_ticks() {
  geo_point = GeoPoint();
}