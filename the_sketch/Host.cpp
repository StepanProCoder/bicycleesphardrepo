#include "Host.h"
#include "Gerkon.h"
#include "SensorFactory.h" 

bool jsonConfigReceived = false; // Flag to track if JSON config is received
std::vector<std::unique_ptr<Sensor>> sensorList; // Array to store created sensors

void Host::handle_root() {
    if (!jsonConfigReceived) {
        server->send(200, "text/plain", "Waiting for JSON config...");
        return;
    }

    StaticJsonDocument<200> jsonDoc;

    // Create JSON array of sensors
    JsonArray jsonArray = jsonDoc.to<JsonArray>();

    // Add sensor data to JSON array
    for (const auto& sensor : sensorList) {
        JsonObject sensorObject = jsonArray.createNestedObject();
        sensorObject["sensor_type"] = sensor->get_sensor_type();
        sensorObject["data"] = sensor->get_data();
    }

    String jsonString;
    serializeJson(jsonDoc, jsonString);

    server->send(200, "application/json", jsonString);
}

void Host::handle_post() {
    String body = server->arg("plain");
    sensorList = SensorFactory::createSensorsFromJson(body.c_str());
    jsonConfigReceived = true;
    server->send(200, "text/plain", "JSON config received!");
}

Host::Host() {
    connect(hostname);

    server = std::make_unique<ESP8266WebServer>(80);
    server->on("/sensors/", HTTP_POST, std::bind(&Host::handle_post, this)); // POST request handler
    server->on("/sensors/", HTTP_GET, std::bind(&Host::handle_root, this));  // GET request handler
    server->begin(); // Start HTTP server
}
