#include "dashboards/weather_dashboard.h"
#include "../images/cloud.h"
#include "../images/stormy.h"
#include "../images/sunny.h"
#include "../images/rainy.h"
#include "../images/snowy.h"

WeatherDashboard::WeatherDashboard(ScreenManager *screenManager, UILib *uiLib) : Dashboard(screenManager)
{
    this->screenManager = screenManager;
    this->uiLib = uiLib;
}

void WeatherDashboard::init(uint8_t screenIndex)
{
    this->screenIndex = screenIndex;
    draw();
    Serial.println("Weather Dashboard initialized.");
}

void WeatherDashboard::update()
{
}

void WeatherDashboard::handleInput(InputEvent event)
{
    if (event == InputEvent::KNOB_PRESS)
    {
        Serial.println("Weather Dashboard: Knob pressed.");
    }
    else if (event == InputEvent::KNOB_CW)
    {
        Serial.println("Weather Dashboard: Knob rotated clockwise.");
    }
    else if (event == InputEvent::KNOB_CCW)
    {
        Serial.println("Weather Dashboard: Knob rotated counter-clockwise.");
    }
}

void WeatherDashboard::draw()
{
    screenManager->selectScreen(screenIndex);
    uiLib->centerIconX(0, CLOUD_WIDTH, CLOUD_HEIGHT, cloud);

    drawWeatherOutlook();
    // fetchCurrentWeatherData();
}

void WeatherDashboard::drawWeatherOutlook()
{
    int absCenter = TFT_WIDTH / 2;
    int weatherCenter = absCenter - 56;
    int currentWeatherY = 40;
    drawCurrentWeather(absCenter, currentWeatherY, "65", "20");

    int futureWeatherY = 115;
    drawHourly(weatherCenter, futureWeatherY, "70", "0", sunny);

    futureWeatherY += 40;
    drawHourly(weatherCenter, futureWeatherY, "35", "15", snowy);

    futureWeatherY += 40;
    drawHourly(weatherCenter, futureWeatherY, "89", "15", sunny);
}

void WeatherDashboard::drawCurrentWeather(int x, int y, String temp, String precip)
{
    screenManager->getScreen()->loadFont(NOTO_BOLD_48);

    String tempLabel = temp + "°";

    int textHeight = screenManager->getScreen()->fontHeight();
    int textWidth = screenManager->getScreen()->textWidth(tempLabel);
    uiLib->drawLabel(x - (textWidth / 2), y + (textHeight / 2), tempLabel, TFT_WHITE, 3);
}

void WeatherDashboard::drawHourly(int x, int y, String temp, String precip, const unsigned short *iconData)
{
    int tempOffset = 40;
    int precipOffset = 75;
    screenManager->getScreen()->loadFont(NOTO_BOLD_15);
    int textHeight = screenManager->getScreen()->fontHeight();
    uiLib->drawIcon(x, y, SUNNY_WIDTH, SUNNY_HEIGHT, iconData); // All small icons same size
    uiLib->drawLabel(x + tempOffset, y + (textHeight / 2), temp + "°", TFT_WHITE, 1);
    uiLib->drawLabel(x + precipOffset, y + (textHeight / 2), precip + "%", TFT_WHITE, 1);
}