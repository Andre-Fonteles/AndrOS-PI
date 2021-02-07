#ifndef	_MINI_UART_H
#define	_MINI_UART_H

#include "common.h"

void uart_init(void);
char uart_recv(void);
void uart_send(char c);
void uart_send_string(char *str);
void uart_print_u64(u64 value, int base);

#endif  /*_MINI_UART_H */