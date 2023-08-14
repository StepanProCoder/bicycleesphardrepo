#ifndef SENSOR_H
#define SENSOR_H

#include <string>

class Sensor {
public:
    virtual ~Sensor() = default;
    Sensor(int pin, const std::string& sensor_type);
    virtual void handle_ticks() = 0;
    int get_pin() const;
    std::string get_sensor_type() const;
    std::string get_data() const;
    void set_pin(int pin);
    void set_sensor_type(const std::string& sensor_type);
    void set_data(const std::string& data);
private:
    int pin;
    std::string sensor_type;
    std::string data;
};

#endif