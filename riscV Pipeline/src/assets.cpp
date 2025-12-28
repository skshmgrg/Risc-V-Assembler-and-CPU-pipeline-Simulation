#include "assets.h"
#include <utility>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

pair<int, int> ALU(string &ALUSelect, int alusrc1, int alusrc2){
    bool ALUFlag = 0;

    if(ALUSelect == "0000"){
        ALUFlag = 0;
        return {alusrc1 & alusrc2, ALUFlag};
    }
    else if(ALUSelect == "0001"){
        ALUFlag = 0;
        return {alusrc1 | alusrc2, ALUFlag};
    }
    else if(ALUSelect == "1010"){
        ALUFlag = 0;
        return {alusrc1 * alusrc2, ALUFlag};
    }
    else if(ALUSelect == "1001"){
        ALUFlag = 0;
        return {alusrc1 % alusrc2, ALUFlag};
    }
    else if(ALUSelect == "0011"){
        ALUFlag = 0;
        return {alusrc1 << alusrc2, ALUFlag};
    }
    else if(ALUSelect == "0101"){ // srai
        ALUFlag = 0;
        return {alusrc1 >> alusrc2, ALUFlag};
    }
    else if(ALUSelect == "0010"){
        ALUFlag = 0;
        return {alusrc1 + alusrc2, ALUFlag};
    }
    else if(ALUSelect == "0110"){
        ALUFlag = 0;
        return {alusrc1 - alusrc2, ALUFlag};
    }
    else if(ALUSelect == "0100"){
        ALUFlag = (alusrc1 == alusrc2);
        return {alusrc1 - alusrc2, ALUFlag};
    }
    else if(ALUSelect == "0111"){
        ALUFlag = (alusrc1 != alusrc2);
        return {alusrc1 - alusrc2, ALUFlag};
    }
    else if(ALUSelect == "1111"){
        ALUFlag = (alusrc1 < alusrc2);
        return {alusrc1 - alusrc2, ALUFlag};
    }
    else if(ALUSelect == "1110"){
        ALUFlag = (alusrc1 >= alusrc2);
        return {alusrc1 - alusrc2, ALUFlag};
    }
    else{
        // cout << "ALUSelect = " << ALUSelect << endl;
        perror("Invalid ALUSelect\n");
        exit(1);
    }
}

int MUX(int select, int arg1, int arg2, int arg3 , int arg4 ){
    switch (select){
        case 0:
            return arg1;
        case 1:
            return arg2;
        case 2:
            return arg3;
        case 3:
            return arg4;
        default:
            cerr << "Invalid Select Line in MUX" << endl;
            exit(1);
    }
}

int  MemoryBlock::memRead(int address){
        return memory[address/4];
    }
void MemoryBlock::memWrite(int address,int val){
        memory[address/4] = val;
    }
    
int  RegisterFetch::regRead(int regNum){
        return registers[regNum];
    }
void RegisterFetch::regWrite(int regNum,int val){
        if(regNum!=0)
        registers[regNum] = val;
    }
    
vector <int> RegisterFetch::registers(32, 0);
vector <int> MemoryBlock::memory(1024, 0);

