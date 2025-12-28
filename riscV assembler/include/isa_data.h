#ifndef ISA_DATA_H
#define ISA_DATA_H

#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;

struct InstructionInfo{
    string opcode, func3, func7;
    char type;
};                                                                                                                                                                                              
extern unordered_map <string, InstructionInfo> mpp;
extern unordered_map <string, string> registers;
void initialiseInstructionMap();
void initialiseRegisterMap();

#endif