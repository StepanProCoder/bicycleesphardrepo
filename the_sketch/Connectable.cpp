#include "Connectable.h"

Connectable::Connectable() {
  server = std::make_unique<ESP8266WebServer>(80);
}

std::string Connectable::get_saved_id() {
 return savedID;
}

void Connectable::connect(const char* hostname) {

  WiFi.mode(WIFI_STA);
  EEPROM.begin(512);

  // EEPROMS::writeToEEPROM(ssidAddr, "", 64); // 64 - максимальная длина SSID
  // EEPROMS::writeToEEPROM(passwordAddr, "", 64); // 64 - максимальная длина пароля
  // EEPROMS::writeToEEPROM(idAddr, "", 64); // 64 - максимальная длина уникального идентификатора
  
  // Чтение данных из EEPROM
  savedSSID = EEPROMS::readFromEEPROM(ssidAddr, 64);
  savedPassword = EEPROMS::readFromEEPROM(passwordAddr, 64);
  savedID = EEPROMS::readFromEEPROM(idAddr, 64);

  Serial.println(savedSSID.c_str());
  
  if (savedSSID.c_str()[0] == '\0' || savedPassword.c_str()[0] == '\0') {
    //Если данные отсутствуют, создаем точку доступа
    createAPMode();
  } else {
    // Если есть сохраненные данные, подключаемся к сети
    WiFi.begin(savedSSID.c_str(), savedPassword.c_str());

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Подключение к Wi-Fi...");
    }

    Serial.println("Подключено к Wi-Fi.");
    Serial.print("IP адрес: ");
    Serial.println(WiFi.localIP());
  }

  server->on("/handshaker/", HTTP_POST, [this](){
    String json = server->arg("plain");

    StaticJsonDocument<200> doc; // Установите размер JSON-документа в соответствии с вашими потребностями
    DeserializationError error = deserializeJson(doc, json);

    if (error) {
      Serial.println("Ошибка разбора JSON");
      server->send(400, "text/plain", "Ошибка разбора JSON");
    } else {
      // Обработка данных из JSON
      const char* ssid = doc["ssid"];
      const char* password = doc["password"];
      const char* id = doc["id"];

      Serial.println("SSID: " + String(ssid));
      Serial.println("Пароль: " + String(password));
      Serial.println("ID: " + String(id));

      // Сохранение SSID, пароля и уникального идентификатора в EEPROM
      EEPROMS::writeToEEPROM(ssidAddr, ssid, 64); // 64 - максимальная длина SSID
      EEPROMS::writeToEEPROM(passwordAddr, password, 64); // 64 - максимальная длина пароля
      EEPROMS::writeToEEPROM(idAddr, id, 64); // 64 - максимальная длина уникального идентификатора

      server->send(200, "text/plain", "Данные сохранены");
      server->close();
    }

  });

  server->begin();

  //Настройка mDNS
  if (!MDNS.begin(hostname)) {
    Serial.println("Error setting up mDNS");
    return;
  }
  Serial.println("mDNS responder started");
  MDNS.addService("http", "tcp", 80);
}

void Connectable::createAPMode() {
  Serial.println("Точка доступа не найдена. Создание точки доступа.");
  WiFi.softAP("ESP-AP", "password123"); // Имя и пароль точки доступа

  IPAddress apIP = WiFi.softAPIP();
  Serial.print("IP адрес точки доступа: ");
  Serial.println(apIP);

  // Здесь вы можете отправить данные с Android приложения
  // и использовать функцию saveToEEPROM для сохранения SSID, пароля и ID
}
