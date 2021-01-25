#ifndef	_GPIO_H
#define	_GPIO_H

#include "peripherals/gpio.h"
#include "common.h"

typedef enum _gpio_func {
    GFInput = 0b000,
    GFOutput = 0b001,
    GFAlt0 = 0b100,
    GFAlt1 = 0b101,
    GFAlt2 = 0b110,
    GFAlt3 = 0b111,
    GFAlt4 = 0b011,
    GFAlt5 = 0b010
} gpio_func;

typedef enum _gpio_pud {
    PUDOff = 0b00,
    PUDEnablePD = 0b01,
    PUDEnablePU = 0b10
} gpio_pud;

void gpio_pin_set_func(u8 pinNumber, gpio_func func);

void gpio_pin_pull_enable(u8 pinNumber, gpio_pud pUpDown);

#endif  /*_GPIO_H */