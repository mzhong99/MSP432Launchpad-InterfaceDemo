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
    }

    // Switches on the LaunchPad require pull up resistors
    GPIO_setAsInputPinWithPullUpResistor(buttons[LP_BTN1].port,
                                         buttons[LP_BTN1].pin);

    GPIO_setAsInputPinWithPullUpResistor(buttons[LP_BTN2].port,
                                         buttons[LP_BTN2].pin);

    return buttons;
}

int Buttons_isDown(ButtonTarget target)
{
    return Buttons_getRawState(target) == PRESSED;
}

int Buttons_getRawState(ButtonTarget target)
{
    Button* buttons = Controller_getInstance()->buttons;
    return GPIO_getInputPinValue(buttons[target].port, buttons[target].pin);
}
