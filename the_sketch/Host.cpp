#include "Host.h"

void Host::handle_root() {
  StaticJsonDocument<200> jsonDoc;
  jsonDoc[arg] = val;

  String jsonString;
  serializeJson(jsonDoc, jsonString);

  server.send(200, "application/json", jsonString);
}

Host::Host(const std::string& arg, const std::string& val) : arg(arg), val(val), server(80) {
    server.on("/speed/", std::bind(&Host::handle_root, this)); // Установка обработчика для корневого URL-пути
    server.begin(); // Запуск HTTP-сервера
}

void Host::setVal(const std::string& val) {
    this->val = val;
}