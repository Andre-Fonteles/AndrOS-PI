#ifndef _TIMER_H
#define _TIMER_H

#include "common.h"

void init_timer(void);
void handle_timer_1(void);
void handle_timer_3(void);
void timer_sleep(u32 ms);
u64 timer_get_ticks(void);

#endif /*_TIMER_H */