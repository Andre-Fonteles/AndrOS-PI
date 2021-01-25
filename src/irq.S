.globl irq_init_vector
irq_init_vector:
	adr	x0, vectors		// Load the address of the vector table
	msr	vbar_el1, x0    // Store the vector table address
	ret

.globl enable_irq
enable_irq:
	msr daifclr, #2 
	ret

.globl disable_irq
disable_irq:
	msr	daifset, #2
	ret