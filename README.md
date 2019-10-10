# efont Unicode BDF Font Data

http://openlab.ring.gr.jp/efont/unicode/

/efont/ Unicode font can be used in Arduino.

## Overview

16-pixel font data of 32 bytes per character using f16.bdf and b16.bdf included in /efont/ Unicode Font.
Full-width characters use f16.bdf, characters up to U+00FF are half-width characters, and b16.bdf is used.

## Font format

Saved in BDF format.

https://en.wikipedia.org/wiki/Glyph_Bitmap_Distribution_Format

```
const uint8_t efontFontData[] PROGMEM = {
#ifdef __EFONT_ENABLE_0X0021__ // ! 
// U+0021 ! 
0x00, 0x00,
0x00, 0x00,
0x00, 0x00,
0x00, 0x00,
0x08, 0x00,
0x08, 0x00,
0x08, 0x00,
0x08, 0x00,
0x08, 0x00,
0x08, 0x00,
0x08, 0x00,
0x00, 0x00,
0x08, 0x00,
0x08, 0x00,
0x00, 0x00,
0x00, 0x00,
#endif
...
```

## How to reduce font size

Fonts are managed in units of characters, and can be set not to be read in units of characters.
If it is 21,729 characters, it will be 721K font data.

The number of characters can be controlled by specifying the read font before efont.h.

```
//#include "efontEnableAll.h"
//#include "efontEnableAscii.h"
//#include "efontEnableCJK.h"
#include "efontEnableJa.h"
#include "efont.h"
```

efontEnableJaMini.h is compact Japanese font data.

## font size

| Target              | Option              | Characters | Font size |
|---------------------|---------------------|------------|-----------|
| ALL                 | efontEnableAll.h    |     21,727 |   738,718 |
| Ascii               | efontEnableAscii.h  |        191 |     6,494 |
| CJK Kanji           | efontEnableCJK.h    |     19,379 |   658,886 |
| Simplified Chinese  | efontEnableCn.h     |     18,077 |   614,618 |
| Japanese            | efontEnableJa.h     |     10,835 |   368,390 |
| Mini Japanese       | efontEnableJaMini.h |      4,107 |   139,638 |
| Korean              | efontEnableKr.h     |      8,319 |   282,846 |
| Traditional Chinese | efontEnableTw.h     |     13,555 |   460,870 |

## Usage other than M5StickC

The drawing area is different for each model, so please recreate it for each model.

## Sample code

```
#include <M5StickC.h>
#include "efontEnableJa.h"
#include "efontM5StickC.h"

void setup() {
  M5.begin();
  M5.Lcd.setRotation(0);
  M5.Lcd.setCursor(0, 0);

  printEfont("Hello", 0, 16*0);
  printEfont("こんにちは", 0, 16*1);
  printEfont("你好", 0, 16*2);
  printEfont("안녕하세요", 0, 16*3);
  printEfont("Доброе утро", 0, 16*4);
  printEfont("Päivää", 0, 16*6);
  printEfont("Здравствуйте", 0, 16*7);
}

void loop() {
}
```
