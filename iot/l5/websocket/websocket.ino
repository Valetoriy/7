#include <WiFi.h>
#include <ArduinoWebsockets.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>

using namespace websockets;

#define SS_PIN 5
#define RST_PIN 13
#define SERVO_PIN 12
MFRC522 rfid(SS_PIN, RST_PIN);
Servo SERVO;
int TIMER;

const char* SSID = "********";
const char* PASSWORD = "********";
const char* WEBSOCKET_SERVER = "ws://IP_АДРЕС:42690";
WebsocketsClient CLIENT;

void setup() {
    Serial.begin(115200);
    SPI.begin();
    rfid.PCD_Init();
    SERVO.attach(SERVO_PIN);
    SERVO.write(0);
    connect_to_wifi();
    connect_to_web_socket();
    delay(1000);
    Serial.println("Приложите RFID карту");
}

void loop() {
    CLIENT.poll();
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        char buffer[64];
        unsigned char *b = rfid.uid.uidByte;
        sprintf(buffer, "%d %d %d %d", b[0], b[1], b[2], b[3]);
        send_message(buffer);

        rfid.PICC_HaltA();
        rfid.PCD_StopCrypto1();
    }
    SERVO.write(millis() - TIMER > 3000 ? 0 : 180);
}

void connect_to_wifi() {
    Serial.println("Подключение к Wi-Fi...");
    WiFi.begin(SSID, PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Подключение...");
    }

    Serial.println("Wi-Fi подключен!");
    Serial.println("IP адрес: ");
    Serial.println(WiFi.localIP());
}

void connect_to_web_socket() {
    Serial.println("Подключение к WebSocket серверу...");

    CLIENT.onMessage([](WebsocketsMessage message) {
        if (message.data()[0] == '1') {
            Serial.println("Успешная авторизация");
            TIMER = millis();
        } else {
            Serial.println("Ошибка авторизации");
        }
    });

    CLIENT.onEvent([](WebsocketsEvent event, String data) {
        if (event == WebsocketsEvent::ConnectionOpened) {
            Serial.println("Соединение открыто");
        } else if (event == WebsocketsEvent::ConnectionClosed) {
            Serial.println("Соединение закрыто. Причина: " + data);
        } else if (event == WebsocketsEvent::GotPing) {
            Serial.println("Получен Ping");
        } else if (event == WebsocketsEvent::GotPong) {
            Serial.println("Получен Pong");
        }
    });

    bool connected = CLIENT.connect(WEBSOCKET_SERVER);
    if (connected) {
        Serial.println("WebSocket соединение установлено!");
    } else {
        Serial.println("Не удалось подключиться к WebSocket серверу.");
    }
}

void send_message(const String& message) {
    if (CLIENT.available()) {
        CLIENT.send(message);
    } else {
        Serial.println("Соединение WebSocket недоступно.");
    }
}
