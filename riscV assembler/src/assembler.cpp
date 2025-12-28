#include <iostream>
#include <sstream>
#include "isa_data.h"   
#include "isa_encode.h" 
#include <fstream> 
using namespace std;

int main(){
    initialiseInstructionMap();
    initialiseRegisterMap();
   
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
   
    if(!input_file.is_open()){
        perror("Error in opening file\n");
        exit(1);
    }
    if(!output_file.is_open()){
        perror("Error in opening file\n");
        exit(1);
    }
   
    string line;
    while (getline(input_file, line)) {
        if (line.empty()) continue;
        string encoded = encodeInstruction(line);          
        output_file << encoded << endl;            
    }
   
    input_file.close();
    output_file.close();
   
    return 0;
}