#include "utils.h"
#include "entry.h"
#include "peripherals/irq.h"
#include "peripherals/aux.h"
#include "mini_uart.h"
#include "string_utils.h"
#include "timer.h"

const char *entry_error_messages[] = {
	"SYNC_INVALID_EL1t",
	"IRQ_INVALID_EL1t",		
	"FIQ_INVALID_EL1t",		
	"ERROR_INVALID_EL1T",		

	"SYNC_INVALID_EL1h",		
	"IRQ_INVALID_EL1h",		
	"FIQ_INVALID_EL1h",		
	"ERROR_INVALID_EL1h",		

	"SYNC_INVALID_EL0_64",		
	"IRQ_INVALID_EL0_64",		
	"FIQ_INVALID_EL0_64",		
	"ERROR_INVALID_EL0_64",	

	"SYNC_INVALID_EL0_32",		
	"IRQ_INVALID_EL0_32",		
	"FIQ_INVALID_EL0_32",		
	"ERROR_INVALID_EL0_32"	
};

void handle_invalid_entry_message(u32 type, u64 esr, u64 address) {

    uart_send_string("ERROR CAUGHT: ");

    // uart_send_string("ERROR CAUGHT: ");
    // uart_send_string((char*) entry_error_messages[type]);
    // uart_send_string(" - ");

    char buffType[] = "00";
    parse_int(type, buffType, 10);
    uart_send_string(buffType);

    uart_send_string(", ESR: ");
    char buffEsr[] = "0000000000000000";
    parse_int(esr, buffEsr, 16);
    uart_send_string(buffEsr);

    uart_send_string(", Address: ");
    char buffAddress[] = "0000000000000000";
    parse_int(address, buffAddress, 16);
    uart_send_string(buffAddress);

    uart_send_string("\n");
}

void enable_interrupt_controller(void) {
#if RPI_VERSION == 4
    REGS_IRQ->irq0_enable_0 = SYS_TIMER_IRQ_1;
#elif RPI_VERSION == 3
    REGS_IRQ->irq0_enable_1 = SYS_TIMER_IRQ_1;
#endif
}

void handle_irq(void) {
    u32 irq;

#if RPI_VERSION == 4
    irq = REGS_IRQ->irq0_pending_0;
#elif RPI_VERSION == 3
    irq = REGS_IRQ->irq0_pending_1;
#endif

    while(irq) {
        if(irq & AUX_IRQ) {
            irq &= ~AUX_IRQ;

            while((REGS_AUX->mu_iir & 4) == 4) {
                uart_send_string("UART Received: ");
                uart_send(uart_recv());
                uart_send_string("\n");
            }
        } else if(irq & SYS_TIMER_IRQ_1) {
            irq &= ~SYS_TIMER_IRQ_1;
            handle_timer_1();
        } else if(irq & SYS_TIMER_IRQ_3) {
            irq &= ~SYS_TIMER_IRQ_3;
            handle_timer_3();
        }
    }

}