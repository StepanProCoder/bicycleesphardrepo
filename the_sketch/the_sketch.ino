#include "Gerkon.h"

std::unique_ptr<Gerkon> gerkon;

void setup() {
  Serial.begin(9600);  // открыть порт для связи по UART
  delay(100);

  Serial.println("THIS IS ARCHITECTURE");

  gerkon = std::make_unique<Gerkon>("speed", "0.0");
}

void loop() {
 
  gerkon->check_staying();

  Serial.print("Speed: ");  // выводим скорость
  Serial.print(gerkon->get_speed());
  Serial.println(" km/h");

  MDNS.update();
  gerkon->host->server.handleClient(); // Обработка запросов клиентов
}
