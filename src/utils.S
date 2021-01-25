// Busy wait
.globl delay
delay:
    subs x0, x0, #1
    bne delay
    ret

// Store value into register
.globl put32
put32:
    str w1, [x0]
    ret

// Load value from register
.globl get32
get32:
    ldr w0, [x0]
    ret

// Return the ARM exception level
.globl get_el
get_el:
    mrs x0, CurrentEL               // Load information from CurrentEL register
    lsr x0, x0, #2                  // Current exception level are in bits [3:2], so we shift shift 2 bits right.
    ret