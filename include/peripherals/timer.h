#ifndef	_P_TIMER_H
#define	_P_TIMER_H

#include "common.h"
#include "peripherals/base.h"

#define CLOCKHZ 1000000

// Section 10.2 BCM2711 ARM Peripherals
struct timer_regs {
    reg32 control_status;
    reg32 counter_low;
    reg32 counter_high;
    reg32 compare[4];
};

#define REGS_TIMER ((struct timer_regs *)(PBASE + 0x00003000))

#endif  /*_P_TIMER_H */