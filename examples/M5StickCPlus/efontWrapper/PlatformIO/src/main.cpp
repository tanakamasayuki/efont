
#include <Arduino.h>
#include <M5StickCPlus.h>

void setup() {
    M5.begin();
    M5.Lcd.setRotation(1);  // Landscape (Portrait + 90)
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextSize(1);

    M5.Lcd.printEfont("Hello", 0, 16 * 0);
    M5.Lcd.printEfont("こんにちは", 0, 16 * 1);
    M5.Lcd.printEfont("你好", 0, 16 * 2);
    M5.Lcd.printEfont("안녕하세요", 0, 16 * 3);
    M5.Lcd.printEfont("Доброе утро", 0, 16 * 4);
    M5.Lcd.printEfont("Päivää", 0, 16 * 6);
    M5.Lcd.printEfont("Здравствуйте", 0, 16 * 7);
}

void loop() {
}
