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
    // getCurrentWeatherData();
    draw();
    Serial.println("Weather Dashboard initialized.");
}

void WeatherDashboard::update()
{
    unsigned long currentTime = millis();

    if (currentTime - lastCurrentWeatherUpdate > currentWeatherInterval)
    {
        // getCurrentWeatherData();
        redrawCurrentWeather();
    }
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

    drawCurrentWeather();
    drawWeatherOutlook();
}

void WeatherDashboard::drawWeatherOutlook()
{
    int absCenter = TFT_WIDTH / 2;
    int weatherCenter = absCenter - 56;

    int futureWeatherY = 115;
    drawHourly(weatherCenter, futureWeatherY, "70", "0", sunny);

    futureWeatherY += 40;
    drawHourly(weatherCenter, futureWeatherY, "35", "15", snowy);

    futureWeatherY += 40;
    drawHourly(weatherCenter, futureWeatherY, "89", "15", sunny);
}

void WeatherDashboard::drawCurrentWeather()
{
    int absCenter = TFT_WIDTH / 2;
    int currentWeatherY = 40;

    screenManager->getScreen()->loadFont(NOTO_BOLD_48);

    String tempLabel;
    if (!(currentWeatherData.size() > 0))
    {
        tempLabel = "--°";
    }
    else
    {
        tempLabel = currentWeatherData[0] + "°";
    }

    int textHeight = screenManager->getScreen()->fontHeight();
    int textWidth = screenManager->getScreen()->textWidth(tempLabel);

    uiLib->drawLabel(absCenter - (textWidth / 2), currentWeatherY + (textHeight / 2), tempLabel, TFT_WHITE, 3);
}

void WeatherDashboard::redrawCurrentWeather()
{
    screenManager->getScreen()->loadFont(NOTO_BOLD_48);

    int textHeight = screenManager->getScreen()->fontHeight();

    screenManager->selectScreen(screenIndex);
    uiLib->clearArea(0, 40, TFT_WIDTH, textHeight);
    drawCurrentWeather();
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

void WeatherDashboard::getCurrentWeatherData()
{
    currentWeatherData = fetchCurrentWeatherData();
    lastCurrentWeatherUpdate = millis();
}

void WeatherDashboard::getFutureWeatherData()
{
    // futureWeatherData = fetchFutureWeatherData();
    // lastFutureWeatherUpdate = millis();
}