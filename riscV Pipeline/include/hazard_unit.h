#ifndef HAZARD_UNIT_H
#define HAZARD_UNIT_H

#include<pipeline_registers.h>
using namespace std;

// hazardUnit checks if there a RAW (Read After Write) data hazard and if the pipeline should stall at decode stage due to the hazard
bool hazardUnit(PipeLineReg4 &EXMO, PipeLineReg5 &MOWB, int rsl1, int rsl2);

#endif