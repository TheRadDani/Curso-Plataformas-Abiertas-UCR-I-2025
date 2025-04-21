/*******************************************************************
* University of Costa Rica - Electrical Engineering
* Lecturer: Daniel Ferreto
* Course: Programming over open platforms
* Pointers
* Description: Use pointers to swap values (common in register manipulation).
* EE Application: Memory-mapped I/O in microcontrollers.
*******************************************************************/
#include <stdio.h>

// Swap using pointers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 5, y = 10;
    printf("Before swap: x = %d, y = %d\n", x, y);
    swap(&x, &y); // Pass addresses
    printf("After swap: x = %d, y = %d\n", x, y);
    return 0;
}