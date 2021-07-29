
#include <Arduino.h>
#include <efontWrapper.h>
#include <esp32-hal-log.h>
#include <efont.h>

EfontWrapper::EfontWrapper(int16_t w, int16_t h) : GraphicsLib(w, h) {}

#if !defined(ADAFRUIT_GFX)
EfontWrapper::EfontWrapper() : GraphicsLib() {}
#endif

EfontWrapper::~EfontWrapper(void) {}

void EfontWrapper::printEfont(const char *str, int x, int y) {
    setCursor(x, y);
    printEfont(str);
}

void EfontWrapper::printEfont(const char *str, int x, int y, uint8_t textsize) {
    setCursor(x, y);
    setTextSize(textsize);
    printEfont(str);
}

const char *EfontWrapper::_efontUFT8toUTF16(uint16_t *pUTF16, const char *pUTF8) {
    return efontUFT8toUTF16(pUTF16, pUTF8);
}

void EfontWrapper::_getefontData(uint8_t *font, uint16_t fontUTF16) {
    getefontData(font, fontUTF16);
}

void EfontWrapper::printEfont(const char *str) {
    int posX = getCursorX();
    int posY = getCursorY();
#if defined(ADAFRUIT_GFX)
    uint8_t textsize = GraphicsLib::textsize_y;
#elif defined(TFT_ESPI)
    uint8_t textsize = GraphicsLib::textsize;
#endif
    uint32_t textcolor   = GraphicsLib::textcolor;
    uint32_t textbgcolor = GraphicsLib::textbgcolor;

    byte font[32] = {0};

    while (*str != 0x00) {
        // 改行処理
        if (*str == '\n') {
            // 改行
            posY += 16 * textsize;
            posX = getCursorX();
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
        log_printf("str : U+%04X\n", strUTF16);
#endif

        // 背景塗りつぶし
        fillRect(posX, posY, width, 16 * textsize, textbgcolor);

        // 取得フォントの確認
        for (uint8_t row = 0; row < 16; row++) {
            word fontdata = font[row * 2] * 256 + font[row * 2 + 1];
            for (uint8_t col = 0; col < 16; col++) {
#ifdef EFONT_DEBUG
                log_printf("%s", ((0x8000 >> col) & fontdata) ? "#" : " ");
#endif
                if ((0x8000 >> col) & fontdata) {
                    int drawX = posX + col * textsize;
                    int drawY = posY + row * textsize;
                    if (textsize == 1) {
                        drawPixel(drawX, drawY, textcolor);
                    } else {
                        fillRect(drawX, drawY, textsize, textsize, textcolor);
                    }
                }
            }
#ifdef EFONT_DEBUG
            log_printf("\n");
#endif
        }

        // 描画カーソルを進める
        posX += width;

        // 折返し処理
        if (GraphicsLib::width() <= posX) {
            posX = 0;
            posY += 16 * textsize;
        }
    }

    // カーソルを更新
    setCursor(posX, posY);
}
