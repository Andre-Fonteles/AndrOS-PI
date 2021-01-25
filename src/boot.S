#include "mm.h"
#include "arm/sysreg.h"

.section ".text.boot"

.globl _start
_start:
    mrs x0, mpidr_el1   // Get info about the CPU from reg mpidr_el1
    and x0, x0, #0xFF   // Extract the ID of the CPU
    cmp x0, #0          // Comopare the id of the CPU core with 0
    beq master          // If the core's id == 0, branch to mater
    b proc_hang         // If the core' id != 0, branch to hang


master:
    // Disable the MMU
    ldr    x0, =SCTLR_VALUE_MMU_DISABLED
    msr    sctlr_el1, x0

    // EL1 will execute at Aarch64
    ldr    x0, =HCR_VALUE
    msr    hcr_el2, x0

    // EL1 will execute at Aarch64; and EL0 and 1 will be "non secure"
    ldr    x0, =SCR_VALUE
    msr    scr_el3, x0

    
    ldr    x0, =SPSR_VALUE
    msr    spsr_el3, x0

    // Configure EL1 to use its own stack and disable interrupts when EL1 
    adr    x0, el1_entry        
    msr    elr_el3, x0

    eret  

el1_entry:
    /* Clean memory from addresses bss_begin to bss_end */
    adr x0, bss_begin
    adr x1, bss_end
    sub x1, x1, x0
    bl memzero          // Call function to clean memory

    mov sp, #LOW_MEMORY // Initialize stack pointer
    bl kernel_main      // Transfer control to kernel_main function
    b proc_hang

proc_hang:
    b proc_hang