#ifndef GEOSENSOR_H
#define GEOSENSOR_H

#include "Sensor.h"
#include <string.h>

struct GeoPoint {
  double latitude;
  double longitude;
};

class GeoSensor: public Sensor {
  public:
    GeoSensor(std::optional<int> pin, const std::string& sensor_type);
    void handle_ticks() override;
    GeoPoint get_current_geopoint();
    static std::string geopoint_to_string(GeoPoint geo_point);
  private:
    GeoPoint geo_point;
};

#endif