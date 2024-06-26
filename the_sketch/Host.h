#ifndef HOST_H
#define HOST_H

#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <string>
#include "Connectable.h"
#include "Sensor.h"
#include "Gerkon.h"
#include "SensorFactory.h" 
#include "GeoSensor.h"

class Host: public Connectable{
public:
    Host();
    bool get_is_posted();
private:
    bool is_posted = false;
    std::vector<std::unique_ptr<Sensor>> sensor_list; 
    void handle_root();
    void handle_post();
};

#endif