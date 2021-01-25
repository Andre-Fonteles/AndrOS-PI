#include "common.h"
#include "mini_uart.h"
#include "irq.h"
#include "string_utils.h"
#include "utils.h"
#include "timer.h"

void kernel_main() {
    uart_init();
    uart_send_string("\n\nRaspberry PI Bare Metal OS Initializing...\n");

    irq_init_vector();
    enable_interrupt_controller();
    enable_irq();
    init_timer();

#if RPI_VERSION == 3
    uart_send_string("\tBoard: Raspberry PI 3\n");
#endif

#if RPI_VERSION == 4
    uart_send_string("\tBoard: Raspberry PI 4\n");
#endif

	int exceptionLevel = get_el();
    char elStr[] = "00";
    parse_int(exceptionLevel, elStr, 10);
    uart_send_string("Exception level: ");
    uart_send_string(elStr);
    uart_send_string("\n");

    uart_send_string("Sleeping for 200 ms...\n");
    timer_sleep(200);
    uart_send_string("Sleeping for 200 ms...\n");
    timer_sleep(200);
    uart_send_string("Sleeping for 200 ms...\n");
    timer_sleep(200);
    uart_send_string("Sleeping for 2000 ms...\n");
    timer_sleep(2000);
    uart_send_string("Sleeping for 5000 ms...\n");
    timer_sleep(5000);
    uart_send_string("Done!\n");

    while(1) {
        // uart_send(uart_recv());
    }
}