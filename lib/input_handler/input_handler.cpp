#include "input_handler.h"

volatile int InputHandler::knobCounter = 0;
volatile bool InputHandler::knobPressed = false;
volatile bool InputHandler::button1Pressed = false;
volatile bool InputHandler::button2Pressed = false;
volatile unsigned long InputHandler::lastKnobPressTime = 0;
volatile unsigned long InputHandler::lastButton1PressTime = 0;
volatile unsigned long InputHandler::lastButton2PressTime = 0;
InputHandler *InputHandler::instance = nullptr;

InputHandler::InputHandler() : KNOB_CLK(KNOB_CLK_PIN), KNOB_DT(KNOB_DT_PIN), KNOB_SW(KNOB_SW_PIN), BUTTON_1(BUTTON_1_PIN)
{
    instance = this;
}

/**
 * @brief Initialize the input handler. Set up the pins and attach the interrupt service routines
 */
void InputHandler::init()
{
    pinMode(KNOB_CLK, INPUT);
    pinMode(KNOB_DT, INPUT);
    pinMode(KNOB_SW, INPUT_PULLUP);
    pinMode(BUTTON_1, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(KNOB_CLK), knobISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(KNOB_SW), buttonISR, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON_1), buttonISR, FALLING);
}

/**
 * @brief Get the next input event
 *
 * @return InputEvent
 */
InputEvent InputHandler::getEvent()
{
    noInterrupts();
    InputEvent event = InputEvent::NONE;

    if (knobCounter > 0)
    {
        event = InputEvent::KNOB_CW;
        knobCounter--;
    }
    else if (knobCounter < 0)
    {
        event = InputEvent::KNOB_CCW;
        knobCounter++;
    }
    else if (knobPressed)
    {
        event = InputEvent::KNOB_PRESS;
        knobPressed = false;
    }
    else if (button1Pressed)
    {
        event = InputEvent::BUTTON_1_PRESS;
        button1Pressed = false;
    }

    interrupts();
    return event;
}

/**
 * @brief Interrupt service routine for the knob rotation
 */
void InputHandler::knobISR()
{
    if (instance)
    {
        static unsigned long lastKnobTurnTime = 0;
        unsigned long currentTime = millis();

        if (currentTime - lastKnobTurnTime > DEBOUNCE_DELAY)
        {
            if (digitalRead(instance->KNOB_CLK) == digitalRead(instance->KNOB_DT))
            {
                instance->knobCounter++;
            }
            else
            {
                instance->knobCounter--;
            }
            lastKnobTurnTime = currentTime;
        }
    }
}

/**
 * @brief Interrupt service routine for any button
 */
void InputHandler::buttonISR()
{
    if (instance)
    {
        unsigned long currentTime = millis();

        if (digitalRead(instance->KNOB_SW) == LOW &&
            currentTime - instance->lastKnobPressTime > DEBOUNCE_DELAY)
        {
            instance->knobPressed = true;
            instance->lastKnobPressTime = currentTime;
        }
        else if (digitalRead(instance->BUTTON_1) == LOW &&
                 currentTime - instance->lastButton1PressTime > DEBOUNCE_DELAY)
        {
            instance->button1Pressed = true;
            instance->lastButton1PressTime = currentTime;
        }
    }
}