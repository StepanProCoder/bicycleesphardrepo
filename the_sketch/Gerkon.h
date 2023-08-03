#ifndef GERKON_H
#define GERKON_H

#include "Sensor.h"
#include <functional>
#include <FunctionalInterrupt.h>

class Gerkon: public Sensor {

  public:
    Gerkon(const std::string& arg, const std::string& val); 
    void ICACHE_RAM_ATTR sens();
    void check_staying();
    float get_speed();
    float SPEED; // переменная хранения скорости в виде десятичной дроби
    float w_length = 2.050;  // длина окружности колеса в метрах

    void handle_ticks() override;

  private:
    unsigned int min_speed = 0;   // минимальная отображаемая скорость, км/ч
    unsigned int max_speed = 40;  // максимальная отображаемая скорость, км/ч
    unsigned long lastturn;  // переменная хранения времени последнего оборота
    
};

#endif