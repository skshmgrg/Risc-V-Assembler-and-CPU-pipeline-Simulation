#include "pipeline_registers.h"
#include <string>
#include <vector>
// #include <iostream>

using namespace std;

// ================= PipeLineReg1 =================

PipeLineReg1::PipeLineReg1() {
    PC = -4;
    stall = false;
}

PipeLineReg1::PipeLineReg1(int PC) {
    this->PC = PC;
    stall = false;
}

// ================= PipeLineReg2 =================

PipeLineReg2::PipeLineReg2() {
    DPC = 0;
    instr = NOP;
    stall = false;
}

PipeLineReg2::PipeLineReg2(int DPC, const string &instr) {
    this->DPC = DPC;
    this->instr = instr;
    stall = false;
}

void PipeLineReg2::flush() {
    DPC = 0;
    instr = NOP;
    stall = false;
}

// ================= PipeLineReg3 =================

PipeLineReg3::PipeLineReg3() {
    DPC = 0;
    imm = 0;
    rs1 = rs2 = 0;
    rsl1 = rsl2 = 0;
    rdl = 0;
    func3 = "000";
    func7 = "";
    CW = ControlWord();
}

PipeLineReg3::PipeLineReg3(
    int DPC, int imm, int rs1, int rs2,
    int rsl1, int rsl2,
    string &func3, string &func7,
    int rdl, const ControlWord &CW
) {
    this->DPC = DPC;
    this->imm = imm;
    this->rs1 = rs1;
    this->rs2 = rs2;
    this->rsl1 = rsl1;
    this->rsl2 = rsl2;
    this->func3 = func3;
    this->func7 = func7;
    this->rdl = rdl;
    this->CW = CW;
}

void PipeLineReg3::flush() {
    DPC = 0;
    imm = 0;
    rs1 = rs2 = 0;
    rsl1 = rsl2 = 0;
    rdl = 0;
    func3 = "000";
    func7 = "";
    CW = ControlWord();
}

// ================= PipeLineReg4 =================

PipeLineReg4::PipeLineReg4() {
    TPC = 0;
    NPC = 0;
    ALUResult = 0;
    rs2 = 0;
    rdl = 0;
}

PipeLineReg4::PipeLineReg4(
    int TPC, int NPC, int ALUResult,
    int rs2, int rdl,
    const ControlWord &CW
) {
    this->TPC = TPC;
    this->NPC = NPC;
    this->ALUResult = ALUResult;
    this->rs2 = rs2;
    this->rdl = rdl;
    this->CW = CW;
}

// ================= PipeLineReg5 =================

PipeLineReg5::PipeLineReg5() {
    TPC = 0;
    NPC = 0;
    ALUResult = 0;
    LDResult = 0;
    rdl = 0;
}

PipeLineReg5::PipeLineReg5(
    int TPC, int NPC, int ALUResult,
    int LDResult, int rdl,
    const ControlWord &CW
) {
    this->TPC = TPC;
    this->NPC = NPC;
    this->ALUResult = ALUResult;
    this->LDResult = LDResult;
    this->rdl = rdl;
    this->CW = CW;
}



