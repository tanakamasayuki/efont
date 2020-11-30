#include <M5CoreInk.h>
#include "efontEnableAll.h"
#include "efont.h"
#include "efontM5StackCoreInk.h"

Ink_Sprite inkPageSprite(&M5.M5Ink);

void setup() {
  M5.begin();
  if ( !M5.M5Ink.isInit()) {
    Serial.printf("Ink Init faild");
    while (1) {
      delay(100);
    }
  }
  M5.M5Ink.clear();
  delay(1000);

  //creat ink refresh Sprite
  if ( inkPageSprite.creatSprite(0, 0, 200, 200, true) != 0 ) {
    Serial.printf("Ink Sprite creat faild");
  }

  printEfont(&inkPageSprite, "Hello\n");
  printEfont(&inkPageSprite, "こんにちは\n");
  printEfont(&inkPageSprite, "你好\n");
  printEfont(&inkPageSprite, "안녕하세요\n");
  printEfont(&inkPageSprite, "Доброе утро\n");
  printEfont(&inkPageSprite, "Päivää\n");
  printEfont(&inkPageSprite, "Здравствуйте\n");

  printEfont(&inkPageSprite, "efont\nPrint Test", 0, 130, 2, 1);

  inkPageSprite.pushSprite();
}

void loop() {
}
