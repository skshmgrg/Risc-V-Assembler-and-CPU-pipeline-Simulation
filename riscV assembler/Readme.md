# RISC-V Assembler (C++)

A simple RISC-V assembler implemented in C++.  
This project translates RISC-V assembly instructions into their corresponding 32-bit binary machine code using a clean, modular design.

----------------------------------------------

## Project Structure

assembler/
│
├── include/
│ ├── isa_data.h     # Instruction metadata and initialization
│ ├── isa_utils.h    # Utility helper functions
│ └── isa_encode.h   # Instruction encoding interfaces
│
├── src/
│ ├── isa_data.cpp   # Instruction and register tables
│ ├── isa_utils.cpp  # Utility implementations
│ ├── isa_encode.cpp # Encoding logic
│ └── assembler.cpp  # Driver (main)
│
├── input.txt        # Input assembly file
├── output.txt       # Generated machine code
└── README.md

--------------------------------------------------

## Features

- Supports RISC-V instruction encoding
- Handles multiple instruction formats:
  - R-type
  - I-type
  - S-type
  - B-type
  - U-type
- Supports pseudo-instructions:
  - `li`
  - `mv`
  - `nop`
- Clean separation of data, utilities, encoding, and driver logic
- Easy to extend with new instructions
------------------------------------------------------

## Build Instructions
Make sure you are in the project root directory.

### Compile

```bash
g++ -Iinclude src/*.cpp -o assembler

### Execute

./assembler
---------------------------------------------------------
#Notes

-Header files contain only declarations
-All implementations are in .cpp files
-Clean include paths handled using -Iinclude

#Future Improvements

-Full RISC-V ISA support
-Label handling and symbol table
-Improved error diagnostics
-Hexadecimal output support

-----------------------------------------------------------