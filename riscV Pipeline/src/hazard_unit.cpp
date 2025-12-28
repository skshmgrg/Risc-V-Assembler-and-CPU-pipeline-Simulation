#include "pipeline_registers.h"
#include <string>
#include <vector>

using namespace std;

// hazardUnit checks if there a RAW (Read After Write) data hazard and if the pipeline should stall at decode stage due to the hazard
bool hazardUnit(PipeLineReg4 &EXMO, PipeLineReg5 &MOWB, int rsl1, int rsl2){
    if(EXMO.CW.regWrite && ((rsl1!=0 && EXMO.rdl == rsl1) || (rsl2!=0 && EXMO.rdl == rsl2))){
        return true;
    }
    if(MOWB.CW.regWrite && ((rsl1!=0 && MOWB.rdl == rsl1) || (rsl2!=0 && MOWB.rdl == rsl2))){
        return true;
    }
    return false;
}
