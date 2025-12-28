#include"utility.h"
using namespace std;

int binary_to_decimal(const string &binary) {
    int p2 = 1;
    int ans = 0;
    for(int i=binary.size()-1; i>=0; i--){
        ans += p2 * (binary[i]-'0');
        p2 <<= 1;
    }
    return ans;
}

int binary_to_decimal_signed(const string &binary) {
    // cout << "binary = " << binary << endl;
    int n = binary.size();
    bool negative = (binary[0]=='1');
    int value = binary_to_decimal(binary);
    if(negative) value -= (1<<n);
    return value;
}

int immGen(string &ins_type, string &ins){
    if(ins_type=="IA" || ins_type=="IL" || ins_type=="IJ"){
        return binary_to_decimal_signed(ins.substr(0,12));
    }
    else if(ins_type=="S" || ins_type=="B"){
        return binary_to_decimal_signed(ins.substr(0,7)+ins.substr(20,5));
    }
    else if(ins_type=="J"){
        return binary_to_decimal_signed(ins.substr(0,20));
    }
    return 0;
}
