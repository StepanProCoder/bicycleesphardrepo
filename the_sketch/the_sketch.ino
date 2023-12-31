#include "Gerkon.h"
#include "Host.h"

std::unique_ptr<Host> host;

void setup() {
  Serial.begin(9600);  // открыть порт для связи по UART
  delay(100);

  Serial.println("THIS IS ARCHITECTURE");

  host = std::make_unique<Host>();
}

void loop() {
 
  // gerkon->handle_ticks();

  // Serial.print("Speed: ");  // выводим скорость
  // Serial.print(gerkon->get_speed());
  // Serial.println(" km/h");

  if(!host->get_is_posted())
    MDNS.update();
  host->server->handleClient(); // Обработка запросов клиентов
}
