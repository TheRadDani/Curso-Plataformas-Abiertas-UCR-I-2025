## Memory-Mapped I/O (MMIO)

Memory-Mapped I/O is a technique where hardware registers or peripherals are mapped into the system’s memory address space, allowing them to be accessed as if they were normal memory locations.

Key Concepts:
1. Memory Addressing

* Registers are assigned fixed memory addresses.

* The processor accesses these registers through standard memory operations (read/write).

2.  Keyword

* Prevents compiler optimizations that could interfere with register access.

* Ensures every read/write operation interacts with the actual hardware.

3. Different Types of Mappings

* Control Registers: Configure hardware components (e.g., enabling/disabling peripherals).

* Status Registers: Indicate operational states (e.g., flags for interrupt requests).

* Data Registers: Store data exchanged between CPU and hardware (e.g., ADC values).