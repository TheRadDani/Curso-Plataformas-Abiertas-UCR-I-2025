# Class5: Introduction to Computer Architecture
## Author: Daniel Ferreto


### What is Computer Architecture?
Computer architecture refers to the design of computer systems, including:
- Instruction Set Architecture (ISA)
- Microarchitecture (physical implementation)
- System design (memory, I/O, interconnects)

Key concepts:
- **ISA**: Interface between hardware and software (e.g., x86, ARM, RISC-V)
- **CISC** vs **RISC**: Complex vs Reduced Instruction Set Computing
- **Endianness**: Byte ordering in memory (Little-endian/Big-endian)

## Common Architectures in Ubuntu
### 1. x86/x86-64
- Dominant in desktop/laptop computers
- CISC architecture (complex instructions)
- 32-bit (x86) and 64-bit (x86-64) variants

### 2. ARM
- RISC architecture
- Dominates mobile/embedded systems
- Growing presence in servers (AWS Graviton)

### 3. RISC-V
- Open-source RISC architecture
- Modular design with base ISA + extensions
- Growing adoption in academia and industry

### Key Components:
- **CPU**: Executes instructions (ALU, Control Unit, Registers)
- **Memory**: Stores data/instructions (RAM, ROM)
- **I/O Devices**: Communication interface
- **Bus System**: Data/address/control buses

### Architecture Types:
- **Von Neumann**: Single bus for data/instructions
- **Harvard**: Separate data/instruction buses

---

## Von Neumann Architecture
![alt text](../images/image-7.png)


## Working with Architectures in Ubuntu
### Checking System Architecture
```bash
# Show CPU architecture
lscpu | grep Architecture
```

# Detailed CPU information
```bash
lscpu
```

# Kernel architecture
```bash
uname -m
```

# Multi-arch Support
Ubuntu supports multiple architectures simultaneously:
```bash
# Add RISC-V architecture support
sudo dpkg --add-architecture riscv64

# Update package lists
sudo apt update
```

## 2. Installing Software from Source (Generic Guide)
### Steps:
1. **Download Source Code**:
```bash
   wget https://example.com/software.tar.gz
   tar -xzvf software.tar.gz
   cd software/
```

```bash
./configure --prefix=/usr/local
```

## Compile
```bash
make
```

## install
```bash
sudo make install
```

## Common Issues:
Missing dependencies: Install using sudo apt install build-essential libtool autoconf

##  FPGA Fundamentals
What is an FPGA?
Field-Programmable Gate Array: Reconfigurable hardware.

## Key Components:
Configurable Logic Blocks (CLBs): Basic logic units.

Interconnects: Reconfigurable wiring.

I/O Blocks: Interface with external devices.

Memory Blocks: Store data.

Yosys Toolchain:
Yosys: Open-source framework for Verilog RTL synthesis.

##  Cross-Compilation & QEMU Emulation
What is Cross-Compilation?
Compiling code for a different architecture (e.g., ARM on x86).

Setup Cross-Compiler (ARM Example):

```bash
sudo apt upgrade -y

sudo apt install gcc-arm-linux-gnueabi qemu-user-static -y
```
```bash
sudo apt install qemu-user -y
```

# RISC-V Development in Ubuntu
Installing RISC-V Tools

```bash
sudo apt install gcc-riscv64-linux-gnu qemu-user-static -y
```

```bash
git clone --recursive https://github.com/riscv-collab/riscv-gnu-toolchain
cd riscv-gnu-toolchain
```

Simple RISC-V Program
Create `hello.c:`
```c
#include <stdio.h>

int main() {
    printf("Hello RISC-V!\n");
    return 0;
}
```

## Compile for RISC-V:
```bash
riscv64-unknown-elf-gcc -march=rv64gc -mabi=lp64d -o hello hello.c
```


# Run using QEMU:
```bash
qemu-riscv64-static hello
Hello RISC-V!
```

# Architecture Comparison Table

| **Feature**      | **x86-64**      | **ARMv8**      | **RISC-V**      |
|-------------------|-----------------|----------------|-----------------|
| **License**       | Proprietary     | Proprietary    | Open-source     |
| **Instruction Set** | CISC           | RISC           | RISC            |
| **Endianness**    | Little          | Bi-endian      | Bi-endian       |
| **Extensions**    | SSE/AVX         | NEON           | Modular         |
| **Registers**     | 16 GP           | 31 GP          | 32 GP           |

## RISC-V Architecture
Key Features
Base integer ISA (RV32I/RV64I)

Standard extensions:

* M (Integer Multiplication/Division)

* A (Atomic Operations)

* F (Single-Precision Float)

* D (Double-Precision Float)

Custom extensions possible

Privilege levels: User, Supervisor, Machine

RISC-V Assembly Example
Create `example.s:`
```asm
.section .text
.globl _start

_start:
    li a0, 42        # Load immediate value 42 into register a0
    li a7, 93        # Exit syscall number
    ecall            # Invoke syscall
```

Assemble and run:
```bash
riscv64-unknown-elf-as -o example.o example.s
riscv64-unknown-elf-ld -o example example.o
qemu-riscv64-static example
echo $?  # Should show 42
```

## Kernel and Hardware Interaction
Hardware Information

```bash
# List all hardware
sudo lshw

# Show PCI devices
lspci

# Show kernel modules
lsmod
```

## System Monitoring
```bash
# CPU usage
top

# Memory usage
free -h

# Hardware events
dmesg | less
```

# Cross-compilation
```bash
# Install cross-compiler
sudo apt install g++-riscv64-linux-gnu

# Cross-compile C++ program
riscv64-linux-gnu-g++ -o cross_app main.cpp
```

# FPGA Development
# Verilog Synthesis with Yosys

# Dependencies
```bash
sudo apt install build-essential clang bison flex \
  libreadline-dev gawk tcl-dev libffi-dev git -y
```

# install from source
```bash
git clone --recurse-submodules https://github.com/YosysHQ/yosys.git
cd yosys
git submodule init
git submodule update
make -j$(nproc)
sudo make install
```


```bash
# Update and upgrade your system
sudo apt update && sudo apt upgrade -y
# Install basic FPGA toolchain
sudo apt install yosys nextpnr-ice40 iverilog qemu-system -y
```

```bash
# Synthesize Verilog for RISC-V
yosys -p "synth_ice40 -top example -json example.json" example.v
```

```bash
nextpnr-ice40 --hx8k --package tq144 --json example.json --asc example.asc
```

```bash
sudo apt install iverilog -y
iverilog -o simulation example.v
vvp simulation
```

```bash
sudo apt install gcc-riscv64-linux-gnu -y
sudo apt install libc6-riscv64-cross -y
sudo apt install gcc-riscv64-unknown-elf -y
riscv64-linux-gnu-gcc -o main.elf main.c
qemu-riscv64 ./main.elf
```

```bash
qemu-system-riscv64 -nographic -machine virt -kernel main.elf
```

# Further Resources

## Books:
- *"Computer Organization and Design RISC-V Edition"* by Patterson & Hennessy
- *"The RISC-V Reader"* by Waterman & Asanović

## Online Courses:
- **edX**: *"RISC-V Architecture and Programming"*
- **Coursera**: *"Computer Architecture"*

## Communities:
- **RISC-V International**: [riscv.org](https://riscv.org)
- **Ubuntu RISC-V Port**: [wiki.ubuntu.com/risc-v](https://wiki.ubuntu.com/risc-v)
