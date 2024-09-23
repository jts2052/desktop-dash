#include <Arduino.h>
#include "ui_lib.h"

UILib::UILib(ScreenManager *screenManager)
{
    this->screenManager = screenManager;
    this->currentScreen = screenManager->getScreen();
}

/**
 * Draw a button on the screen
 *
 * @param x The x coordinate of the top-left corner of the button
 * @param y The y coordinate of the top-left corner of the button
 * @param w The width of the button
 * @param h The height of the button
 * @param label The text to display on the button
 * @param color The color of the text
 * @param bgColor The background color of the button
 */
void UILib::drawButton(int x, int y, int w, int h, const char *label, uint16_t color, uint16_t bgColor)
{
    currentScreen->fillRoundRect(x, y, w, h, 5, bgColor);
    currentScreen->drawRoundRect(x, y, w, h, 5, color);
    currentScreen->setTextColor(color, bgColor);
    currentScreen->setTextSize(1);
    currentScreen->setTextFont(1);
    currentScreen->drawString(label, x + 5, y + 5);
}

/**
 * Load a font for the screen
 *
 * @param textSize The size of the text
 */
void UILib::loadNotoFont(uint8_t textSize)
{
    switch (textSize)
    {
    case 1:
        currentScreen->loadFont(NOTO_BOLD_15);
        break;
    case 2:
        currentScreen->loadFont(NOTO_BOLD_36);
        break;
    case 3:
        currentScreen->loadFont(NOTO_BOLD_48);
        break;
    case 4:
        currentScreen->loadFont(NOTO_BOLD_72);
        break;
    }
}

/**
 * Draw a label on the screen
 *
 * @param x The x coordinate of the top-left corner of the label
 * @param y The y coordinate of the top-left corner of the label
 * @param text The text to display
 * @param color The color of the text
 * @param textSize The size of the text
 */
void UILib::drawLabel(int x, int y, String text, uint16_t color, uint8_t textSize)
{
    loadNotoFont(textSize);
    currentScreen->setTextColor(color);
    currentScreen->drawString(text, x, y);
}

/**
 * Draw an icon on the screen
 *
 * @param x The x coordinate of the top-left corner of the icon
 * @param y The y coordinate of the top-left corner of the icon
 * @param width The width of the icon
 * @param height The height of the icon
 * @param iconData The icon data
 */
void UILib::drawIcon(int x, int y, int width, int height, const unsigned short *iconData)
{
    currentScreen->pushImage(x, y, width, height, iconData, TFT_BLACK);
}

void UILib::drawImageRow(int x, int y, int w, int h, const unsigned short *images[], int numImages)
{
    int elementWidth = w / numImages; // Divide the row width by the number of images

    for (int i = 0; i < numImages; i++)
    {
        // Draw each image at the specified location
        drawIcon(x + (i * elementWidth), y, elementWidth, h, images[i]);
    }
}

void UILib::drawImageColumn(int x, int y, int imageWidth, int imageHeight, const unsigned short *images[], int numImages)
{
    int totalHeight = imageHeight * numImages; // Total height occupied by all images
    for (int i = 0; i < numImages; i++)
    {
        // Draw each image with spacing between them if needed
        drawIcon(x, y + (i * imageHeight), imageWidth, imageHeight, images[i]);
    }
}

std::pair<int, int> UILib::centerIconX(int y, int elementWidth, int elementHeight, const unsigned short *image)
{
    int centerX = (TFT_WIDTH - elementWidth) / 2;

    drawIcon(centerX, y, elementWidth, elementHeight, image);

    return std::make_pair(centerX, y);
}

std::pair<int, int> UILib::centerIconY(int x, int elementWidth, int elementHeight, const unsigned short *image)
{
    int centerY = (TFT_HEIGHT - elementHeight) / 2;

    drawIcon(x, centerY, elementWidth, elementHeight, image);

    return std::make_pair(x, centerY);
}

std::pair<int, int> UILib::centerTextX(int y, String text, uint16_t color, uint8_t textSize)
{
    loadNotoFont(textSize);

    uint16_t textWidth = currentScreen->textWidth(text);

    int centerX = (TFT_WIDTH - textWidth) / 2;

    currentScreen->drawString(text, centerX, y);

    return std::make_pair(centerX, y);
}

std::pair<int, int> UILib::centerTextY(int x, String text, uint16_t color, uint8_t textSize)
{
    loadNotoFont(textSize);

    uint16_t textHeight = currentScreen->fontHeight();

    int centerY = (TFT_HEIGHT - textHeight) / 2;

    currentScreen->drawString(text, x, centerY);

    return std::make_pair(x, centerY);
}

std::pair<int, int> UILib::centerTextXY(String text, uint16_t color, uint8_t textSize)
{
    loadNotoFont(textSize);

    uint16_t textWidth = currentScreen->textWidth(text);
    uint16_t textHeight = currentScreen->fontHeight();

    int centerX = (TFT_WIDTH - textWidth) / 2;
    int centerY = (TFT_HEIGHT - textHeight) / 2;

    currentScreen->drawString(text, centerX, centerY);

    return std::make_pair(centerX, centerY);
}

/**
 * Clear a specific area on the screen
 *
 * @param x The x coordinate of the top-left corner of the area
 * @param y The y coordinate of the top-left corner of the area
 * @param w The width of the area
 * @param h The height of the area
 */
void UILib::clearArea(int x, int y, int w, int h)
{
    currentScreen->fillRect(x, y, w, h, TFT_BLACK);
}