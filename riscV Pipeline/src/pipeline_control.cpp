#include "pipeline_control.h"
#include <cstdlib>   // for exit()

// ================= Instruction Type Decoder =================

string instructionType(string &opcode) {
    if (opcode == "0110011") return "R";
    if (opcode == "0010011") return "IA";
    if (opcode == "0000011") return "IL";
    if (opcode == "0100011") return "S";
    if (opcode == "1100011") return "B";
    if (opcode == "1101111") return "J";
    if (opcode == "1100111") return "IJ";

    cerr << "Invalid opcode: " << opcode << endl;
    exit(1);
}

// ================= ControlWord =================

ControlWord::ControlWord() {
    ALUSrc    = false;
    memToReg  = false;
    regRead   = false;
    regWrite  = false;
    memRead   = false;
    memWrite  = false;
    branch    = false;
    jump      = false;
    jumpr     = false;
}

// ================= Control Unit =================

ControlWord controlUnit(string &insType) {
    ControlWord CW;

    if (insType == "R") {
        CW.ALUSrc    = 0;
        CW.memToReg  = 0;
        CW.regRead   = 1;
        CW.regWrite  = 1;
        CW.memRead   = 0;
        CW.memWrite  = 0;
        CW.branch    = 0;
        CW.jump      = 0;
        CW.jumpr     = 0;
        CW.ALUOp     = "10";
    }
    else if (insType == "IA") {
        CW.ALUSrc    = 1;
        CW.memToReg  = 0;
        CW.regRead   = 1;
        CW.regWrite  = 1;
        CW.memRead   = 0;
        CW.memWrite  = 0;
        CW.branch    = 0;
        CW.jump      = 0;
        CW.jumpr     = 0;
        CW.ALUOp     = "11";
    }
    else if (insType == "IL") {
        CW.ALUSrc    = 1;
        CW.memToReg  = 1;
        CW.regRead   = 1;
        CW.regWrite  = 1;
        CW.memRead   = 1;
        CW.memWrite  = 0;
        CW.branch    = 0;
        CW.jump      = 0;
        CW.jumpr     = 0;
        CW.ALUOp     = "00";
    }
    else if (insType == "S") {
        CW.ALUSrc    = 1;
        CW.memToReg  = 0;
        CW.regRead   = 1;
        CW.regWrite  = 0;
        CW.memRead   = 0;
        CW.memWrite  = 1;
        CW.branch    = 0;
        CW.jump      = 0;
        CW.jumpr     = 0;
        CW.ALUOp     = "00";
    }
    else if (insType == "B") {
        CW.ALUSrc    = 0;
        CW.memToReg  = 0;
        CW.regRead   = 1;
        CW.regWrite  = 0;
        CW.memRead   = 0;
        CW.memWrite  = 0;
        CW.branch    = 1;
        CW.jump      = 0;
        CW.jumpr     = 0;
        CW.ALUOp     = "01";
    }
    else if (insType == "J") {
        CW.ALUSrc    = 0;
        CW.memToReg  = 0;
        CW.regRead   = 0;
        CW.regWrite  = 1;
        CW.memRead   = 0;
        CW.memWrite  = 0;
        CW.branch    = 0;
        CW.jump      = 1;
        CW.jumpr     = 0;
        CW.ALUOp     = "00";
    }
    else if (insType == "IJ") {
        CW.ALUSrc    = 1;
        CW.memToReg  = 0;
        CW.regRead   = 1;
        CW.regWrite  = 1;
        CW.memRead   = 0;
        CW.memWrite  = 0;
        CW.branch    = 0;
        CW.jump      = 0;
        CW.jumpr     = 1;
        CW.ALUOp     = "00";
    }

    return CW;
}

// ================= ALU Control =================

void ALUControl(ControlWord &CW, string &func3, string &func7) {
    if (CW.ALUOp == "00") {
        CW.ALUSelect = "0010";   // jump, store, load
    }
    else if (CW.ALUOp == "01") {
        if (func3 == "000")      CW.ALUSelect = "0100"; // beq
        else if (func3 == "001") CW.ALUSelect = "0111"; // bne
        else if (func3 == "100") CW.ALUSelect = "1111"; // blt
        else                     CW.ALUSelect = "1110"; // bge
    }
    else if (CW.ALUOp == "10") {
        if (func7[1] == '1') {
            if (func3 == "000")
                CW.ALUSelect = "0110"; // sub, sra
        }
        else if (func7[6] == '1') {
            if (func3 == "000") CW.ALUSelect = "1010"; // mul
            else                CW.ALUSelect = "1001"; // rem
        }
        else {
            if      (func3 == "000") CW.ALUSelect = "0010"; // add
            else if (func3 == "111") CW.ALUSelect = "0000"; // and
            else if (func3 == "110") CW.ALUSelect = "0001"; // or
        }
    }
    else {
        if      (func3 == "000") CW.ALUSelect = "0010"; // addi
        else if (func3 == "111") CW.ALUSelect = "0000"; // andi
        else if (func3 == "110") CW.ALUSelect = "0001"; // ori
        else if (func3 == "001") CW.ALUSelect = "0011"; // slli
        else if (func3 == "101") CW.ALUSelect = "0101"; // srai
    }
}
