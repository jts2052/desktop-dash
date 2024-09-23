#pragma once

#include <config.h>
#include <TFT_eSPI.h>

class ScreenManager
{
public:
    ScreenManager();
    void init();
    TFT_eSPI *getScreen();
    void selectScreen(int8_t index);
    void deselectAllScreens();
    int8_t getCurrentScreenIndex();
    uint8_t *getScreenDashboards();

    // Testing
    void clearAllScreens(int8_t curIndex);
    void debug();

private:
    TFT_eSPI screen;
    const uint8_t CS_PINS[NUM_SCREENS] = {SCREEN_1_CS, SCREEN_2_CS, SCREEN_3_CS, SCREEN_4_CS};
    const uint8_t SCREEN_DASHBOARDS[NUM_SCREENS] = {SCREEN_1_DASHBOARD, SCREEN_2_DASHBOARD, SCREEN_3_DASHBOARD, SCREEN_4_DASHBOARD};
    int8_t currentScreenIndex;
};