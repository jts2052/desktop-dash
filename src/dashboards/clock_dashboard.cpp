#include "dashboards/clock_dashboard.h"
#include "../images/clock.h"
#include "wifi_client.h"

ClockDashboard::ClockDashboard(ScreenManager *screenManager, UILib *uiLib) : Dashboard(screenManager)
{
    this->screenManager = screenManager;
    this->uiLib = uiLib;
}

void ClockDashboard::init(uint8_t screenIndex)
{
    this->screenIndex = screenIndex;
    draw();
    Serial.println("Clock Dashboard initialized.");
}

void ClockDashboard::update()
{
    if (lastTime != getFormattedTime())
    {
        lastTime = getFormattedTime();
        redrawTime();
    }
}

void ClockDashboard::handleInput(InputEvent event)
{
    if (event == InputEvent::KNOB_PRESS)
    {
        Serial.println("Clock Dashboard: Knob pressed.");
    }
    else if (event == InputEvent::KNOB_CW)
    {
        Serial.println("Clock Dashboard: Knob rotated clockwise.");
    }
    else if (event == InputEvent::KNOB_CCW)
    {
        Serial.println("Clock Dashboard: Knob rotated counter-clockwise.");
    }
}

void ClockDashboard::draw()
{
    screenManager->selectScreen(screenIndex);
    uiLib->centerIconX(0, CLOCK_WIDTH, CLOCK_HEIGHT, clock_i);
    timePosition = uiLib->centerTextX(TFT_HEIGHT / 2, lastTime, TFT_WHITE, 3);
}

void ClockDashboard::redrawTime()
{
    screenManager->selectScreen(screenIndex);
    uiLib->clearArea((TFT_WIDTH - 2 * timePosition.first), timePosition.second, TFT_WIDTH, screenManager->getScreen()->fontHeight());
    timePosition = uiLib->centerTextX(TFT_HEIGHT / 2, lastTime, TFT_WHITE, 3);
}