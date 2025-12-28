#ifndef FORWARDING_UNIT_H
#define FORWARDING_UNIT_H
// #include<iostream>
#include<pipeline_registers.h>
using namespace std;

//forwarder 1 sees if the previous instructions in pipeline can provide their output at this stage , in case of a read after write dependency at register rsl1
int forwarder1(int rsl1, PipeLineReg4 &EXMO, PipeLineReg5 &MOWB);

//forwarder 2 sees if the previous instructions in pipeline can provide their output at this stage , in case of a read after write dependency at register rsl2
int forwarder2(int rsl2, PipeLineReg4 &EXMO, PipeLineReg5 &MOWB);

#endif