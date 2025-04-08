.global _start

.section .data
value1: .word 5
value2: .word 10

.section .text
_start:
    ldr r0, =value1    // Load address of value1 into r0
    ldr r1, [r0]       // Load value1 from memory into r1
    ldr r0, =value2    // Load address of value2 into r0
    ldr r2, [r0]       // Load value2 from memory into r2

    add r3, r1, r2     // Perform addition: r3 = r1 + r2

    // Exit program (Linux syscall)
    mov r7, #1         // Syscall for exit
    swi 0