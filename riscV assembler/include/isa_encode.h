#ifndef ISA_ENCODE_H
#define ISA_ENCODE_H

#include<iostream>
#include<unordered_map>
#include<string>
#include<sstream>

#include "isa_utils.h"
#include "isa_data.h"
using namespace std;

string encodeR(const InstructionInfo &info, const string &rd, const string &rs1, const string &rs2);

string encodeI(const InstructionInfo &info, const string &rd, const string &rs1, int imm);

string encodeS(const InstructionInfo &info, const string &rs1, const string &rs2, int imm);

string encodeB(const InstructionInfo &info, const string &rs1, const string &rs2, int imm);

string encodeJ(const InstructionInfo &info, const string &rd, int imm);

string encodeU(const InstructionInfo &info, const string &rd, int imm);

// a commom encode function for both pseudo instructions and standard instructions
string encodeInstruction(string &line);


#endif