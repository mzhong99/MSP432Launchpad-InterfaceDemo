/*
 * Demo.c
 *
 *  Created on: Jul 29, 2019
 *      Author: Matthew Zhong
 */

#include <Demo.h>
#include <LED.h>

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
