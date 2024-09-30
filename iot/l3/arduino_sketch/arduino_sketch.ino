#include <WiFi.h>
#include <PubSubClient.h>

const char *SSID = "********";
const char *PASSWD = "********";
WiFiClient ESP_CLIENT;
void sub_callback(char *, unsigned char *, unsigned int);
PubSubClient CLIENT("test.mosquitto.org", 1883, sub_callback, ESP_CLIENT);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    delay(100);

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

    CLIENT.loop();
}

void sub_callback(char *topic, unsigned char *payload, unsigned int length) {
    if (payload[0] == '1') digitalWrite(LED_BUILTIN, HIGH);
    else if (payload[0] == '0') digitalWrite(LED_BUILTIN, LOW);
}

void reconnect() {
    while (!CLIENT.connected()) {
        Serial.println("Connecting to MQTT broker...");

        if (CLIENT.connect("iotlab3_esp32")) {
            Serial.println("Connected.");
            CLIENT.subscribe("iotlab3");
        } else {
            Serial.print("Failed to connect, code: ");
            Serial.println(CLIENT.state());
        }
    }
}
