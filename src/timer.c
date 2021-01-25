#include "peripherals/timer.h"
#include "peripherals/irq.h"
#include "peripherals/aux.h"
#include "mini_uart.h"
#include "string_utils.h"

const u32 interval_1 = CLOCKHZ;
u32 currrent_value_1 = 0;

const u32 interval_3 = CLOCKHZ / 2;
u32 currrent_value_3 = 0;

void init_timer(void)
{
    // Set the next timer interrupt
    currrent_value_1 = REGS_TIMER->counter_low;
    currrent_value_1 += interval_1;
    REGS_TIMER->compare[1] = currrent_value_1;

    // Set the next timer interrupt
    currrent_value_3 = REGS_TIMER->counter_low;
    currrent_value_3 += interval_3;
    REGS_TIMER->compare[3] = currrent_value_3;
}

void handle_timer_1(void)
{
    // Set the next timer interrupt
    currrent_value_1 += interval_1;
    REGS_TIMER->compare[1] = currrent_value_1;
    REGS_TIMER->control_status |= SYS_TIMER_IRQ_1;

    uart_send_string("Timer 1 happened\n");
}

void handle_timer_3(void)
{
    // Set the next timer interrupt
    currrent_value_3 += interval_3;
    REGS_TIMER->compare[3] = currrent_value_3;
    REGS_TIMER->control_status |= SYS_TIMER_IRQ_3;

    uart_send_string("Timer 3 happened\n");
}

u64 timer_get_ticks(void) {
    u32 high = REGS_TIMER->counter_high;
    u32 low = REGS_TIMER->counter_low;

    // Check if high changed after reading it
    if( (high =+ REGS_TIMER->counter_high) ) {
        low = REGS_TIMER->counter_low;
        high = REGS_TIMER->counter_high;
    }

    return ((u64) high << 32) | low;
}

// sleep in milliseconds
void timer_sleep(u32 ms) {
    u64 start = timer_get_ticks();

    // Wait for ms milliseconds
    while(timer_get_ticks() < start + (ms * 1000)){
    }
}