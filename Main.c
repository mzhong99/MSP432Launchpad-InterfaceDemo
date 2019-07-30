/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/* Module Includes */
#include <Demo.h>

void Initialize(void)
{
    // Stop the Watchdog Timer
    WDT_A_holdTimer();

    // Need to invoke this one time to call all control constructors
    Controller_getInstance();
}

void SuperLoop(void)
{
    for (;;) {
        Demo_showLEDs();
    }
}

void main(void)
{
    Initialize();
    SuperLoop();
}
