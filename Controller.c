/*
 * Controller.c
 *
 *  Created on: Jul 29, 2019
 *      Author: Matthew Zhong
 */

#include <Controller.h>
#include <stdlib.h>

Controller* Controller_getInstance()
{
    static Controller* controller = NULL;
    if (controller == NULL) {
        controller = Controller_construct();
    }
    return controller;
}

Controller* Controller_construct()
{
    Controller* controller = malloc(sizeof(Controller));

    controller->leds    = LEDs_construct();
    controller->buttons = Buttons_construct();

    return controller;
}

