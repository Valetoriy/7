#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 13
#define SS_PIN 5

// Брелок {0x5A, 0x6C, 0x6B, 0x15}
// Карта {0x99, 0x3D, 0x08, 0x7F}

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
	Serial.begin(115200);
	while(!Serial);
	SPI.begin();
	mfrc522.PCD_Init();
	delay(4);
	mfrc522.PCD_DumpVersionToSerial();
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
	if (!mfrc522.PICC_IsNewCardPresent()) return;
	if (!mfrc522.PICC_ReadCardSerial()) return;
	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
