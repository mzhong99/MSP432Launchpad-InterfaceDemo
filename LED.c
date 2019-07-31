/*
 * LEDs.c
 *
 *  Created on: Jul 29, 2019
 *      Author: Matthew Zhong
 */
#include <Controller.h>
#include <LED.h>

#include <malloc.h>

LED* LEDs_construct()
{
    // Status of each pin is initialized because calloc will set as zero
    LED* leds = calloc(NUM_LEDS, sizeof(LED));

    leds[LP_L1].port = GPIO_PORT_P1;
    leds[LP_L1].pin  = GPIO_PIN0;

    leds[LP_RED].port = GPIO_PORT_P2;
    leds[LP_RED].pin  = GPIO_PIN0;

    leds[LP_GRN].port = GPIO_PORT_P2;
    leds[LP_GRN].pin  = GPIO_PIN1;

    leds[LP_BLU].port = GPIO_PORT_P2;
    leds[LP_BLU].pin  = GPIO_PIN2;

    leds[BP_RED].port = GPIO_PORT_P2;
    leds[BP_RED].pin  = GPIO_PIN6;

    leds[BP_GRN].port = GPIO_PORT_P2;
    leds[BP_GRN].pin  = GPIO_PIN4;

    leds[BP_BLU].port = GPIO_PORT_P5;
    leds[BP_BLU].pin  = GPIO_PIN6;

    for (int i = 0; i < NUM_LEDS; i++) {
        GPIO_setAsOutputPin(leds[i].port, leds[i].pin);
        GPIO_setOutputLowOnPin(leds[i].port, leds[i].pin);
    }

    return leds;
}

void LEDs_turnOn(LEDTarget target)
{
    LED* leds = Controller_getInstance()->leds;
    uint_fast8_t port = leds[target].port;
    uint_fast16_t pin = leds[target].pin;

    GPIO_setOutputHighOnPin(port, pin);
    leds[target].status = LED_ON;
}

void LEDs_turnOff(LEDTarget target)
{
    LED* leds = Controller_getInstance()->leds;
    uint_fast8_t port = leds[target].port;
    uint_fast16_t pin = leds[target].pin;

    GPIO_setOutputLowOnPin(port, pin);
    leds[target].status = LED_OFF;
}

void LEDs_toggle(LEDTarget target)
{
    LED* leds = Controller_getInstance()->leds;
    uint_fast8_t port = leds[target].port;
    uint_fast16_t pin = leds[target].pin;

    GPIO_toggleOutputOnPin(port, pin);
    leds[target].status = !leds[target].status;
}

int LEDs_getStatus(LEDTarget target)
{
    LED* leds = Controller_getInstance()->leds;
    return leds[target].status;
}

void LEDs_turnOffAll(void)
{
    LED* leds = Controller_getInstance()->leds;

    for (int i = 0; i < NUM_LEDS; i++) {
        GPIO_setOutputLowOnPin(leds[i].port, leds[i].pin);
    }
}
