.section .text
.globl _start

_start:
    li a0, 42        # Load immediate value 42 into register a0
    li a7, 93        # Exit syscall number
    ecall            # Invoke syscall