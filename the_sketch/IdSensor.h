#ifndef IDSENSOR_H
#define IDSENSOR_H

#include "Sensor.h"
#include <string.h>
#include <Preferences.h>

class IdSensor: public Sensor {
  public:
    IdSensor(std::optional<int> pin, const std::string& sensor_type);
    void handle_ticks() override;
    std::string get_saved_id();
  private:
    Preferences prefs;
    std::string saved_id;
};

#endif