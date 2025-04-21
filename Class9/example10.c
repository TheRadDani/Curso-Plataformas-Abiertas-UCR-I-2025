/*******************************************************************
* University of Costa Rica - Electrical Engineering
* Lecturer: Daniel Ferreto
* Course: Programming over open platforms
* Simulating Hardware Register Access
* Description: Use pointers to read/write memory-mapped registers.
* EE Application: Embedded programming for microcontrollers.
*******************************************************************/
#include <stdio.h>
#include <stdint.h>

// Simulate a hardware register at address 0x40000000
//#define STATUS_REGISTER (*(volatile uint32_t*)0x40000000)
volatile uint32_t STATUS_REGISTER = 0; 

int main() {
    // Read status register (e.g., check sensor flag)
    uint32_t status = STATUS_REGISTER;

    // Write to register (e.g., enable a peripheral)
    STATUS_REGISTER = 0x1;

    printf("Register value: %x\n", STATUS_REGISTER);

    return 0;
}