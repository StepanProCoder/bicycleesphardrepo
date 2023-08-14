#ifndef HOST_H
#define HOST_H

#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <string>
#include "Connectable.h"

class Host: public Connectable{
public:
    Host();
    std::unique_ptr<ESP8266WebServer> server;
private:
    const char* hostname = "SpeedESP";
    void handle_root();
    void handle_post();
};

#endif