#pragma once

#include <screen_manager.h>
#include <input_handler.h>
#include <dashboard.h>
#include "../ui_lib/ui_lib.h"
#include <utility>

class MusicDashboard : public Dashboard
{
public:
    MusicDashboard(ScreenManager *screenManager, UILib *uiLib);

    void init(uint8_t screenIndex);
    void update();
    void handleInput(InputEvent event) override;

private:
    ScreenManager *screenManager;
    UILib *uiLib;
    uint8_t screenIndex;
    void draw();
};