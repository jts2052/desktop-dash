#pragma once

#include <TFT_eSPI.h>
#include <screen_manager.h>
#include <utility>

class UILib
{
public:
    UILib(ScreenManager *screenManager);
    void drawButton(int x, int y, int w, int h, const char *label, uint16_t color, uint16_t bgColor);
    void drawLabel(int x, int y, String text, uint16_t color, uint8_t textSize);
    void drawIcon(int x, int y, int width, int height, const unsigned short *iconData);
    void drawImageRow(int x, int y, int w, int h, const unsigned short *images[], int numImages);
    void drawImageColumn(int x, int y, int imageWidth, int imageHeight, const unsigned short *images[], int numImages);
    std::pair<int, int> centerIconX(int y, int elementWidth, int elementHeight, const unsigned short *image);
    std::pair<int, int> centerIconY(int x, int elementWidth, int elementHeight, const unsigned short *image);
    std::pair<int, int> centerTextX(int y, String text, uint16_t color, uint8_t textSize);
    std::pair<int, int> centerTextY(int x, String text, uint16_t color, uint8_t textSize);
    void clearArea(int x, int y, int w, int h);

private:
    ScreenManager *screenManager;
    TFT_eSPI *currentScreen;
};
