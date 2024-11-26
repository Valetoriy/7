#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 4);

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Date: ");
  lcd.print(12);
  lcd.print("/");
  lcd.print(12);
  lcd.print("/");
  lcd.print(12);

  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.print(12);
  lcd.print(":");
  lcd.print(12);
  lcd.print(":");
  lcd.print(12);

  delay(1000);
}
