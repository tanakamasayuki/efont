# efont Font Data(PROGMEM)

http://openlab.ring.gr.jp/efont/unicode/

/efont/ Unicode Font をArduinoで使えるようにしました。

## 概要

/efont/ Unicode Fontに収録されているf16.bdfとb16.bdfを利用して1文字32バイトの16ピクセルフォントデータです。
全角文字はf16.bdfを利用し、U+00FFまでの文字は半角としb16.bdfを利用しています。

## 使い方

ダウンロードしたフォルダをArduinoのlibrariesフォルダにコピーをするか、必要なファイルだけプロジェクトの中にコピーしてください。

## フォントサイズを減らす方法

フォントは1文字単位で管理されており、1文字単位で読み込まない設定が可能です。
全21,729文字だと721Kのフォントデータになります。

efont.hより前に、読み込みフォントを指定することで、文字数を制御できます。


```
//#include "efontEnableAll.h"
//#include "efontEnableAscii.h"
//#include "efontEnableCJK.h"
#include "efontEnableJa.h"
#include "efont.h"
```

efontEnableJaMini.hは常用漢字と表外漢字とよく使いそうな記号が使え、一部の旧字や中国語、ハングル文字、諸外国語などは使えないコンパクトなフォントデータです。

## フォントサイズ

| 対象            | オプション          | 文字数 | フォント容量 |
|-----------------|---------------------|--------|--------------|
| すべて          | efontEnableAll.h    | 21,727 | 738,718      |
| Ascii           | efontEnableAscii.h  | 191    | 6,494        |
| CJK漢字         | efontEnableCJK.h    | 19,379 | 658,886      |
| 簡体字中国語    | efontEnableCn.h     | 18,077 | 614,618      |
| 日本語          | efontEnableJa.h     | 10,835 | 368,390      |
| 日本語(常用＋α) | efontEnableJaMini.h | 4,107  | 139,638      |
| 韓国語          | efontEnableKr.h     | 8,319  | 282,846      |
| 繁体字中国語    | efontEnableTw.h     | 13,555 | 460,870      |

## M5StickC以外での利用方法

描画周りについては機種ごとに違うため、各自機種に合わせて作り直してください。

## サンプルコード
```
#include <M5StickC.h>
#include "efontEnableJa.h"
#include "efontM5StickC.h"

void setup() {
  M5.begin();
  M5.Lcd.setRotation(0);
  M5.Lcd.setCursor(0, 0);

  printEfont("新しい朝が来た", 0, 16*0);
}

void loop() {
}
```
