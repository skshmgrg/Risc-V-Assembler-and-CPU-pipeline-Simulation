#include "pipeline_datapath.h"
#include "assets.h"
#include<iostream>
#include<fstream>
#include<string>


int main(){
    ifstream input_file("input.txt");
    if(!input_file.is_open()){
        perror("Error in opening file\n");
        exit(1);
    }
    
    vector <string> im;
    string line;
    while(getline(input_file, line)){
        im.push_back(line);
    }

    RegisterFetch::regWrite(1, im.size()*4); // set return address
    RegisterFetch::regWrite(2, 1024*4);      // set stack pointer
    
    PipeLineReg1 IM;
    PipeLineReg2 IFID;
    PipeLineReg3 IDEX;
    PipeLineReg4 EXMO;
    PipeLineReg5 MOWB;
    
    int maxPC = 4*im.size(), cnt = 0;
    bool pipelineEmpty = false;

    while(!pipelineEmpty){
        cnt++;
        /*we are executing the pipeline in reverse order in our code , as a sequential simulation of pipeline
        stages (in code) requires the need that the values fed in the registers in the previous clock cycle shall be used
        in the current clock cycle as inuts , not the values fed in the current clock cycle */

        WriteBack(MOWB, IM, IM.PC + 4);

        MemoryOperation(EXMO, MOWB);

        bool flush;
        execute(IDEX, EXMO, MOWB, flush);

        if(flush){
            IFID.flush();
            IDEX.flush();
            IM = PipeLineReg1(EXMO.TPC);
        }

        decode(IFID, IDEX, IM, EXMO, MOWB);

        fetch(IM, IFID, im, maxPC);
        
        //hasValidInstructions checks if the pipeline has any of the valid instructions currently, by checking if any combination of CW flags are set, that corresponds to a valid instruction
        bool hasValidInstructions = (IFID.instr!=NOP ||
            (IDEX.rdl!=0 && IDEX.CW.regWrite) || IDEX.CW.memWrite || IDEX.CW.branch || IDEX.CW.jump || IDEX.CW.jumpr ||
            (EXMO.rdl!=0 && EXMO.CW.regWrite) || EXMO.CW.memWrite || EXMO.CW.branch || EXMO.CW.jump || EXMO.CW.jumpr ||
            (MOWB.rdl!=0 && MOWB.CW.regWrite) || MOWB.CW.memWrite || MOWB.CW.branch || MOWB.CW.jump || MOWB.CW.jumpr);

        pipelineEmpty = (IM.PC >= maxPC && !hasValidInstructions);
    }

    cout << "\nNumber of cycles: " << cnt << '\n';
    
    cout << "Registers: ";
    for(int i=0; i<32; i++){
        cout << RegisterFetch::regRead(i) << ' ';
    }
    cout << endl;

    // for(auto it: memory){
    //     cout << it << ' ';
    // }
    // cout << endl;

    return 0;
}