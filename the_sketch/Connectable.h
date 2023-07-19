#ifndef CONNECTABLE_H
#define CONNECTABLE_H

#include <ESP8266mDNS.h>
#include <WiFiManager.h>

class Connectable {
public:
    virtual ~Connectable() = default;
    virtual void connect(const char* hostname);
};

#endif