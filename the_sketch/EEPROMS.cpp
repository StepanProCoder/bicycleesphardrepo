#include "EEPROMS.h"

std::string EEPROMS::readFromEEPROM(int address, int size) {
  std::string value;
  for (int i = 0; i < size; i++) {
    char character = EEPROM.read(address + i);
    if (character != 0) {
      value += character;
    }
  }
  return value;
}

void EEPROMS::writeToEEPROM(int address, std::string value, int size) {
  
  for (int i = 0; i < size; i++) {
    if (i < value.length()) {
      EEPROM.write(address + i, value[i]);
    } else {
      EEPROM.write(address + i, 0); // Записываем нули после последнего символа
    }
  }
  EEPROM.commit(); // Сохранение данных в EEPROM
}