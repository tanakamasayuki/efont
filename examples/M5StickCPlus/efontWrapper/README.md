# efontWrapper for ESP32

  - [🍀 Overview](#-overview)
  - [🔨 How to use](#-how-to-use)
    - [📂 Copy the efont library to the library folder](#-copy-the-efont-library-to-the-library-folder)
    - [📝 Modify efontWrapper.h](#-modify-efontwrapperh)
      - [📝 Using TFT_eSPI Library](#-using-tft_espi-library)
      - [📝 Using Adafruit_GFX Library](#-using-adafruit_gfx-library)
      - [📝 Select a font](#-select-a-font)
    - [👖　Apply a patch to the M5Display library](#apply-a-patch-to-the-m5display-library)
  - [📝 License](#-license)
  - [👤 Author](#-author)

## 🍀 Overview

I have turned the [efont library][efontURL] into a class library.
I derived efontWrapper from the [Adafruit_GFX][AdafruitGFX] library or the [TFT_eSPI][TFTeSPI] library.

## 🔨 How to use

### 📂 Copy the efont library to the library folder

**Arduino**

Copy the efont library to the library folder

```powershell:example
C:\Users\{{username}}\Documents\Arduino
```

**PlatformIO**

Edit the platformio.ini file.

```ini:(example)platformio.ini
lib_deps =
        https://github.com/m5stack/M5StickC-Plus.git@0.0.2
        https://github.com/tanakamasayuki/efont.git
```

### 📝 Modify efontWrapper.h

#### 📝 Using TFT_eSPI Library

If you are using the `M5Display` library with [M5Stack](https://github.com/m5stack/M5Stack) or [M5StickC](https://github.com/m5stack/M5StickC) to control any display unit, change `TFT_eSPI` to the derivation source and use `EfontWrapper` Class.
To make the change effective, modify the preprocessor in `efontWrapper.h` as follows

```cpp:efontWrapper.h
#define TFT_ESPI
```

#### 📝 Using Adafruit_GFX Library

If you are using the [Adafruit_GFX][AdafruitGFX] library to control any display unit (LED matrix, TFT display, etc.) with the ESP32, you should change the derivation of [Adafruit_GFX][AdafruitGFX] to use the `EfontWrapper` class.
To make the change effective, modify the preprocessor in `efontWrapper.h` as follows

```cpp:efontWrapper.h
#define ADAFRUIT_GFX
```

#### 📝 Select a font

You can modify the following preprocessor to select the [`efont Unicode BDF Font Data`][efontURL] you want to use.

```cpp:efontWrapper.h
#define EFONTENABLEJAMINI

~

#if defined(EFONTENABLEALL)
#include <efontEnableAll.h>
#endif
#if defined(EFONTENABLEASCII)
#include <efontEnableAscii.h>
#endif
#if defined(EFONTENABLECJK)
#include <efontEnableCJK.h>
#endif
#if defined(EFONTENABLECN)
#include <efontEnableCn.h>
#endif
#if defined(EFONTENABLEJA)
#include "efontEnableJa.h"
#elif defined(EFONTENABLEJAMINI)
#include <efontEnableJaMini.h>
#endif
#if defined(EFONTENABLEKR)
#include <efontEnableKr.h>
#endif
#if defined(EFONTENABLETW)
#include <efontEnableTw.h>
#endif
```

### 👖　Apply a patch to the M5Display library

I have made modifications to the `M5Display` class library in order to use efontWrapper.
The version of the M5StickCPlus library is [0.0.2]().
Please apply the following patch to `M5Display.cpp` and `M5Display.h.`
Execute the following command in the directory hierarchy where the two files are located.

```bash
git apply 0.0.2toDiff.patch
```

The `M5Display` class is derived from the `TFT_eSPI` class.
I have modified the class from which the `M5Display` class is derived (`TFT_eSPI`) to change it to the `EfontWrapper` class at compile time.

## 📝 License

This software is released under the [MIT](https://github.com/riraosan/ESP32_ntp_clock/blob/main/LICENSE) License.

## 👤 Author

If I can contribute something to you, I will be happy.

- GitHub: [riraosan](https://github.com/riraosan)
- Qiita: [riaosan](https://qiita.com/riraosan)

> _Serenity Prayer_
>
> God, grant me the serenity to accept the things I cannot change
> courage to change the things I can,
> and wisdom to know the difference.
> [_Reinhold Niebuhr_](https://en.wikipedia.org/wiki/Reinhold_Niebuhr)


[Google]: http://www.google.co.jp
[efontURL]: https://github.com/tanakamasayuki/efont
[AdafruitGFX]: https://github.com/adafruit/Adafruit-GFX-Library
[TFTeSPI]: https://github.com/Bodmer/TFT_eSPI
