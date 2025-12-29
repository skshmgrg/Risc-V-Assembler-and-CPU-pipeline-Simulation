# Assembler + 5-Stage Pipelined Processor Simulator

This repository contains a complete RISC-V toolchain implemented in C++, consisting of:
1) A RISC-V Assembler that converts assembly instructions into 32-bit binary machine code
2) A cycle-accurate 5-stage pipelined RISC-V processor simulator with hazard handling and forwarding

The project follows a modular, hardware-inspired design and is intended for academic and educational use.

------------------------------------------------------------

## PROJECT STRUCTURE

<pre>
Risc-V-Assembler-and-CPU-pipeline-Simulation/
│
├── assembler/
│   ├── include/
│   │   ├── isa_data.h
│   │   ├── isa_utils.h
│   │   └── isa_encode.h
│   │
│   ├── src/
│   │   ├── isa_data.cpp
│   │   ├── isa_utils.cpp
│   │   ├── isa_encode.cpp
│   │   └── assembler.cpp
│   │
│   ├── input.txt
│  
│
├── pipeline/
│   ├── include/
│   │   ├── assets.h
│   │   ├── forwarding_unit.h
│   │   ├── hazard_unit.h
│   │   ├── pipeline_control.h
│   │   ├── pipeline_datapath.h
│   │   ├── pipeline_registers.h
│   │   └── utility.h
│   │
│   ├── src/
│   │   ├── assets.cpp
│   │   ├── forwarding_unit.cpp
│   │   ├── hazard_unit.cpp
│   │   ├── pipeline_control.cpp
│   │   ├── pipeline_datapath.cpp
│   │   ├── pipeline_registers.cpp
│   │   ├── utility.cpp
│   │   └── main.cpp
│   │
│   ├── input.txt
│   
│
└── README.md
</pre>

------------------------------------------------------------

## RISC-V ASSEMBLER (C++)

### OVERVIEW
A modular assembler that translates RISC-V assembly instructions into 32-bit binary machine code.

### FEATURES
- Supports instruction formats:
  - R-type
  - I-type
  - S-type
  - B-type
  - U-type
- Supports pseudo-instructions:
  - li
  - mv
  - nop
- Clean separation of:
  - Instruction metadata
  - Utility helpers
  - Encoding logic
  - Driver program
- Easily extensible with new instructions

### INPUT / OUTPUT
- input.txt contains RISC-V assembly code
- output.txt contains generated 32-bit machine code

------------------------------------------------------------

## RISC-V PIPELINED PROCESSOR SIMULATOR (C++)

### OVERVIEW
A cycle-accurate simulation of a 5-stage pipelined RISC-V processor that closely models real hardware behavior.

### PIPELINE STAGES
- IF : Instruction Fetch
- ID : Instruction Decode
- EX : Execute
- MO : Memory Operation
- WB : Write Back

### FEATURES
- Pipeline registers between all stages
- Data hazard detection
- Forwarding unit for RAW hazards
- Pipeline stalls and flushing
- Modular separation of:
  - Datapath
  - Control logic
  - Hazard unit
  - Forwarding unit
- Input program loaded from a text file
- Cycle-by-cycle simulation

------------------------------------------------------------

## HOW THE TWO PROJECTS FIT TOGETHER

- The Assembler converts RISC-V assembly into machine code
- The Pipeline Simulator executes instructions using a realistic pipelined datapath
- Together, they form a mini RISC-V execution toolchain

------------------------------------------------------------

## COMPILE
### PIPELINE
-Go to the riscV Pipeline directory and run 
```bash
g++ -Iinclude src/*.cpp -o pipeline
```
### ASSEMBLER
-Go to the riscV assembler directory and run 
```bash
g++ -Iinclude src/*.cpp -o assembler
```
------------------------------------------------------------

## FUTURE IMPROVEMENTS

### ASSEMBLER
- Full RISC-V ISA support
- Label handling and symbol table
- Improved error diagnostics
- Hexadecimal output format

### PIPELINE SIMULATOR
- Branch prediction
- Exception and interrupt handling
- Cache simulation
- Support for additional RISC-V instructions

------------------------------------------------------------
