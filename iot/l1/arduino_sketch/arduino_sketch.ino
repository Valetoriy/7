
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    for (int i = 0; i < 255; i++) {
        analogWrite(LED_BUILTIN, i);
        delay(5);
    }
    for (int i = 255; i >= 0; i--) {
        analogWrite(LED_BUILTIN, i);
        delay(5);
    }
}
