#include "Gerkon.h"
#include <Arduino.h> 

void ICACHE_RAM_ATTR Gerkon::sens() {
  if (millis() - lastturn > 80) {  // защита от случайных измерений (основано на том, что велосипед не будет ехать быстрее 120 км/ч)
    SPEED = w_length / ((float)(millis() - lastturn) / 1000) * 3.6;  // расчет скорости, км/ч
    //host->setVal(std::to_string(SPEED));
    lastturn = millis();  // запомнить время последнего оборота
  }
}

void Gerkon::handle_ticks() {
    Gerkon::check_staying();
}

Gerkon::Gerkon(const std::string& sensor_type, const std::string& data) {
    set_sensor_type(sensor_type);
    set_data(data);
    attachInterrupt(digitalPinToInterrupt(4), [this]() {Gerkon::sens();}, RISING); // подключить прерывание на пин D2 при повышении сигнала
}

void Gerkon::check_staying() {
    if ((millis() - lastturn) > 2000) { // если сигнала нет больше 2 секунд
        SPEED = 0;  // считаем, что SPEED равно 0
        //host->setVal(std::to_string(SPEED));
    }
}

float Gerkon::get_speed() {
    return SPEED;
}