#ifndef SENSOR_H
#define SENSOR_H

#include <optional>
#include <string>

class Sensor {
public:
    virtual ~Sensor() = default;
    Sensor(std::optional<int> pin, const std::string& sensor_type);
    virtual void handle_ticks() = 0;
    std::optional<int> get_pin() const;
    std::string get_sensor_type() const;
    std::string get_data() const;
    void set_pin(std::optional<int> pin);
    void set_sensor_type(const std::string& sensor_type);
    void set_data(const std::string& data);
private:
    std::optional<int> pin;
    std::string sensor_type;
    std::string data;
};

#endif