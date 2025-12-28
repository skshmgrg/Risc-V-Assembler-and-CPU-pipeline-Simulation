#include<iostream>
#include<unordered_map>
#include "isa_data.h"

using namespace std;

unordered_map<string, InstructionInfo> mpp;
unordered_map<string, string> registers;

void initialiseInstructionMap(){

    /*Register type instructions*/
    mpp["add"] = {"0110011", "000", "0000000", 'R'};
    mpp["slt"] = {"0110011", "010", "0000000", 'R'};
    mpp["sltu"]= {"0110011", "011", "0000000", 'R'};
    mpp["and"] = {"0110011", "111", "0000000", 'R'};
    mpp["or"]  = {"0110011", "110", "0000000", 'R'};
    mpp["xor"] = {"0110011", "100", "0000000", 'R'};
    mpp["sll"] = {"0110011", "001", "0000000", 'R'};
    mpp["srl"] = {"0110011", "101", "0000000", 'R'};
    mpp["sub"] = {"0110011", "000", "0100000", 'R'};
    mpp["sra"] = {"0110011", "101", "0100000", 'R'};
    mpp["mul"] = {"0110011", "000", "0000001", 'R'};
    mpp["rem"] = {"0110011", "110", "0000001", 'R'};
    
    /*Immidiate type instructions*/
    mpp["addi"] = {"0010011", "000", "", 'I'};
    mpp["slti"] = {"0010011", "010", "", 'I'};
    mpp["sltiu"]= {"0010011", "011", "", 'I'};
    mpp["andi"] = {"0010011", "111", "", 'I'};
    mpp["ori"]  = {"0010011", "110", "", 'I'};
    mpp["xori"] = {"0010011", "100", "", 'I'};
    
    /*Immidiate type instructions (shift operation)*/
    mpp["slli"] = {"0010011", "001", "0000000", 'I'};
    mpp["srli"] = {"0010011", "101", "0000000", 'I'};
    mpp["srai"] = {"0010011", "101", "0100000", 'I'};
   
    /*load type instructions*/
    mpp["lw"] = {"0000011", "010", "", 'I'};
    mpp["ld"] = {"0000011", "011", "", 'I'};
    mpp["lh"] = {"0000011", "001", "", 'I'};
    mpp["lb"] = {"0000011", "000", "", 'I'};
    mpp["lwu"]= {"0000011", "110", "", 'I'};
    mpp["lhu"]= {"0000011", "101", "", 'I'};
    mpp["lbu"]= {"0000011", "100", "", 'I'};
    
    /*store type instructions*/
    mpp["sd"] = {"0100011", "011", "", 'S'};
    mpp["sw"] = {"0100011", "010", "", 'S'};
    mpp["sh"] = {"0100011", "001", "", 'S'};
    mpp["sb"] = {"0100011", "000", "", 'S'};
    
    /*branch type instructions*/
    mpp["beq"] = {"1100011", "000", "", 'B'};
    mpp["bne"] = {"1100011", "001", "", 'B'};
    mpp["blt"] = {"1100011", "100", "", 'B'};
    mpp["bltu"]= {"1100011", "110", "", 'B'};
    mpp["bge"] = {"1100011", "101", "", 'B'};
    mpp["bgeu"]= {"1100011", "111", "", 'B'};
    
    /*jump instructions*/
    mpp["jal"] = {"1101111", "", "", 'J'};
    mpp["jalr"]= {"1100111", "000", "", 'I'};

    /*upper immidiate type instructions*/
    mpp["lui"]  = {"0110111", "", "", 'U'};
    mpp["auipc"]= {"0010111", "", "", 'U'};
}

/*registers mapping*/
void initialiseRegisterMap(){
    registers["zero"] = "x0";
    registers["r0"] = "x0";
    registers["ra"] = "x1";
    registers["sp"] = "x2";
    registers["gp"] = "x3";
    registers["tp"] = "x4";
    registers["t0"] = "x5";
    registers["t1"] = "x6";
    registers["t2"] = "x7";
    registers["s0"] = "x8";
    registers["s1"] = "x9";
    registers["a0"] = "x10";
    registers["a1"] = "x11";
    registers["a2"] = "x12";
    registers["a3"] = "x13";
    registers["a4"] = "x14";
    registers["a5"] = "x15";
    registers["a6"] = "x16";
    registers["a7"] = "x17";
    registers["s2"] = "x18";
    registers["s3"] = "x19";
    registers["s4"] = "x20";
    registers["s5"] = "x21";
    registers["s6"] = "x22";
    registers["s7"] = "x23";
    registers["s8"] = "x24";
    registers["s9"] = "x25";
    registers["s10"]= "x26";
    registers["s11"]= "x27";
    registers["t3"] = "x28";
    registers["t4"] = "x29";
    registers["t5"] = "x30";
    registers["t6"] = "x31";
}
