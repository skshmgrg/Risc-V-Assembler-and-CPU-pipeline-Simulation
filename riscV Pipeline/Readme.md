# RISC-V Pipelined Processor Simulator (C++)

This project implements a cycle-accurate 5-stage pipelined RISC-V processor simulator in C++, including **data forwarding**, **hazard detection**, **stalls**, and **pipeline control logic**.  
The design follows a modular, hardware-inspired structure, closely resembling how real processors are built and simulated.

---------------------------------------------------------

## Project Structure
PIPELINE_REFINED_FINAL/
│
├── include/
│ ├── assets.h             # Common utilities, MUXes, constants
│ ├── forwarding_unit.h    # Data forwarding logic
│ ├── hazard_unit.h        # Hazard detection and stall logic
│ ├── pipeline_control.h   # Control signal generation
│ ├── pipeline_datapath.h  # Pipeline stage functions (IF, ID, EX, MEM, WB)
│ ├── pipeline_registers.h # Definitions of pipeline registers
│ └── utility.h            # Helper functions
│
├── src/
│ ├── assets.cpp
│ ├── forwarding_unit.cpp
│ ├── hazard_unit.cpp
│ ├── pipeline_control.cpp
│ ├── pipeline_datapath.cpp
│ ├── pipeline_registers.cpp
│ ├── utility.cpp
│ └── main.cpp             # Simulator entry point
│
├── input.txt              # Input RISC-V instructions
├── pipeline.exe           # Compiled executable
└── README.md

----------------------------------------------------------

## Features

- 5-stage pipeline:
  - IF – Instruction Fetch  
  - ID – Instruction Decode  
  - EX – Execute  
  - MO – Memory Operation
  - WB – Write Back
- Pipeline registers between each stage
- Data hazard detection
- Forwarding unit for RAW hazards
- Pipeline stalling and flushing
- Modular separation of:
  - Datapath
  - Control logic
  - Hazard unit
  - Forwarding unit
- Input program loaded from a text file
- Cycle-by-cycle simulation

-----------------------------------------------------------

## Build Instructions
Make sure you are in the project root directory.

### Compile (Linux / Windows – g++)

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o pipeline

### Run
./pipeline

-------------------------------------------------------------

##Future Improvements
-Branch prediction
-Exception handling
-Support for more RISC-V instructions

-------------------------------------------------------------