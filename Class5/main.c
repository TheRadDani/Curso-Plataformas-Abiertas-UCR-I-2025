#include <stdio.h>

// Emulated FPGA function (AND gate)
unsigned char emulated_fpga(unsigned char a, unsigned char b) {
    return a & b;
}

int main() {
    unsigned char a = 1, b = 1; // Test inputs
    unsigned char y = emulated_fpga(a, b);
    printf("Result: %d\n", y);
    return 0;
}
