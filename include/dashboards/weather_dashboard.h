#pragma once

#include <screen_manager.h>
#include <input_handler.h>
#include <dashboard.h>
#include "../ui_lib/ui_lib.h"
#include <wifi_client.h>

class WeatherDashboard : public Dashboard
{
public:
    WeatherDashboard(ScreenManager *screenManager, UILib *uiLib);

    void init(uint8_t screenIndex);
    void update();
    void handleInput(InputEvent event) override;

private:
    ScreenManager *screenManager;
    UILib *uiLib;
    uint8_t screenIndex;
    void draw();
    void drawCurrentWeather(int x, int y, String temp, String precip);
    void drawWeatherOutlook();
    void drawHourly(int x, int y, String temp, String precip, const unsigned short *iconData);
    void drawDaily(int x, int y, String low, String high, String precip, const unsigned short *iconData);
};