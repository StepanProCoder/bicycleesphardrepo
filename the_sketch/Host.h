#ifndef HOST_H
#define HOST_H

#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <string>

class Host {
public:
    Host(const std::string& arg, const std::string& val);
    void setVal(const std::string& val);
    ESP8266WebServer server;
private:
    std::string arg;
    std::string val;
    void handle_root();
};

#endif