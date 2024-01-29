#include "Gerkon.h" 

Gerkon* Gerkon::gerkon = nullptr;

void ICACHE_RAM_ATTR Gerkon::sens() {
  if (millis() - lastturn > 80) {  // защита от случайных измерений (основано на том, что велосипед не будет ехать быстрее 120 км/ч)
    set_speed(w_length / ((float)(millis() - lastturn) / 1000) * 3.6);  // расчет скорости, км/ч
    set_data(std::to_string(get_speed()));
    lastturn = millis();  // запомнить время последнего оборота
  }
}

void Gerkon::handle_ticks() {
    attachInterrupt(digitalPinToInterrupt(get_pin().value()), [this]() {Gerkon::sens();}, RISING); // подключить прерывание на пин D2 при повышении сигнала
    timer.attachInterruptInterval(CHECK_INTERVAL, check_staying);
}

Gerkon::Gerkon(std::optional<int> pin, float w_length, const std::string& sensor_type): Sensor(pin, sensor_type) {
    this->w_length = w_length;
    this->gerkon = this;
    set_data(std::to_string(SPEED));
    handle_ticks();
}

void Gerkon::check_staying() {
    if ((millis() - gerkon->get_lastturn()) > 2000) { // если сигнала нет больше 2 секунд
        gerkon->set_speed(0);  // считаем, что SPEED равно 0
        gerkon->set_data(std::to_string(gerkon->get_speed()));
    }
}

void Gerkon::set_speed(float speed) {
  this->SPEED = speed;
}

float Gerkon::get_speed() const{
  return SPEED;
}

unsigned long Gerkon::get_lastturn() const{
  return lastturn;
}