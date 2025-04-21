/*******************************************************************
* University of Costa Rica - Electrical Engineering
* Lecturer: Daniel Ferreto
* Course: Programming over open platforms
* Simulating Hardware Register Access
* Description: Demonstrates register access using MMIO.
* EE Application: Direct communication with FPGA peripherals.
*******************************************************************/

#include <stdio.h>
#include <stdint.h>

// Base address for hardware registers (example for FPGA AXI)
#define FPGA_BASE_ADDRESS  0x40000000

// Register Offsets (assuming 32-bit registers)
#define CONTROL_REG   (*(volatile uint32_t*)(FPGA_BASE_ADDRESS + 0x00)) // Control settings
#define STATUS_REG    (*(volatile uint32_t*)(FPGA_BASE_ADDRESS + 0x04)) // Status flags
#define DATA_REG      (*(volatile uint32_t*)(FPGA_BASE_ADDRESS + 0x08)) // Data exchange

int main() {
    /* *** Initialize hardware via control register *** */
    CONTROL_REG = 0x1; // Enable a peripheral

    /* *** Read status register to check device state *** */
    uint32_t status = STATUS_REG;
    if (status & 0x1) {
        printf("Device is ready.\n");
    } else {
        printf("Device is not ready.\n");
    }

    /* *** Read data from FPGA register *** */
    uint32_t sensor_value = DATA_REG;
    printf("Sensor reading: %u\n", sensor_value);

    return 0;
}