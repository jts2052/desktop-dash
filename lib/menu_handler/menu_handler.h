#pragma once

#include <TFT_eSPI.h>
#include <screen_manager.h>
#include <input_handler.h>
#include <dashboard_manager.h>

class MenuHandler
{
public:
    MenuHandler();
    void setScreenManager(ScreenManager *screenManager);
    void setDashboardManager(DashboardManager *dashboardManager);
    void init();
    void handleInput(InputEvent event);
    void enterMenu();
    void exitMenu();
    bool isMenuActive();
    int8_t getCurrentScreenInMenu();

private:
    bool menuActive;
    bool editMenuActive;
    int8_t currentScreenIndex;
    ScreenManager *screenManager;
    TFT_eSPI *currentScreen;
    DashboardManager *dashboardManager;

    void drawSelectionIndicator();
    void drawSelectedScreenIndicator();
    void clearSelectionIndicator();
    void clearAllScreenSelections();
};