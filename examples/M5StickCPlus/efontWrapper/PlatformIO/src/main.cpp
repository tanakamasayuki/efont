
#include <Arduino.h>
#include <M5StickCPlus.h>

void setup() {
    M5.begin();
    M5.Lcd.setRotation(1);  // Landscape (Portrait + 90)
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextSize(2);

    M5.Lcd.printEfont("Hello");
    M5.Lcd.printEfont("こんにちは");
}

void loop() {
}
