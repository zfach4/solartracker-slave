#ifndef POWERSLEEP
#define POWERSLEEP

#include <avr/sleep.h>

void sleepMode()
{
    sleep_enable();
    set_sleep_mode(SLEEP_MODE_STANDBY);
    sleep_cpu();
}

#endif