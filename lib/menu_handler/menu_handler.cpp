#include "menu_handler.h"
#include "../../include/dashboards/music_dashboard.h"
#include <Arduino.h>

// extern DashboardManager dashboardManager;

MenuHandler::MenuHandler()
{
    this->menuActive = false;
    this->editMenuActive = false;
    this->currentScreenIndex = 0;
}

void MenuHandler::setScreenManager(ScreenManager *screenManager)
{
    this->screenManager = screenManager;
    this->currentScreen = screenManager->getScreen();
}

void MenuHandler::setDashboardManager(DashboardManager *dashboardManager)
{
    this->dashboardManager = dashboardManager;
}

void MenuHandler::init()
{
}

void MenuHandler::handleInput(InputEvent event)
{
    if (event == InputEvent::KNOB_PRESS)
    {
        if (!menuActive)
        {
            enterMenu();
        }
        else
        {
            exitMenu();
        }
    }
    else if (menuActive)
    {
        if (event == InputEvent::KNOB_CW)
        {
            if (editMenuActive)
            {
                // dashboardManager->handleInput(event, currentScreenIndex);
                Serial.printf("DashboardManager address in MenuHandler: %p\n", dashboardManager);
                if (dashboardManager != nullptr)
                {
                    dashboardManager->handleInput(event, currentScreenIndex);
                }
                else
                {
                    Serial.println("Error: dashboardManager is nullptr");
                }
                return;
            }
            // Handle clockwise rotation in the menu
            editMenuActive = false; // TODO: For now, just exit edit menu. Later on send event to specific dashboard to handle it

            currentScreenIndex = (currentScreenIndex + 1) % NUM_SCREENS;
            Serial.printf("Menu active - Current screen: %d\n", currentScreenIndex);

            clearAllScreenSelections();
            screenManager->selectScreen(currentScreenIndex);
            drawSelectionIndicator();
        }
        else if (event == InputEvent::KNOB_CCW)
        {
            // Handle counter-clockwise rotation in the menu
            // ** Note: Since CCW rot not working, just make this go CW **
            editMenuActive = false; // TODO: For now, just exit edit menu. Later on send event to specific dashboard to handle it

            currentScreenIndex = (currentScreenIndex + 1) % NUM_SCREENS;
            Serial.printf("Menu active - Current screen: %d\n", currentScreenIndex);

            clearAllScreenSelections();
            screenManager->selectScreen(currentScreenIndex);
            drawSelectionIndicator();
        }
        else if (event == InputEvent::BUTTON_1_PRESS)
        {
            if (editMenuActive)
            {
                Serial.printf("Menu active - Exited menu - Selected screen: %d\n", currentScreenIndex);
                editMenuActive = false;
                drawSelectionIndicator();
            }
            else
            {
                Serial.printf("Menu active - Selected screen: %d\n", currentScreenIndex);
                editMenuActive = true;
                drawSelectedScreenIndicator();
            }
        }
    }
}

void MenuHandler::enterMenu()
{
    menuActive = true;
    Serial.println("Entered Menu");
    drawSelectionIndicator();
}

void MenuHandler::exitMenu()
{
    menuActive = false;
    editMenuActive = false;
    Serial.println("Exited Menu");
    clearAllScreenSelections();
}

bool MenuHandler::isMenuActive()
{
    return menuActive;
}

int8_t MenuHandler::getCurrentScreenInMenu()
{
    return currentScreenIndex;
}

void MenuHandler::drawSelectionIndicator()
{
    currentScreen->drawEllipse(TFT_WIDTH / 2, TFT_WIDTH / 2, TFT_WIDTH / 2 - 1, TFT_WIDTH / 2 - 1, TFT_WHITE);
}

void MenuHandler::drawSelectedScreenIndicator()
{
    currentScreen->drawEllipse(TFT_WIDTH / 2, TFT_WIDTH / 2, TFT_WIDTH / 2 - 1, TFT_WIDTH / 2 - 1, TFT_RED);
}

void MenuHandler::clearSelectionIndicator()
{
    currentScreen->drawEllipse(TFT_WIDTH / 2, TFT_WIDTH / 2, TFT_WIDTH / 2 - 1, TFT_WIDTH / 2 - 1, TFT_BLACK);
}

void MenuHandler::clearAllScreenSelections()
{
    for (int i = 0; i < NUM_SCREENS; i++)
    {
        screenManager->selectScreen(i);
        clearSelectionIndicator();
    }
    screenManager->selectScreen(currentScreenIndex);
}