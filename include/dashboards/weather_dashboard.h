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
    std::vector<String> currentWeatherData;
    std::vector<String> futureWeatherData;

    unsigned long lastCurrentWeatherUpdate = 0;
    unsigned long lastFutureWeatherUpdate = 0;

    // Update intervals in milliseconds
    const unsigned long currentWeatherInterval = 15 * 60 * 1000; // 15 minutes
    const unsigned long futureWeatherInterval = 30 * 60 * 1000;  // 30 minutes

    void draw();
    void drawCurrentWeather();
    void redrawCurrentWeather();
    void drawWeatherOutlook();
    void drawHourly(int x, int y, String temp, String precip, const unsigned short *iconData);
    void drawDaily(int x, int y, String low, String high, String precip, const unsigned short *iconData);
    void getCurrentWeatherData();
    void getFutureWeatherData();
};