/*
 * Button.h
 *
 *  Created on: Jul 30, 2019
 *      Author: Matthew Zhong
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include <Timer.h>

#define PRESSED  0
#define RELEASED 1

#define NUM_BUTTONS 5

#define DEBOUNCE_MS 3

enum _ButtonTarget
{
	LP_BTN1 = 0, LP_BTN2, BP_BTN1, BP_BTN2, BP_BTN3
};
typedef enum _ButtonTarget ButtonTarget;

enum _DebounceState
{
	DB_Released, DB_Releasing, DB_Pressed, DB_Pressing
};
typedef enum _DebounceState DebounceState;

struct _Button
{
	uint_fast8_t port;
	uint_fast16_t pin;
	DebounceState debounceState;
	SWTimer* timer;
	bool hasBufferedTap;
	uint32_t history;
};
typedef struct _Button Button;

Button* Buttons_construct();
int Buttons_isHeld(ButtonTarget target);
int Buttons_isTapped(ButtonTarget target);
int Buttons_getRawState(ButtonTarget target);

void Buttons_refresh();

#endif /* BUTTON_H_ */
