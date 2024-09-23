#pragma once

#include <config.h>
#include <screen_manager.h>
#include <input_handler.h>

class Dashboard
{
public:
    Dashboard(ScreenManager *screenManager);
    virtual ~Dashboard() = default;
    virtual void init(uint8_t screenIndex) = 0;
    virtual void update() = 0;
    virtual void handleInput(InputEvent event) = 0;

protected:
    ScreenManager *screenManager;
};