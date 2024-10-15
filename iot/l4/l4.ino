#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#define DHT_PIN 13

const char *SSID = "********";
const char *PASSWD = "********";
WiFiClient ESP_CLIENT;
PubSubClient CLIENT(ESP_CLIENT);
DHT dht(DHT_PIN, DHT11);
// DHT dht(DHT_PIN, DHT22);
unsigned long TIMER;

void setup() {
    CLIENT.setServer("ЛОКАЛЬНЫЙ IP", 1883);

    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    delay(100);
    dht.begin();

    Serial.print("Connecting to ");
    Serial.print(SSID);
    WiFi.begin(SSID, PASSWD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.print("\nWiFi connected, IP: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    if (!CLIENT.connected()) {
        reconnect();
    }
    unsigned long current_time = millis();
    if (current_time - TIMER >= 2000) {
        TIMER = current_time;
        send_measurements();
    }

    CLIENT.loop();
}

void send_measurements() {
    unsigned long start_ms = millis();
    unsigned long start_us = micros();
    float hum  = dht.readHumidity();
    float temp = dht.readTemperature();
    unsigned long end_us = micros();
    unsigned long end_ms = millis();

    if (isnan(hum) || isnan(temp)) {
        Serial.println("Failed to read from the DHT sensor!");
    } else {
        char buffer[64];
        int len = sprintf(buffer, "%.1f %.1f %ld %ld",
            temp, hum, end_ms - start_ms, end_us - start_us);
        CLIENT.publish("iotl4/esp_srvc", buffer, len);
        Serial.print("Sent: ");
        Serial.println(buffer);
    }
}

void reconnect() {
    while (!CLIENT.connected()) {
        Serial.println("Connecting to MQTT broker...");

        if (CLIENT.connect("iotlab_esp32")) {
            Serial.println("Connected.");
        } else {
            Serial.print("Failed to connect, code: ");
            Serial.println(CLIENT.state());
        }
    }
}
