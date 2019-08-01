/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/* Module Includes */
#include <Demo.h>
#include <Timer.h>
#include <Controller.h>

void Initialize(void)
{
    // Stop the Watchdog Timer
    WDT_A_holdTimer();

    // Initialize global timers
    HWTimers_init();

    // Need to invoke this one time to call all control constructors
    Controller_getInstance();
}

void SuperLoop(void)
{
    for (;;) {
        Demo_showTimerLEDs();
    }
}

int main(void)
{
    Initialize();
    SuperLoop();
}
