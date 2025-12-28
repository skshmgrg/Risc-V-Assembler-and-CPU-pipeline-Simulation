#ifndef PIPELINE_ASSETS_H
#define PIPELINE_ASSETS_H

#include<vector>
#include<string>
using namespace std;

pair<int, int> ALU(string &ALUSelect, int alusrc1, int alusrc2);

int MUX(int select, int arg1, int arg2, int arg3 = 0, int arg4 = 0);

class RegisterFetch {
private:
    static vector<int> registers; 
public:
    static int regRead(int regNum);
    static void regWrite(int regNum, int val);
};

class MemoryBlock{
private:
    static vector<int> memory;
public:
    static int memRead(int address);
    static void memWrite(int address, int val);
};

#endif