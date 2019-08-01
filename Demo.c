/*
 * Demo.c
 *
 *  Created on: Jul 29, 2019
 *      Author: Matthew Zhong
 */

#include <Demo.h>

#include <Controller.h>
#include <Timer.h>

void Demo_showLEDs()
{
    for (int ledsToShow = 0; ledsToShow < (1 << NUM_LEDS); ledsToShow++) {
        LEDs_turnOffAll();
        for (int led = 0; led < NUM_LEDS; led++) {
            if ((1 << led) & ledsToShow) {
                LEDs_turnOn(led);
            }
        }
        for (int i = 0; i < 1000000; i++); // delay without timer
    }
}

void Demo_showTimerLEDs()
{
    static SWTimer* timer;
    static enum { Init, FlashOn, FlashOff } state;
    switch (state)
    {
        case Init: {
            timer = SWTimer_construct(125);
            LEDs_turnOn(LP_L1);
            state = FlashOn;
            break;
        }
        case FlashOn: {
            if (SWTimer_expired(timer)) {
                SWTimer_start(timer);
                LEDs_turnOff(LP_L1);
                state = FlashOff;
            }
            break;
        }
        case FlashOff: {
            if (SWTimer_expired(timer)) {
                SWTimer_start(timer);
                LEDs_turnOn(LP_L1);
                state = FlashOn;
            }
            break;
        }
    }
}

void Demo_showButtons()
{
	int oldL1Status = LEDs_getStatus(LP_L1);
	LEDs_turnOffAll();
	if (oldL1Status == LED_ON) { LEDs_turnOn(LP_L1); }

	for (int i = 0; i < NUM_BUTTONS; i++) {
		if (Buttons_isTapped(i)) {
			LEDs_toggle(LP_L1);
		}
	}

	if (Buttons_isHeld(BP_BTN1)) { LEDs_turnOn(BP_RED); }
	if (Buttons_isHeld(BP_BTN2)) { LEDs_turnOn(BP_GRN); }
	if (Buttons_isHeld(BP_BTN3)) { LEDs_turnOn(BP_BLU); }

	if (Buttons_isHeld(LP_BTN1)) { LEDs_turnOn(LP_RED); }
	if (Buttons_isHeld(LP_BTN2)) { LEDs_turnOn(LP_BLU); }
}
