#include "dashboards/music_dashboard.h"
#include "../images/music_note.h"
#include "../images/play_pause.h"
#include "../images/skip.h"
#include "../images/skip_prev.h"

MusicDashboard::MusicDashboard(ScreenManager *screenManager, UILib *uiLib) : Dashboard(screenManager)
{
    this->screenManager = screenManager;
    this->uiLib = uiLib;
}

void MusicDashboard::init(uint8_t screenIndex)
{
    this->screenIndex = screenIndex;
    draw();
    Serial.println("Music Dashboard initialized.");
}

void MusicDashboard::update()
{
}

void MusicDashboard::handleInput(InputEvent event)
{
    if (event == InputEvent::KNOB_PRESS)
    {
        Serial.println("Music Dashboard: Knob pressed.");
    }
    else if (event == InputEvent::KNOB_CW)
    {
        Serial.println("Music Dashboard: Knob rotated clockwise.");
    }
    else if (event == InputEvent::KNOB_CCW)
    {
        Serial.println("Music Dashboard: Knob rotated counter-clockwise.");
    }
}

void MusicDashboard::draw()
{
    screenManager->selectScreen(screenIndex);
    uiLib->centerIconX(0, MUSIC_NOTE_WIDTH, MUSIC_NOTE_HEIGHT, music_note);
    // std::pair<int, int> centerCoords = uiLib->centerIconX((TFT_HEIGHT - TFT_HEIGHT / 3), PLAY_PAUSE_WIDTH, PLAY_PAUSE_HEIGHT, play_pause);
    // int x = centerCoords.first - (PLAY_PAUSE_WIDTH / 2);
    // int y = centerCoords.second;
    int absCenter = TFT_WIDTH / 2;
    int centerX = (TFT_WIDTH - PLAY_PAUSE_WIDTH) / 2;
    int playPauseY = (TFT_HEIGHT - (TFT_HEIGHT / 3));
    uiLib->drawIcon(centerX, playPauseY, PLAY_PAUSE_WIDTH, PLAY_PAUSE_HEIGHT, play_pause);
    uiLib->drawIcon(absCenter + (PLAY_PAUSE_WIDTH / 2), playPauseY + ((PLAY_PAUSE_HEIGHT - SKIP_NEXT_HEIGHT) / 2), SKIP_NEXT_WIDTH, SKIP_NEXT_HEIGHT, skip_next);
    uiLib->drawIcon(absCenter - (PLAY_PAUSE_WIDTH / 2 + SKIP_PREVIOUS_WIDTH), playPauseY + ((PLAY_PAUSE_HEIGHT - SKIP_NEXT_HEIGHT) / 2), SKIP_PREVIOUS_WIDTH, SKIP_PREVIOUS_HEIGHT, skip_previous);
}