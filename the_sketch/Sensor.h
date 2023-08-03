#ifndef SENSOR_H
#define SENSOR_H

#include <string>

class Sensor {
public:
    virtual ~Sensor() = default;
    virtual void handle_ticks() = 0;
    std::string get_sensor_type() const;
    std::string get_data() const;
    void set_sensor_type(const std::string& sensor_type);
    void set_data(const std::string& data);
private:
    std::string sensor_type;
    std::string data;
};

#endif