#pragma once

#include <config.h>
#include <Arduino.h>

enum class InputEvent
{
    NONE,
    KNOB_CW,
    KNOB_CCW,
    KNOB_PRESS,
    BUTTON_1_PRESS,
    BUTTON_2_PRESS
};

class InputHandler
{
public:
    InputHandler();
    void init();
    InputEvent getEvent();

private:
    static void knobISR();
    static void buttonISR();

    const uint8_t KNOB_CLK;
    const uint8_t KNOB_DT;
    const uint8_t KNOB_SW;
    const uint8_t BUTTON_1;
    // const uint8_t BUTTON_2;

    static volatile int knobCounter;
    static volatile bool knobPressed;
    static volatile bool button1Pressed;
    static volatile bool button2Pressed;

    static const unsigned long DEBOUNCE_DELAY = 150;
    static volatile unsigned long lastKnobPressTime;
    static volatile unsigned long lastButton1PressTime;
    static volatile unsigned long lastButton2PressTime;

    static InputHandler *instance;
};