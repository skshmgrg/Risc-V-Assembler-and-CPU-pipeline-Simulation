#ifndef ISA_UTILS_H
#define ISA_UTILS_H

#include <string>
using namespace std;

string immToBin(int imm, int bits);
string regToBin(const string& reg);
string clean (const string &ins);


#endif