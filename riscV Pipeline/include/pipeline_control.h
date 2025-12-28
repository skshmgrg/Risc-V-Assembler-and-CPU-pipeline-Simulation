#ifndef PIPELINE_CONTROL_H
#define PIPELINE_CONTROL_H
#include<iostream>
using namespace std;

string instructionType(string &opcode);

class ControlWord{
    public:
    bool ALUSrc;
    bool memToReg;
    bool regRead;
    bool regWrite;
    bool memRead;
    bool memWrite;
    bool branch;
    bool jump;
    bool jumpr;
    string ALUOp;
    string ALUSelect;

    ControlWord();
};

//genertaes control word signals
ControlWord controlUnit(string &insType);

//generates ALU select based on ALUOp, func3 and func7
void ALUControl(ControlWord &CW, string &func3, string &func7);
#endif