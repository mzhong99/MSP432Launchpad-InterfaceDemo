/*
 * Controller.h
 *
 *  Created on: Jul 29, 2019
 *      Author: Matthew Zhong
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <LED.h>
#include <Button.h>

struct _Controller
{
    LED* leds;
    Button* buttons;
};
typedef struct _Controller Controller;

Controller* Controller_getInstance(void);
Controller* Controller_construct(void);

#endif /* CONTROLLER_H_ */
