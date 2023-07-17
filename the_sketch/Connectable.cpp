#include "Connectable.h"

void Connectable::connect() {
    const char* hostname = "SpeedESP";
    WiFiManager wifiManager;

    // Попытка подключения к существующей Wi-Fi сети
    // Если не удалось подключиться, будет создана новая сеть в режиме точки доступа
    if (!wifiManager.autoConnect(hostname)) {
        Serial.println("Failed to connect and hit timeout");
        // При неудаче можно предпринять дополнительные действия
        // Например, перезагрузить устройство или повторить попытку подключения
    }

    // Настройка mDNS
    if (!MDNS.begin(hostname)) {
        Serial.println("Error setting up mDNS");
        return;
    }
    Serial.println("mDNS responder started");
    MDNS.addService("http", "tcp", 80);
}