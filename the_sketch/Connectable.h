#ifndef CONNECTABLE_H
#define CONNECTABLE_H

#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <ESP8266TimerInterrupt.h>
#include <ArduinoJson.h>
#include <FunctionalInterrupt.h>
#include "EEPROMS.h"

class Connectable {
public:
    virtual ~Connectable() = default;
    Connectable();
    virtual void connect(const char* hostname);
    std::string get_saved_id();
    std::string get_saved_uuid();
    std::unique_ptr<ESP8266WebServer> server;
private:
    void createAPMode();
    const int ssidAddr = 0;      // Адрес начала сохранения SSID
    const int passwordAddr = 64; // Адрес начала сохранения пароля
    const int idAddr = 128;      // Адрес начала сохранения уникального идентификатора
    const int uuidAddr = 192;
    std::string savedSSID;
    std::string savedPassword;
    std::string savedID;
    std::string savedUUID;
protected:
    const char* hostname = "SpeedESP";
    void read_all();
    void save_all(std::string ssid, std::string password, std::string id, std::string uuid);
    void reset_btn_pressed();
};

#endif