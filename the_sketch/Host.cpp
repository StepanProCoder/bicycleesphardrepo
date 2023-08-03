#include "Host.h"
#include "Gerkon.h"

void Host::handle_root() {
    StaticJsonDocument<200> jsonDoc;
  
    // Создаем список смарт-указателей на объекты Sensor
    std::vector<std::unique_ptr<Sensor>> sensorList;
    sensorList.push_back(std::make_unique<Gerkon>("speedo", "5.0"));

    // Создаем JSON-массив
    JsonArray jsonArray = jsonDoc.to<JsonArray>();

    // Добавляем объекты SensorData в JSON-массив
    for (const auto& sensor : sensorList) {
        JsonObject sensorObject = jsonArray.createNestedObject();
        sensorObject["sensor_type"] = sensor->get_sensor_type();
        sensorObject["data"] = sensor->get_data();
    }

    String jsonString;
    serializeJson(jsonDoc, jsonString);

    server->send(200, "application/json", jsonString);
}

Host::Host(const std::string& arg, const std::string& val) : arg(arg), val(val) {
  connect(hostname);
  
  server = std::make_unique<ESP8266WebServer>(80);
  server->on("/sensors/", std::bind(&Host::handle_root, this)); // Установка обработчика для корневого URL-пути
  server->begin(); // Запуск HTTP-сервера
}

void Host::setVal(const std::string& val) {
    this->val = val;
}