#ifndef PIPELINE_REGISTERS_H
#define PIPELINE_REGISTERS_H
#include "pipeline_control.h"
#define NOP "00000000000000000000000000010011"

#include<iostream>
using namespace std;

class PipeLineReg1{
    public:
    int PC;
    bool stall;
    
    PipeLineReg1();
    PipeLineReg1(int PC);
};

//set of registers at Instruction fetch and decode stage(stage 2 of pipeline)
class PipeLineReg2{
    public:
    int DPC;
    string instr;
    bool stall;
    
    PipeLineReg2();
    PipeLineReg2(int DPC, const string&instr);
    void flush();
};

//set of registers at Instruction decode and execute stage(stage 3 of pipeline)
class PipeLineReg3{
    public:
    int DPC, imm, rs1, rs2, rsl1, rsl2, rdl;
    ControlWord CW;
    string func3, func7;
    
    PipeLineReg3();
    PipeLineReg3(int DPC, int imm, int rs1, int rs2, int rsl1, int rsl2, string &func3, string &func7, int rdl, const ControlWord &CW);
    void flush();
};

//set of registers at Instruction execute and memory operation stage(stage 4 of pipeline)
class PipeLineReg4{
    public:
    int TPC, NPC, ALUResult, rs2, rdl;
    ControlWord CW;
    
    PipeLineReg4();
    PipeLineReg4(int TPC, int NPC, int ALUResult, int rs2, int rdl, const ControlWord &CW);
};


//set of registers at Instruction memory operation and write back stage(stage 5 of pipeline)
class PipeLineReg5{
    public:
    int TPC, NPC, ALUResult, LDResult, rdl;
    ControlWord CW;

    PipeLineReg5();
    PipeLineReg5(int TPC, int NPC, int ALUResult, int LDResult, int rdl, const ControlWord &CW);
};

#endif