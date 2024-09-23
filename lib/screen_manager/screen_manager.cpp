#include "screen_manager.h"

ScreenManager::ScreenManager()
{
}

/**
 * @brief Initialize the screen manager. Set up the CS pins and initialize the TFT_eSPI object
 */
void ScreenManager::init()
{
    for (int i = 0; i < NUM_SCREENS; i++)
    {
        pinMode(CS_PINS[i], OUTPUT);
        digitalWrite(CS_PINS[i], LOW);
    }

    screen.init();
    screen.setRotation(0);

    currentScreenIndex = 0;
}

/**
 * @brief Get the TFT_eSPI object
 *
 * @return TFT_eSPI*
 */
TFT_eSPI *ScreenManager::getScreen()
{
    return &screen;
}

/**
 * @brief Select a screen by turning the corresponding CS pin HIGH
 *
 * @param index The index of the screen to select
 */
void ScreenManager::selectScreen(int8_t index)
{
    if (index >= 0 && index < NUM_SCREENS)
    {
        deselectAllScreens();
        digitalWrite(CS_PINS[index], LOW);
        currentScreenIndex = index;
    }
}

/**
 * @brief Deselect all screens by turning all CS pins LOW
 */
void ScreenManager::deselectAllScreens()
{
    for (int i = 0; i < NUM_SCREENS; i++)
    {
        digitalWrite(CS_PINS[i], HIGH);
    }
}

/**
 * @brief Get the index of the currently selected screen
 *
 * @return int8_t
 */
int8_t ScreenManager::getCurrentScreenIndex()
{
    return currentScreenIndex;
}

/**
 * @brief Get the array of screen dashboards
 *
 * @return uint8_t*
 */
uint8_t *ScreenManager::getScreenDashboards()
{
    return (uint8_t *)SCREEN_DASHBOARDS;
}

// Testing functions
void ScreenManager::clearAllScreens(int8_t curIndex)
{
    for (int i = 0; i < NUM_SCREENS; i++)
    {
        selectScreen(i);
        screen.fillScreen(TFT_BLACK);
    }
    currentScreenIndex = curIndex;
    selectScreen(curIndex);
}

void ScreenManager::debug()
{
    Serial.printf("Current screen index: %d\n", currentScreenIndex);
    for (int i = 0; i < NUM_SCREENS; i++)
    {
        Serial.printf("CS pin %d: %d\n", i, CS_PINS[i]);
        Serial.printf("CS pin %d state: %d\n", i, digitalRead(CS_PINS[i]));
    }
}