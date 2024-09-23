#include <Arduino.h>
#include <TFT_eSPI.h>
#include <config.h>
#include <screen_manager.h>
#include <input_handler.h>
#include <menu_handler.h>
#include <ui_lib.h>
#include <dashboard_manager.h>
#include "dashboards/music_dashboard.h"
#include "dashboards/weather_dashboard.h"
#include "dashboards/clock_dashboard.h"
#include <wifi_client.h>

ScreenManager screenManager;
DashboardManager dashboardManager;
TFT_eSPI currentScreen = *screenManager.getScreen();
InputHandler inputHandler;
MenuHandler menuHandler;
UILib uiLib(&screenManager);

// put function declarations here:
void initializeDashboards();

void setup(void)
{
  Serial.begin(115200);

  setupWiFi();

  screenManager.init();
  inputHandler.init();

  dashboardManager.setScreenManager(&screenManager);

  menuHandler.setScreenManager(&screenManager);
  menuHandler.setDashboardManager(&dashboardManager);

  screenManager.clearAllScreens(0);

  initializeDashboards();
}

void loop()
{
  InputEvent event = inputHandler.getEvent();
  menuHandler.handleInput(event);

  dashboardManager.update();
}

void initializeDashboards()
{
  uint8_t *screenDashboards = screenManager.getScreenDashboards();
  Dashboard **dashboards = new Dashboard *[NUM_SCREENS];
  for (int i = 0; i < NUM_SCREENS; i++)
  {
    dashboards[i] = nullptr;
  }

  for (int i = 0; i < NUM_SCREENS; i++)
  {
    screenManager.selectScreen(i);
    currentScreen.fillScreen(TFT_BLACK);

    switch (screenDashboards[i])
    {
    case 0:
      Serial.println("None");
      // uiLib.drawLabel(120, 120, "None", TFT_WHITE, 2);
      dashboards[i] = new MusicDashboard(&screenManager, &uiLib);
      break;
    case 1:
      Serial.println("Clock");
      // uiLib.drawLabel(120, 120, "Clock", TFT_WHITE, 2);
      dashboards[i] = new ClockDashboard(&screenManager, &uiLib);
      break;
    case 2:
      Serial.println("Weather");
      // uiLib.drawLabel(120, 120, "Weather", TFT_WHITE, 2);
      dashboards[i] = new WeatherDashboard(&screenManager, &uiLib);
      break;
    case 3:
      Serial.println("Music");
      // uiLib.drawLabel(120, 120, "Music", TFT_WHITE, 2);
      dashboards[i] = new MusicDashboard(&screenManager, &uiLib);
      break;
    }
  }

  dashboardManager.setDashboards(dashboards);
  dashboardManager.init();

  Serial.printf("Dashboard Manager address in main.cpp: %p\n", &dashboardManager);
}