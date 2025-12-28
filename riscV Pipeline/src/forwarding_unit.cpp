#include "pipeline_registers.h"
#include <string>
#include <vector>

using namespace std;

//forwarder 1 sees if the previous instructions in pipeline can provide their output at this stage , in case of a read after write dependency at register rsl1
int forwarder1(int rsl1, PipeLineReg4 &EXMO, PipeLineReg5 &MOWB){
    if(rsl1!=0 && EXMO.rdl!=0 && rsl1==EXMO.rdl && EXMO.CW.regWrite && !EXMO.CW.memRead){
        return 1;
    }
    if(rsl1!=0 && MOWB.rdl!=0 && rsl1==MOWB.rdl && MOWB.CW.regWrite){
        if(MOWB.CW.memRead) return 2;
        else return 3;
    }
    return 0;
}

//forwarder 2 sees if the previous instructions in pipeline can provide their output at this stage , in case of a read after write dependency at register rsl2
int forwarder2(int rsl2, PipeLineReg4 &EXMO, PipeLineReg5 &MOWB){
    if(rsl2!=0 && EXMO.rdl!=0 && rsl2==EXMO.rdl && EXMO.CW.regWrite && !EXMO.CW.memRead){
        return 1;
    }
    if(rsl2!=0 && MOWB.rdl!=0 && rsl2==MOWB.rdl && MOWB.CW.regWrite){
        if(MOWB.CW.memRead) return 2;
        else return 3;
    }
    return 0;
}