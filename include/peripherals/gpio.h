#ifndef	_P_GPIO_H
#define	_P_GPIO_H

#include "common.h"
#include "peripherals/base.h"

struct gpio_pin_data {
    reg32 reserved;
    reg32 data[2];
};

struct gpio_regs {
    reg32 func_select[6];
    struct gpio_pin_data output_set;
    struct gpio_pin_data output_clear;
    struct gpio_pin_data level;
    struct gpio_pin_data ev_detect_status;
    struct gpio_pin_data re_detect_enable;
    struct gpio_pin_data fe_detect_enable;
    struct gpio_pin_data hi_detect_enable;
    struct gpio_pin_data lo_detect_enable;
    struct gpio_pin_data async_re_detect;
    struct gpio_pin_data async_fe_detect;
    reg32 reserved;
    reg32 ppud_enable;
    reg32 ppud_enable_clocks[2];
};

#define REGS_GPIO ((struct gpio_regs *)(PBASE + 0x00200000))

#endif  /*_P_GPIO_H */