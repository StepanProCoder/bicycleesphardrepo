#ifndef CONNECTABLE_H
#define CONNECTABLE_H

#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266TimerInterrupt.h>
#include <ArduinoJson.h>
#include <FunctionalInterrupt.h>
#include <Preferences.h>

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
    Preferences prefs;
    const char* ssidKey = "ssid";
    const char* passwordKey = "password";
    const char* idKey = "id";
    const char* uuidKey = "uuid";
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