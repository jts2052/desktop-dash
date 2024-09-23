#pragma once

#include <screen_manager.h>
#include <input_handler.h>
#include <dashboard.h>
#include "../ui_lib/ui_lib.h"
#include <utility>

class ClockDashboard : public Dashboard
{
public:
    ClockDashboard(ScreenManager *screenManager, UILib *uiLib);

    void init(uint8_t screenIndex);
    void update();
    void handleInput(InputEvent event) override;

private:
    ScreenManager *screenManager;
    UILib *uiLib;
    uint8_t screenIndex;
    String lastTime;
    std::pair<int, int> timePosition;
    void draw();
    void redrawTime();
};