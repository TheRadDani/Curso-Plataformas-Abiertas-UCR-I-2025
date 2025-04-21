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

// Define memory-mapped addresses (assuming they exist)
#define GPIO_INPUT_REGISTER (*(volatile uint32_t*)0x40001000)
#define GPIO_OUTPUT_REGISTER (*(volatile uint32_t*)0x40001004)

int main() {
    // Simulating peripheral input
    uint32_t gpio_state = GPIO_INPUT_REGISTER;  // Read GPIO status

    // If button pressed (assuming bit 0 represents a button flag)
    if (gpio_state & 0x1) {
        GPIO_OUTPUT_REGISTER = 0x1; // Set output (e.g., turn on LED)
    }

    // Debug output
    printf("GPIO Status: %u\n", gpio_state);
    printf("GPIO Output: %u\n", GPIO_OUTPUT_REGISTER);

    return 0;
}
