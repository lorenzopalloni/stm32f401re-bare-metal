#ifndef CORE_SYSTEM_H
#define CORE_SYSTEM_H

#include "stdint.h"

#define CPU_FREQ 84000000
#define SYSTICK_FREQ 1000

void system_setup(void);
uint64_t system_get_ticks(void);

#endif  // CORE_SYSTEM_H