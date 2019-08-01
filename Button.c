/*
 * Button.c
 *
 *  Created on: Jul 30, 2019
 *      Author: Matthew Zhong
 */

#include <Controller.h>
#include <Button.h>

#include <malloc.h>

Button* Buttons_construct(void)
{
    Button* buttons = calloc(NUM_BUTTONS, sizeof(Button));

    buttons[LP_BTN1].port = GPIO_PORT_P1;
    buttons[LP_BTN1].pin  = GPIO_PIN1;

    buttons[LP_BTN2].port = GPIO_PORT_P1;
    buttons[LP_BTN2].pin  = GPIO_PIN4;

    buttons[BP_BTN1].port = GPIO_PORT_P5;
    buttons[BP_BTN1].pin  = GPIO_PIN1;

    buttons[BP_BTN2].port = GPIO_PORT_P3;
    buttons[BP_BTN2].pin  = GPIO_PIN5;

    buttons[BP_BTN3].port = GPIO_PORT_P4;
    buttons[BP_BTN3].pin  = GPIO_PIN1;

    // First, set every switch as a GPIO with no pull-up / pull-down resistor
    for (int i = 0; i < NUM_BUTTONS; i++) {
        GPIO_setAsInputPin(buttons[i].port, buttons[i].pin);
        buttons[i].history = 0xFFFFFFFF;
        buttons[i].debounceState = DB_Released;
        buttons[i].hasBufferedTap = false;
        buttons[i].timer = SWTimer_construct(DEBOUNCE_MS);
    }

    // Switches on the LaunchPad require pull up resistors
    GPIO_setAsInputPinWithPullUpResistor(buttons[LP_BTN1].port,
                                         buttons[LP_BTN1].pin);

    GPIO_setAsInputPinWithPullUpResistor(buttons[LP_BTN2].port,
                                         buttons[LP_BTN2].pin);

    return buttons;
}

int Buttons_isHeld(ButtonTarget target)
{
    Button* buttons = Controller_getInstance()->buttons;
    return buttons[target].debounceState == DB_Pressed
        || buttons[target].debounceState == DB_Pressing;
}

int Buttons_isTapped(ButtonTarget target)
{
    Button* buttons = Controller_getInstance()->buttons;
    int bufferedInput = buttons[target].hasBufferedTap;
    buttons[target].hasBufferedTap = false;
    return bufferedInput;
}

int Buttons_getRawState(ButtonTarget target)
{
    Button* buttons = Controller_getInstance()->buttons;
    return GPIO_getInputPinValue(buttons[target].port, buttons[target].pin);
}

void Buttons_refresh()
{
    Button* buttons = Controller_getInstance()->buttons;

    for (int i = 0; i < NUM_BUTTONS; i++) {
		int rawState = Buttons_getRawState(i);
        switch (buttons[i].debounceState)
        {
        	case DB_Released: {
        		if (rawState == PRESSED) {
        			SWTimer_start(buttons[i].timer);
        			buttons[i].debounceState = DB_Pressing;
        		}
        		buttons[i].hasBufferedTap = false;
        		break;
        	}
        	case DB_Pressed: {
        		if (rawState == RELEASED) {
        			SWTimer_start(buttons[i].timer);
        			buttons[i].debounceState = DB_Releasing;
        		}
        		break;
        	}
        	case DB_Releasing: {
        		if (rawState == PRESSED) {
        			buttons[i].debounceState = DB_Pressed;
        		}
        		else if (SWTimer_expired(buttons[i].timer)) {
        			buttons[i].debounceState = DB_Released;
        			buttons[i].hasBufferedTap = false;
        		}
        		break;
        	}
        	case DB_Pressing: {
        		if (rawState == RELEASED) {
        			buttons[i].debounceState = DB_Released;
        		}
        		else if (SWTimer_expired(buttons[i].timer)) {
        			buttons[i].debounceState = DB_Pressed;
        			buttons[i].hasBufferedTap = true;
        		}
        		break;
        	}
        }
    }
}
