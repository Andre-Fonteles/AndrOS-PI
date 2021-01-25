#ifndef	_GPIO_H
#define	_GPIO_H

void irq_init_vector (void);
void enable_irq (void);
void disable_irq (void);
void enable_interrupt_controller(void);

#endif /* _GPIO_H */