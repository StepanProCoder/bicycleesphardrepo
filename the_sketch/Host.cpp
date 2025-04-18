#include "Host.h"

void Host::handle_root() {
    if (!is_posted) {
        //server->send(200, "text/plain", "Waiting for JSON config...");
        return;
    }

    StaticJsonDocument<400> json_doc;

    // Create JSON array of sensors
    JsonArray json_array = json_doc.to<JsonArray>();

    // Add sensor data to JSON array
    for (const auto& sensor : sensor_list) {

        if (!strcmp(sensor->get_sensor_type().c_str(), "geo") && server->hasArg("latitude") && server->hasArg("longitude")) {
          String latitudeStr = server->arg("latitude");
          String longitudeStr = server->arg("longitude");
          GeoPoint geo_point = GeoPoint();
          geo_point.latitude = latitudeStr.toDouble();
          geo_point.longitude = longitudeStr.toDouble();
          sensor->set_data(GeoSensor::geopoint_to_string(geo_point));
          Serial.println(sensor->get_data().c_str());
        }

        JsonObject sensor_object = json_array.createNestedObject();
        sensor_object["sensor_type"] = sensor->get_sensor_type();
        sensor_object["data"] = sensor->get_data();
    }

    String json_string;
    serializeJson(json_doc, json_string);

    server->send(200, "application/json", json_string);
}

void Host::handle_post() {
    String body = server->arg("plain");
    Serial.println(body.c_str());

    if(!strcmp(body.c_str(), "ERASE")) {
      Serial.println("RESETTING");
      server->send(200, "text/plain", "RESETTING");
      server->close();
      reset_btn_pressed();
    } 
    else {
      sensor_list = SensorFactory::createSensorsFromJson(body.c_str());
      is_posted = true;
      handle_root();
    }
}

Host::Host(): Connectable() {
    Serial.println("host consructor started");
    connect(hostname);
    Serial.println("connect over");
    server->on("/sensors/", HTTP_POST, std::bind(&Host::handle_post, this)); // POST request handler
    server->on("/sensors/", HTTP_GET, std::bind(&Host::handle_root, this));  // GET request handler
    server->begin(); // Start HTTP server
    Serial.println("host consructor over");
}

bool Host::get_is_posted() {
  return is_posted;
}
