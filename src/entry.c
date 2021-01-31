#include "entry.h"
#include "scheduler.h"
#include "mini_uart.h"

void channel() {
    // while(1) 
	//     uart_send_string("\n\nCalling ret_from_fork...\n");
    ret_from_fork();
}

unsigned long get_fun() {
    return (unsigned long) channel;
}