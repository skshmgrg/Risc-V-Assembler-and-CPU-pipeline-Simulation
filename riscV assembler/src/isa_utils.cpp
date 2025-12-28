#include "isa_utils.h"
#include "isa_data.h"
#include <bitset>
#include <unordered_map>

using namespace std;

//function used to remove commas from instructions
string clean(const string &ins){
    string s;
    for(char c: ins){
        if(c!=',') s += c;
    }
    return s;
}

//converts register number to binary
string regToBin(const string &reg){
    string curr_reg = clean(reg);
   
    if(registers.count(curr_reg)) curr_reg = registers[curr_reg];
   
    if(curr_reg[0]!='x'){
        perror("Invalid Register\n");
        exit(1);
    }

    int num = stoi(curr_reg.substr(1));
    if(num<0 || num>31){
        perror("Register out of range\n");
        exit(1);
    }
    return bitset<5>(num).to_string();
}
//converts the immediate value to binary
string immToBin(int imm, int bits){
    if(imm<0) imm = (1<<bits) + imm;
    return bitset<32>(imm).to_string().substr(32-bits, bits);
}
