#include "isa_utils.h"
#include "isa_data.h"
#include "isa_encode.h"
#include <bitset>
#include <unordered_map>

using namespace std;

string encodeR(const InstructionInfo &info, const string &rd, const string &rs1, const string &rs2){
    return info.func7 + regToBin(rs2) + regToBin(rs1) + info.func3 + regToBin(rd) + info.opcode;
}

string encodeI(const InstructionInfo &info, const string &rd, const string &rs1, int imm){
    if(info.func7 != "") return info.func7 + immToBin(imm, 5) + regToBin(rs1) + info.func3 + regToBin(rd) + info.opcode;
    else return immToBin(imm, 12) + regToBin(rs1) + info.func3 + regToBin(rd) + info.opcode;
}

string encodeS(const InstructionInfo &info, const string &rs1, const string &rs2, int imm){
    string immBinary = immToBin(imm, 12);
   
    return immBinary.substr(0, 7) + regToBin(rs2) + regToBin(rs1) + info.func3 + immBinary.substr(7, 5) + info.opcode;
}

string encodeB(const InstructionInfo &info, const string &rs1, const string &rs2, int imm){
    string immBinary = immToBin(imm, 12);
   
    return immBinary.substr(0, 7) + regToBin(rs2) + regToBin(rs1) + info.func3 + immBinary.substr(7, 5) + info.opcode;
}

string encodeJ(const InstructionInfo &info, const string &rd, int imm){
    string immBinary = immToBin(imm, 20);
   
    return immBinary + regToBin(rd) + info.opcode;
}

string encodeU(const InstructionInfo &info, const string &rd, int imm){
    return immToBin(imm, 20) + regToBin(rd) + info.opcode;
}

// a commom encode function for both pseudo instructions and standard instructions
string encodeInstruction(string &line){

    string modified_line;

    for(int i=0;i<line.size();i++)
    {
        if(line[i]==',')
        {
            modified_line.push_back(' ');
        }
        else
        {
            modified_line.push_back(line[i]);
        }
    }
    istringstream iss(modified_line);
   
    string instr;
    iss >> instr;
   
    //handling pseudo instructions
    if(instr == "mv"){
        string rd, rs;
        iss >> rd >> rs;
        line = "add " + rd + " " + rs + " zero";
        return encodeInstruction(line);
    }
    else if(instr == "nop"){
        line = "addi zero zero 0";
        return encodeInstruction(line);
    }
    else if(instr == "li"){
        string rd, immStr;
        iss >> rd >> immStr;
        
        line = "addi " + rd + " zero " + immStr;
        return encodeInstruction(line);
    }
    else if(instr == "j"){
        string immStr;
        iss >> immStr;
        line = "jal zero " + immStr;
        return encodeInstruction(line);
    }
    else if(instr == "jr"){
        string rs;
        iss >> rs;
        line = "jalr zero " + rs + " 0";
        return encodeInstruction(line);
    }
    else if(instr == "ble"){
        string rs1, rs2;
        int imm;
        iss >> rs1 >> rs2 >> imm;
        line = "bge " + rs2 + " " + rs1 + " " + to_string(imm);
        return encodeInstruction(line);
    }
    else if(instr == "bgt"){
        string rs1, rs2;
        int imm;
        iss >> rs1 >> rs2 >> imm;
        line = "blt " + rs2 + " " + rs1 + " " + to_string(imm);
        return encodeInstruction(line);
    }
    else if(instr == "bgtu"){
        string rs1, rs2;
        int imm;
        iss >> rs1 >> rs2 >> imm;
        line = "bltu " + rs2 + " " + rs1 + " " + to_string(imm);
        return encodeInstruction(line);
    }
    else if(instr == "bleu"){
        string rs1, rs2;
        int imm;
        iss >> rs1 >> rs2 >> imm;
        line = "bgeu " + rs2 + " " + rs1 + " " + to_string(imm);
        return encodeInstruction(line);
    }

    auto it = mpp.find(instr);
   
    if(it == mpp.end()){
        perror("Unknown instruction\n");
        exit(1);
    }
   
    InstructionInfo info = it->second;
   
    if(info.type == 'R'){
        string rd, rs1, rs2;
        iss >> rd >> rs1 >> rs2;
       
        rd = clean(rd), rs1 = clean(rs1), rs2 = clean(rs2);
        return encodeR(info, rd, rs1, rs2);
    }
    if(info.type == 'I'){
        string rd, rs1, immStr;
        iss >> rd >> rs1 >> immStr;
       
        if(immStr == ""){
            immStr = rs1;
            rd = clean(rd), immStr = clean(immStr);
           
            size_t pos1 = immStr.find('(');
            size_t pos2 = immStr.find(')');
           
            return encodeI(info, rd, clean(immStr.substr(pos1+1, pos2-pos1-1)), stoi(immStr.substr(0, pos1)));
        }
        else {
            rd = clean(rd), rs1 = clean(rs1), immStr = clean(immStr);
            return encodeI(info, rd, rs1, stoi(immStr));
        }
    }
    if(info.type == 'S'){
        string rs2, offsetRs1;
        iss >> rs2 >> offsetRs1;
       
        rs2 = clean(rs2), offsetRs1 = clean(offsetRs1);
       
        size_t pos1 = offsetRs1.find('(');
        size_t pos2 = offsetRs1.find(')');
       
        return encodeS(info, offsetRs1.substr(pos1+1, pos2-pos1-1), rs2, stoi(offsetRs1.substr(0, pos1)));
    }
    if(info.type == 'B'){
        string rs1, rs2;
        int imm;
        iss >> rs1 >> rs2 >> imm;
       
        rs1 = clean(rs1), rs2 = clean(rs2);
       
        return encodeB(info, rs1, rs2, imm);
    }
    if(info.type == 'U'){
        string rd;
        int imm;
       
        iss >> rd >> imm;
        rd = clean(rd);
       
        return encodeU(info, rd, imm);
    }
    if(info.type == 'J'){
        string rd;
        int imm;
        iss >> rd >> imm;
       
        rd = clean(rd);
        return encodeJ(info, rd, imm);
    }
   
    perror("Unsupported instruction type\n");
    exit(1);
}