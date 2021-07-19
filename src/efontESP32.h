#ifndef __EFONT_ESP_H__
#define __EFONT_ESP_H__

#ifdef _M5STICKC_H_
//  #include <M5StickC.h>
  #define _TFT_OBJECT   M5.Lcd
#else 
  #ifdef _M5STACK_H_
//    #include <M5Stack.h>
    #define _TFT_OBJECT   M5.Lcd
  #else
//    #include <TFT_eSPI.h> 
    #define _TFT_OBJECT   tft
  #endif
#endif

#include "efont.h"

//#define EFONT_DEBUG

void printEfont(char *str) {
  int posX = _TFT_OBJECT.getCursorX();
  int posY = _TFT_OBJECT.getCursorY();
  uint8_t textsize = _TFT_OBJECT.textsize;
  uint32_t textcolor = _TFT_OBJECT.textcolor;
  uint32_t textbgcolor = _TFT_OBJECT.textbgcolor;
  
  byte font[32];
  
  while( *str != 0x00 ){
    // 改行処理
    if( *str == '\n' ){
      // 改行
      posY += 16 * textsize;
      posX = _TFT_OBJECT.getCursorX();
      str++;
      continue;
    }

    // フォント取得
    uint16_t strUTF16;
    str = efontUFT8toUTF16( &strUTF16, str );
    getefontData( font, strUTF16 );

    // 文字横幅
    int width = 16 * textsize;
    if( strUTF16 < 0x0100 ){
      // 半角
      width = 8 * textsize;
    }


#ifdef EFONT_DEBUG
    Serial.printf( "str : U+%04X\n", strUTF16 );
#endif


    // 背景塗りつぶし
    _TFT_OBJECT.fillRect(posX, posY, width, 16 * textsize, textbgcolor);

    // 取得フォントの確認
    for (uint8_t row = 0; row < 16; row++) {
      word fontdata = font[row*2] * 256 + font[row*2+1];
      for (uint8_t col = 0; col < 16; col++) {
#ifdef EFONT_DEBUG
        Serial.write( ( (0x8000 >> col) & fontdata ) ? "#" : " " );
#endif
        if( (0x8000 >> col) & fontdata ){
          int drawX = posX + col * textsize;
          int drawY = posY + row * textsize;
          if( textsize == 1 ){
            _TFT_OBJECT.drawPixel(drawX, drawY, textcolor);
          } else {
            _TFT_OBJECT.fillRect(drawX, drawY, textsize, textsize, textcolor);
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
    if( _TFT_OBJECT.width() <= posX ){
      posX = 0;
      posY += 16 * textsize;
    }
  }

  // カーソルを更新
  _TFT_OBJECT.setCursor(posX, posY);
}

void printEfont(char *str, int x, int y) {
  _TFT_OBJECT.setCursor(x, y);
  printEfont(str);
}

void printEfont(char *str, int x, int y, int textsize) {
  _TFT_OBJECT.setCursor(x, y);
  _TFT_OBJECT.textsize = textsize;
  printEfont(str);
}

#endif
