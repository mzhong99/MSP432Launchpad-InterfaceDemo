/*
 * LEDs.h
 *
 *  Created on: Jul 29, 2019
 *      Author: Matthew Zhong
 */

#ifndef LED_H_
#define LED_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define LED_ON  1
#define LED_OFF 0

#define NUM_LEDS 7

enum _LEDTarget { LP_1, LP_RED, LP_GRN, LP_BLU, BP_RED, BP_GRN, BP_BLU };
typedef enum _LEDTarget LEDTarget;

struct _LED
{
    uint_fast8_t port;
    uint_fast16_t pin;
    int status;
};
typedef struct _LED LED;

LED* LEDs_construct();
void LEDs_turnOn(LEDTarget target);
void LEDs_turnOff(LEDTarget target);
void LEDs_turnOffAll();
int LEDs_getStatus(LEDTarget target);
void LEDs_toggle(LEDTarget target);

#endif /* LED_H_ */
