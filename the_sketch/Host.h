#ifndef HOST_H
#define HOST_H

#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <string>
#include "Connectable.h"

class Host: public Connectable{
public:
    Host(const std::string& arg, const std::string& val);
    void setVal(const std::string& val);
    std::unique_ptr<ESP8266WebServer> server;
private:
    const char* hostname = "SpeedESP";
    std::string arg;
    std::string val;
    void handle_root();
};

#endif