#ifndef EEPROMS_H
#define EEPROMS_H

#include <EEPROM.h>
#include <Arduino.h>
#include <string>

namespace EEPROMS {
  std::string readFromEEPROM(int address, int size);
  void writeToEEPROM(int address, std::string value, int size);
}

#endif
