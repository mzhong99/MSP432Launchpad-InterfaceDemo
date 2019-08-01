/*
 * Timer.h
 *
 *  Created on: Jul 30, 2019
 *      Author: Matthew Zhong
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define SYSTEM_CLOCK      48000000
#define PRESCALER         256
#define UNIT_SCALE_FACTOR 1000

struct _HWTimer
{
    uint32_t timerID;       // TIMER32_0_BASE or TIMER32_1_BASE

    uint32_t prescaler;     // TIMER32_PRESCALER_{1,16,256}

    uint32_t resolution;    // TIMER32_16BIT or TIMER32_13BIT

    uint32_t resetMode;     // TIMER32_FREE_RUN_MODE (One-Shot)
                            // TIMER32_PERIODIC_MODE (Resets itself)

    uint32_t loadValue;     // N, the load value (decrement 1 per sysclk cycle)

    uint64_t rollovers;     // The number of times since system start the timer
                            // has been reset
};
typedef struct _HWTimer HWTimer;

// In this API, all software timers are dependent on TIMER32_0_BASE
struct _SWTimer
{
    uint64_t endHWTicks;
    uint64_t endHWRollovers;
    uint64_t duration_ms;
};
typedef struct _SWTimer SWTimer;

void HWTimers_init();
SWTimer* SWTimer_construct();
void SWTimer_start(SWTimer* timer);
bool SWTimer_expired(SWTimer* timer);

#endif /* TIMER_H_ */
