#include <WiFi.h>
#include <PubSubClient.h>

const int GREEN_LED = 12;
const int RED_LED = 13;
const int BUTTON = 14;
const char *SSID = "********";
const char *PASSWD = "********";
WiFiClient ESP_CLIENT;
void sub_callback(char *, unsigned char *, unsigned int);
PubSubClient CLIENT("test.mosquitto.org", 1883, sub_callback, ESP_CLIENT);

void setup() {
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BUTTON, INPUT_PULLUP);
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

    if (!digitalRead(BUTTON)) {
        CLIENT.publish("iotl3/esp_srvc", "P");
        delay(500);
    }

    CLIENT.loop();
}

void sub_callback(char *topic, unsigned char *payload, unsigned int length) {
    if (payload[0] == '1') {
        digitalWrite(GREEN_LED, HIGH);
        delay(1000);
        digitalWrite(GREEN_LED, LOW);
    }
    else if (payload[0] == '0') {
        digitalWrite(RED_LED, HIGH);
        delay(1000);
        digitalWrite(RED_LED, LOW);
    }
}

void reconnect() {
    while (!CLIENT.connected()) {
        Serial.println("Connecting to MQTT broker...");

        if (CLIENT.connect("iotlab3_esp32")) {
            Serial.println("Connected.");
            CLIENT.subscribe("iotl3/srvc_esp");
        } else {
            Serial.print("Failed to connect, code: ");
            Serial.println(CLIENT.state());
        }
    }
}
