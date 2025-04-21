/*******************************************************************
 * University of Costa Rica - Electrical Engineering
 * Lecturer: Daniel Ferreto
 * Course: Programming over open platforms
 * Example: Communication with GPIO Peripheral via Memory-Mapped I/O
 * EE Application: Controlling hardware peripherals in FPGA/microcontrollers.
 *******************************************************************/

 #include <stdio.h>
 #include <stdint.h>
 
 // Define base address for GPIO peripheral (Example: FPGA or microcontroller)
 #define GPIO_BASE_ADDRESS  0x40020000  // Hypothetical memory-mapped address
 #define GPIO_INPUT_REG  (*(volatile uint32_t*)(GPIO_BASE_ADDRESS + 0x00))  // Input register
 #define GPIO_OUTPUT_REG (*(volatile uint32_t*)(GPIO_BASE_ADDRESS + 0x04))  // Output register
 #define GPIO_CONFIG_REG (*(volatile uint32_t*)(GPIO_BASE_ADDRESS + 0x08))  // Configuration register
 
 int main() {
     /* *** Configure GPIO as Output *** */
     GPIO_CONFIG_REG = 0x1;  // Assuming 0x1 means setting pin as output
 
     /* *** Write a value to GPIO Output *** */
     GPIO_OUTPUT_REG = 0xFF;  // Example: Set all output pins high
 
     /* *** Read GPIO Input Status *** */
     uint32_t input_status = GPIO_INPUT_REG;  // Read input register
     printf("GPIO Input Status: 0x%08X\n", input_status);  // Display read value
 
     return 0;
 }
 