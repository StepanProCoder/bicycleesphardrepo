#ifndef GERKON_H
#define GERKON_H

#include "Sensor.h"
#include <functional>
#include <FunctionalInterrupt.h>
#include <Arduino.h>
#include <ESP8266TimerInterrupt.h>

class Gerkon: public Sensor {

  public:
    Gerkon(int pin, float w_length, const std::string& sensor_type); 
    void ICACHE_RAM_ATTR sens();
    static void check_staying();
    void set_speed(float speed);
    float get_speed() const;
    unsigned long get_lastturn() const;
    void handle_ticks() override;

  private:
    float SPEED = 0; // переменная хранения скорости в виде десятичной дроби
    float w_length;  // длина окружности колеса в метрах
    unsigned int min_speed = 0;   // минимальная отображаемая скорость, км/ч
    unsigned int max_speed = 40;  // максимальная отображаемая скорость, км/ч
    unsigned long lastturn;  // переменная хранения времени последнего оборота
    const unsigned long CHECK_INTERVAL = 1000000;
    ESP8266TimerInterrupt timer;
    static Gerkon* gerkon;
};

#endif