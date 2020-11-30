#ifndef __EFONT_M5STACKCOREINK_H__
#define __EFONT_M5STACKCOREINK_H__

#define EFONT_USED

#include "M5CoreInk.h"
#include "efont.h"

//#define EFONT_DEBUG

void printEfont(Ink_Sprite *sprite, char *str, int x = -1, int y = -1, int textsize = 1, int color = 0) {
  static int posX = 0;
  static int posY = 0;
  uint32_t textcolor = 0;
  uint32_t textbgcolor = 1;

  if(color!=0){
    textcolor = 1;
    textbgcolor = 0;
  }

  if (x != -1) {
    posX = x;
  }
  if (y != -1) {
    posY = y;
  }

  byte font[32];

  while (*str != 0x00) {
    // 改行処理
    if (*str == '\n') {
      // 改行
      posY += 16 * textsize;
      posX = 0;
      str++;
      continue;
    }

    // フォント取得
    uint16_t strUTF16;
    str = efontUFT8toUTF16(&strUTF16, str);
    getefontData(font, strUTF16);

    // 文字横幅
    int width = 16 * textsize;
    if (strUTF16 < 0x0100) {
      // 半角
      width = 8 * textsize;
    }

#ifdef EFONT_DEBUG
    Serial.printf( "str : U+%04X\n", strUTF16 );
#endif

    // 背景塗りつぶし
    sprite->FillRect(posX, posY, width, 16 * textsize, textbgcolor);

    // 取得フォントの確認
    for (uint8_t row = 0; row < 16; row++) {
      word fontdata = font[row * 2] * 256 + font[row * 2 + 1];
      for (uint8_t col = 0; col < 16; col++) {
#ifdef EFONT_DEBUG
        Serial.write( ( (0x8000 >> col) & fontdata ) ? "#" : " " );
#endif
        if ((0x8000 >> col) & fontdata) {
          int drawX = posX + col * textsize;
          int drawY = posY + row * textsize;
          if (textsize == 1) {
            sprite->drawPix(drawX, drawY, textcolor);
          } else {
            sprite->FillRect(drawX, drawY, textsize, textsize, textcolor);
          }
        }
      }
#ifdef EFONT_DEBUG
      Serial.write( "\n" );
#endif
    }

    // 描画カーソルを進める
    posX += width;

    // 折返し処理
    if (sprite->width() <= posX) {
      posX = 0;
      posY += 16 * textsize;
    }
  }
}

#endif
