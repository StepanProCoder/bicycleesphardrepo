#include "Gerkon.h"
#include "Host.h"

#include <EEPROM.h>

std::unique_ptr<Host> host;

void setup() {
  Serial.begin(9600);  // открыть порт для связи по UART
  delay(100);

  Serial.println("THIS IS ARCHITECTURE");

  host = std::make_unique<Host>();
}

void loop() {
  
  //if(!host->get_is_posted()) {
    //Serial.println("MDNS!!!");
    MDNS.update();
  //}
    
  host->server->handleClient(); // Обработка запросов клиентов
}
