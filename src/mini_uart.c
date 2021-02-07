#include "gpio.h"
#include "utils.h"
#include "peripherals/aux.h"
#include "mini_uart.h"
#include "string_utils.h"

#define TXD 14
#define RXD 15

static char* u64_str_buff = "0000000000000000";

void uart_init(void)
{
    gpio_pin_set_func(TXD, GFAlt5);
    gpio_pin_set_func(RXD, GFAlt5);

    gpio_pin_pull_enable(TXD, PUDOff);
    gpio_pin_pull_enable(RXD, PUDOff);

    REGS_AUX->enables = 1;
    REGS_AUX->mu_control = 0;
    REGS_AUX->mu_ier = 0b1101; // Enable UART receive interrupt
    REGS_AUX->mu_lcr = 3;
    REGS_AUX->mu_mcr = 0;

#if RPI_VERSION == 3
    REGS_AUX->mu_baud_rate = 270; // = 115200 @ 250 Mhz
#endif

#if RPI_VERSION == 4
    REGS_AUX->mu_baud_rate = 541; // = 115200 @ 500 Mhz
#endif

    REGS_AUX->mu_control = 3;
}

void uart_send(char c)
{
    // Loop (pool) until the device is ready to send the data.
    while (!(REGS_AUX->mu_lsr & 0x20))
        ; // Bit 5 tells if the transmiter is empty (the UART is ready write)

    REGS_AUX->mu_io = c;
}

char uart_recv(void)
{
    // Loop (pool) until the device is ready to receive the data.
    while (!(REGS_AUX->mu_lsr & 1))
        ; // Bit 1 tells if that data is ready to be read

    return REGS_AUX->mu_io & 0xFF; // Data is in the 8 LSB (8 bit mode)
}

void uart_send_string(char *str)
{
    while (*str)
    {
        if (*str == '\n')
        {
            uart_send('\r');
        }

        uart_send(*str);
        str++;
    }
}

void uart_print_u64(u64 value, int base) {
    parse_int(value, u64_str_buff, base);
    uart_send_string(u64_str_buff);
    uart_send_string("\n");
}