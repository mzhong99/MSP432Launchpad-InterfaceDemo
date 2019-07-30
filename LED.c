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

    leds[LP_1].port = GPIO_PORT_P1;
    leds[LP_1].pin  = GPIO_PIN0;

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
    Controller* controller = Controller_getInstance();
    uint_fast8_t port = controller->leds[target].port;
    uint_fast16_t pin = controller->leds[target].pin;

    GPIO_setOutputHighOnPin(port, pin);
    controller->leds[target].status = LED_ON;
}

void LEDs_turnOff(LEDTarget target)
{
    Controller* controller = Controller_getInstance();
    uint_fast8_t port = controller->leds[target].port;
    uint_fast16_t pin = controller->leds[target].pin;

    GPIO_setOutputLowOnPin(port, pin);
    controller->leds[target].status = LED_OFF;
}

void LEDs_toggle(LEDTarget target)
{
    Controller* controller = Controller_getInstance();
    uint_fast8_t port = controller->leds[target].port;
    uint_fast16_t pin = controller->leds[target].pin;

    GPIO_toggleOutputOnPin(port, pin);
    controller->leds[target].status = !controller->leds[target].status;
}

int LEDs_getStatus(LEDTarget target)
{
    Controller* controller = Controller_getInstance();
    return controller->leds[target].status;
}

void LEDs_turnOffAll(void)
{
    Controller* controller = Controller_getInstance();

    for (int i = 0; i < NUM_LEDS; i++) {
        uint_fast8_t port = controller->leds[i].port;
        uint_fast16_t pin = controller->leds[i].pin;

        GPIO_setOutputLowOnPin(port, pin);
    }
}
