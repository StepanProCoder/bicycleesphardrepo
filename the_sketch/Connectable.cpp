#include "Connectable.h"

// Адреса в EEPROM для хранения данных
const int ssidAddr = 0;      // Адрес начала сохранения SSID
const int passwordAddr = 64; // Адрес начала сохранения пароля
const int idAddr = 128;      // Адрес начала сохранения уникального идентификатора


Connectable::Connectable() {
  server = std::make_unique<ESP8266WebServer>(80);
}

void Connectable::connect(const char* hostname) {

  WiFi.mode(WIFI_STA);
  EEPROM.begin(512);

  // writeToEEPROM(ssidAddr, "", 64); // 64 - максимальная длина SSID
  // writeToEEPROM(passwordAddr, "", 64); // 64 - максимальная длина пароля
  // writeToEEPROM(idAddr, "", 64); // 64 - максимальная длина уникального идентификатора
  
  // Чтение данных из EEPROM
  String savedSSID = readFromEEPROM(ssidAddr, 64);
  String savedPassword = readFromEEPROM(passwordAddr, 64);
  String savedID = readFromEEPROM(idAddr, 64);

  Serial.println(savedSSID);
  
  if (savedSSID.isEmpty() || savedPassword.isEmpty()) {
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
      writeToEEPROM(ssidAddr, ssid, 64); // 64 - максимальная длина SSID
      writeToEEPROM(passwordAddr, password, 64); // 64 - максимальная длина пароля
      writeToEEPROM(idAddr, id, 64); // 64 - максимальная длина уникального идентификатора

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

String Connectable::readFromEEPROM(int address, int size) {
  String value;
  for (int i = 0; i < size; i++) {
    char character = EEPROM.read(address + i);
    if (character != 0) {
      value += character;
    }
  }
  return value;
}

void Connectable::writeToEEPROM(int address, String value, int size) {
  for (int i = 0; i < size; i++) {
    if (i < value.length()) {
      EEPROM.write(address + i, value[i]);
    } else {
      EEPROM.write(address + i, 0); // Записываем нули после последнего символа
    }
  }
  EEPROM.commit(); // Сохранение данных в EEPROM
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
