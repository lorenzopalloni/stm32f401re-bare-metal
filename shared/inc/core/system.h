#ifndef CORE_SYSTEM_H
#define CORE_SYSTEM_H

#include "stdint.h"

#define CPU_FREQ 84000000
#define SYSTICK_FREQ 1000

void sys_tick_handler(void);
void system_setup(void);
uint64_t system_get_ticks(void);
void system_delay(uint64_t milliseconds);

#endif  // CORE_SYSTEM_H