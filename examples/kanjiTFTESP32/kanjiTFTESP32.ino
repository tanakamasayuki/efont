#include "FS.h"

#include <SPI.h>
#include <TFT_eSPI.h>      // Hardware-specific library

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

#include "efontESP32.h"

void setup() {
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  
  printEfont("Hello", 0, 16*0);
  printEfont("こんにちは", 0, 16*1);
  printEfont("１月４日　土曜日　９時５５分", 0, 16*2);  
}

void loop() {
  static int32_t i=0;
  char msg[50];
  sprintf(msg,"%i回目です。",i++);
  printEfont(msg,0,16*3);
  delay(1000);
}
