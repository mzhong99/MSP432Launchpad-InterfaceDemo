/*
 * Timer.c
 *
 *  Created on: Jul 30, 2019
 *      Author: Matthew Zhong
 */

#include <Timer.h>
#include <malloc.h>

// Global Timer32 instance. Used for timing all software timers.
// Do not change the settings unless you know what you're doing.
// This timer is currently configured to maximize the time between rollovers
static HWTimer Timer32_0;

void Timer32_0_InterruptHandler()
{
    Timer32_0.rollovers++;
    Timer32_clearInterruptFlag(Timer32_0.timerID);
}

void HWTimers_init()
{
    Timer32_0.timerID    = TIMER32_0_BASE;
    Timer32_0.prescaler  = TIMER32_PRESCALER_256;
    Timer32_0.resolution = TIMER32_32BIT;
    Timer32_0.resetMode  = TIMER32_PERIODIC_MODE;
    Timer32_0.loadValue  = 0xFFFFFFFF;
    Timer32_0.rollovers  = 0;

    Timer32_initModule(Timer32_0.timerID,
                       Timer32_0.prescaler,
                       Timer32_0.resolution,
                       Timer32_0.resetMode);
    Timer32_enableInterrupt(Timer32_0.timerID);
    Timer32_registerInterrupt(TIMER32_0_INTERRUPT, Timer32_0_InterruptHandler);
    Timer32_setCount(Timer32_0.timerID, Timer32_0.loadValue);
    Timer32_startTimer(Timer32_0.timerID, Timer32_0.resetMode);
}

SWTimer* SWTimer_construct(uint32_t time_ms)
{
    SWTimer* timer = malloc(sizeof(SWTimer));

    timer->duration_ms = time_ms;
    SWTimer_start(timer);

    return timer;
}

void SWTimer_start(SWTimer* timer)
{
    uint64_t startHWTicks
        = (uint64_t) Timer32_0.loadValue
        - (uint64_t) Timer32_getValue(Timer32_0.timerID);
    uint64_t ticksInDuration
        = ((uint64_t) timer->duration_ms * (uint64_t) SYSTEM_CLOCK)
        / ((uint64_t) PRESCALER * (uint64_t) UNIT_SCALE_FACTOR);

    uint64_t ticksPerRollover = (uint64_t) Timer32_0.loadValue;

    uint64_t runoffTicks = ticksInDuration % ticksPerRollover;

    uint64_t baseRollovers = ticksInDuration / ticksPerRollover;
    uint64_t extraRollover = (runoffTicks + startHWTicks) / ticksPerRollover;
    uint64_t endHWTicks = (startHWTicks + runoffTicks) % ticksPerRollover;

    timer->endHWRollovers = Timer32_0.rollovers + baseRollovers + extraRollover;
    timer->endHWTicks = endHWTicks;
}

bool SWTimer_expired(SWTimer* timer)
{
    uint64_t currentHWTicks
        = (uint64_t) Timer32_0.loadValue
        - (uint64_t) Timer32_getValue(Timer32_0.timerID);

    return currentHWTicks >= timer->endHWTicks
        && Timer32_0.rollovers >= timer->endHWRollovers;
}
