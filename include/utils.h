#ifndef	_BOOT_H
#define	_BOOT_H

#include "common.h"

void delay(u64 ticks);
void put32(u64 address, u32 value);
u32 get32(u64 address);
u64 get_el(void);

#endif  /*_BOOT_H */