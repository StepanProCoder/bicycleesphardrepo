#ifndef IDSENSOR_H
#define IDSENSOR_H

#include "Sensor.h"
#include "EEPROMS.h"
#include <string.h>

class IdSensor: public Sensor {
  public:
    IdSensor(int pin, const std::string& sensor_type);
    void handle_ticks() override;
    std::string get_saved_id();
  private:
    std::string saved_id;
    const int id_addr = 128;
};

#endif