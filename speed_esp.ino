#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

unsigned int min_speed = 0;   // минимальная отображаемая скорость, км/ч
unsigned int max_speed = 40;  // максимальная отображаемая скорость, км/ч

unsigned long lastturn;  // переменная хранения времени последнего оборота
float SPEED; // переменная хранения скорости в виде десятичной дроби
float w_length = 2.050;  // длина окружности колеса в метрах

ESP8266WebServer server(80);
const char* hostname = "SpeedESP";

void ICACHE_RAM_ATTR sens() {
  if (millis() - lastturn > 80) {  // защита от случайных измерений (основано на том, что велосипед не будет ехать быстрее 120 км/ч)
    SPEED = w_length / ((float)(millis() - lastturn) / 1000) * 3.6;  // расчет скорости, км/ч
    lastturn = millis();  // запомнить время последнего оборота
  }
}

void handleRoot() {
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["speed"] = String(SPEED);

  String jsonString;
  serializeJson(jsonDoc, jsonString);

  server.send(200, "application/json", jsonString);
}

void setup() {
  Serial.begin(9600);  // открыть порт для связи по UART
  delay(100);
  attachInterrupt(digitalPinToInterrupt(4), sens, RISING); // подключить прерывание на пин D2 при повышении сигнала

   // Создание экземпляра объекта Wi-Fi Manager
  WiFiManager wifiManager;

  // Попытка подключения к существующей Wi-Fi сети
  // Если не удалось подключиться, будет создана новая сеть в режиме точки доступа
  if (!wifiManager.autoConnect(hostname)) {
    Serial.println("Failed to connect and hit timeout");
    // При неудаче можно предпринять дополнительные действия
    // Например, перезагрузить устройство или повторить попытку подключения
  }

   // Настройка mDNS
  if (!MDNS.begin(hostname)) {
    Serial.println("Error setting up mDNS");
    return;
  }
  Serial.println("mDNS responder started");
  MDNS.addService("http", "tcp", 80);

  server.on("/speed/", handleRoot); // Установка обработчика для корневого URL-пути
  server.begin(); // Запуск HTTP-сервера
}

void loop() {
  if ((millis() - lastturn) > 2000) { // если сигнала нет больше 2 секунд
    SPEED = 0;  // считаем, что SPEED равно 0
  }

  Serial.print("Speed: ");  // выводим скорость
  Serial.print(SPEED);
  Serial.println(" km/h");

  MDNS.update();
  server.handleClient(); // Обработка запросов клиентов
}
