/*
* In Xilinx FPGAs, register access is often done via AXI interfaces using functions provided by the Xilinx SDK (e.g., Xilinx Vivado/SDK).
* Getting Base Address
* FPGA peripherals (e.g., GPIO, UART, DMA) have mapped base addresses assigned in hardware (address mapped by Vivado's block design).
* These addresses are found in Xilinx Vivado hardware design after synthesis.
* Usually stored in xparameters.h in SDK, defining register base addresses.
*/


#include "xparameters.h"  // Contains base addresses of AXI devices
#include "xil_io.h"       // Xilinx I/O library for register access

#define LED_CONTROL_REG XPAR_MY_DEVICE_BASEADDR + 0x04  // Base + offset

int main() {
    /* *** Write to the FPGA hardware register *** */
    Xil_Out32(LED_CONTROL_REG, 0x1); // Turn LED ON

    /* *** Read register value *** */
    uint32_t reg_value = Xil_In32(LED_CONTROL_REG);
    printf("Register Value: %u\n", reg_value);

    return 0;
}
