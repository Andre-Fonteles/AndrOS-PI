#include "gpio.h"
#include "utils.h"

void gpio_pin_set_func(u8 pinNumber, GpioFunc func) {
    u8 reg = pinNumber / 10;
    u8 startBit = (pinNumber * 3) % 30;

    u32 selector = REGS_GPIO->func_select[reg];
    selector &= ~(7 << startBit);
    selector |= (func << startBit);

    REGS_GPIO->func_select[reg] = selector;
}

/* Refactor - this is hard coded to disable... */
void gpio_pin_pull_enable(u8 pinNumber, GpioPUpDown pUpDown) {
    REGS_GPIO->ppud_enable = pUpDown;
    delay(150);
    REGS_GPIO->ppud_enable_clocks[pinNumber / 32] = 1 << (pinNumber % 32);
    delay(150);
    REGS_GPIO->ppud_enable = 0;
    REGS_GPIO->ppud_enable_clocks[pinNumber / 32] = 0;
}
