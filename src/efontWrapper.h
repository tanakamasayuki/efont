
#pragma once

#if defined(ADAFRUIT_GFX)
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_I2CDevice.h>
using GraphicsLib = Adafruit_GFX;
#endif

#if defined(TFT_ESPI)
#include <utility/In_eSPI.h>
using GraphicsLib = TFT_eSPI;
#endif

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

class EfontWrapper : public GraphicsLib {
   public:
#if !defined(ADAFRUIT_GFX)
    EfontWrapper();
#endif 
    EfontWrapper(int16_t w, int16_t h);
    ~EfontWrapper(void);

    void printEfont(const char *str);
    void printEfont(const char *str, int x, int y);
    void printEfont(const char *str, int x, int y, uint8_t textsize);

   private:
    const char *_efontUFT8toUTF16(uint16_t *pUTF16, const char *pUTF8);
    void _getefontData(uint8_t *font, uint16_t fontUTF16);
};

