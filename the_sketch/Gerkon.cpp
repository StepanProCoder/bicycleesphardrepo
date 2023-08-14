#include "Gerkon.h"
#include <Arduino.h> 

void ICACHE_RAM_ATTR Gerkon::sens() {
  if (millis() - lastturn > 80) {  // защита от случайных измерений (основано на том, что велосипед не будет ехать быстрее 120 км/ч)
    SPEED = w_length / ((float)(millis() - lastturn) / 1000) * 3.6;  // расчет скорости, км/ч
    set_data(std::to_string(SPEED));
    //host->setVal(std::to_string(SPEED));
    lastturn = millis();  // запомнить время последнего оборота
  }
}

void Gerkon::handle_ticks() {
    Gerkon::check_staying();
}

Gerkon::Gerkon(int pin, float w_length, const std::string& sensor_type): Sensor(pin, sensor_type) {
    this->w_length = w_length;
    set_data(std::to_string(SPEED));
    attachInterrupt(digitalPinToInterrupt(pin), [this]() {Gerkon::sens();}, RISING); // подключить прерывание на пин D2 при повышении сигнала
}

void Gerkon::check_staying() {
    if ((millis() - lastturn) > 2000) { // если сигнала нет больше 2 секунд
        SPEED = 0;  // считаем, что SPEED равно 0
        set_data(std::to_string(SPEED));
        //host->setVal(std::to_string(SPEED));
    }
}

float Gerkon::get_speed() {
    return SPEED;
}