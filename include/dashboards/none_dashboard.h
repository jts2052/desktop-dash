#pragma once

#include <screen_manager.h>
#include <input_handler.h>
#include <dashboard.h>
#include "../ui_lib/ui_lib.h"

class NoneDashboard : public Dashboard
{
public:
    NoneDashboard(ScreenManager *screenManager, UILib *uiLib);

    void init(uint8_t screenIndex);
    void update();
    void handleInput(InputEvent event) override;
};