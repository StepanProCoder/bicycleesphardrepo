#include "Connectable.h"
#include "uuid.h"

Connectable::Connectable() {
  pinMode(5, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(5), [this]() {Connectable::reset_btn_pressed(); Serial.println("ERASED");}, FALLING);
  server = std::make_unique<ESP8266WebServer>(80);
  prefs.begin("SpeedESP");
}

std::string Connectable::get_saved_id() {
 return savedID;
 //return StringUUIDGen();
}

std::string Connectable::get_saved_uuid() {
  return savedUUID;
}

void Connectable::connect(const char* hostname) {

  WiFi.mode(WIFI_STA);
  read_all();

  Serial.println(savedSSID.c_str());
  Serial.println(savedPassword.c_str());
  Serial.println(savedID.c_str());
  Serial.println(savedUUID.c_str());
  
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
      std::string uuid = StringUUIDGen();

      Serial.println("SSID: " + String(ssid));
      Serial.println("Пароль: " + String(password));
      Serial.println("ID: " + String(id));
      Serial.println("UUID: " + String(uuid.c_str()));

      // Сохранение SSID, пароля и уникального идентификатора в EEPROM
      save_all(ssid, password, id, uuid);
      read_all();

      server->send(200, "text/plain", savedUUID.c_str());
      
      server->close();
      delay(100);
      ESP.restart();
    }

  });

  server->begin();

  //Настройка mDNS
  if (!MDNS.begin(savedUUID.c_str())) {
    Serial.println("Error setting up mDNS");
    return;
  }
  Serial.println("mDNS responder started");
  MDNS.addService("speedesp", "tcp", 80);
}

void Connectable::reset_btn_pressed() {
  prefs.clear();
  read_all();
  ESP.restart();
}

void Connectable::read_all() {
  savedSSID = std::string(prefs.getString(ssidKey, "").c_str());
  savedPassword = std::string(prefs.getString(passwordKey, "").c_str());
  savedID = std::string(prefs.getString(idKey, "").c_str());
  savedUUID = std::string(prefs.getString(uuidKey, "").c_str());
}

void Connectable::save_all(std::string ssid, std::string password, std::string id, std::string uuid) {
  prefs.putString(ssidKey, String(ssid.c_str()));
  prefs.putString(passwordKey, String(password.c_str()));
  prefs.putString(idKey, String(id.c_str()));
  prefs.putString(uuidKey, String(uuid.c_str()));
}

void Connectable::createAPMode() {
  Serial.println("Точка доступа не найдена. Создание точки доступа.");
  WiFi.softAP(hostname); // Имя и пароль точки доступа

  IPAddress apIP = WiFi.softAPIP();
  Serial.print("IP адрес точки доступа: ");
  Serial.println(apIP);

  // Здесь вы можете отправить данные с Android приложения
  // и использовать функцию saveToEEPROM для сохранения SSID, пароля и ID
}
