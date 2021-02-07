#include "mini_uart.h"
#include "irq.h"
#include "utils.h"
#include "timer.h"
#include "fork.h"
#include "scheduler.h"
#include "string_utils.h"
#include "common.h"

void process(char *array)
{
	while (1){
		for (int i = 0; i < 5; i++){
			uart_send(array[i]);
			delay(100000);
		}
	}
}

void kernel_main(void)
{
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

	int res = copy_process((unsigned long)&process, (unsigned long)"12345");
	if (res != 0) {
		uart_send_string("error while starting process 1\n");
		return;
	}
	res = copy_process((unsigned long)&process, (unsigned long)"abcde");
	if (res != 0) {
		uart_send_string("error while starting process 2");
		return;
	}

	while (1){
		schedule();
	}	
}