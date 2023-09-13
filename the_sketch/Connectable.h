#ifndef CONNECTABLE_H
#define CONNECTABLE_H

#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <ESP8266TimerInterrupt.h>
#include <ArduinoJson.h>

class Connectable {
public:
    virtual ~Connectable() = default;
    Connectable();
    virtual void connect(const char* hostname);
    std::unique_ptr<ESP8266WebServer> server;
private:
    String readFromEEPROM(int address, int size);
    void writeToEEPROM(int address, String value, int size);
    void createAPMode();
};

#endif