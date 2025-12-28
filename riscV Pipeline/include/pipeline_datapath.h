#ifndef PIPELINE_DATAPATH_H
#define PIPELINE_DATAPATH_H

#include "pipeline_registers.h"
#include <vector>
#define NOP "00000000000000000000000000010011"

using namespace std;

void fetch(PipeLineReg1 &IM, PipeLineReg2 &IFID, vector<string>&instructionMemory, int maxPC);
void decode(PipeLineReg2 &IFID, PipeLineReg3 &IDEX,PipeLineReg1 &IM,PipeLineReg4 &EXMO,PipeLineReg5 &MOWB);
void execute(PipeLineReg3 &IDEX, PipeLineReg4 &EXMO, PipeLineReg5 &MOWB, bool &flush);
void MemoryOperation(PipeLineReg4 &EXMO, PipeLineReg5& MOWB);
void WriteBack(PipeLineReg5 &MOWB, PipeLineReg1 &IM, int NPC);

#endif