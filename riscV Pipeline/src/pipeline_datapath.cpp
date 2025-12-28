#include "pipeline_datapath.h"
#include "utility.h"
#include "assets.h"
#include "hazard_unit.h"
#include "forwarding_unit.h"


// ========================== FETCH ==========================

void fetch(PipeLineReg1 &IM,
           PipeLineReg2 &IFID,
           vector<string> &instructionMemory,
           int maxPC)
{
    if (IM.stall)
        return;

    if (IM.PC >= maxPC)
    {
        IFID = PipeLineReg2();
        return;
    }

    IFID = PipeLineReg2(IM.PC, instructionMemory[IM.PC / 4]);
}

// ========================== DECODE ==========================

void decode(PipeLineReg2 &IFID,
            PipeLineReg3 &IDEX,
            PipeLineReg1 &IM,
            PipeLineReg4 &EXMO,
            PipeLineReg5 &MOWB)
{
    string ins = IFID.instr;
    string opcode = ins.substr(25, 7);

    int rsl1 = binary_to_decimal(ins.substr(12, 5));
    int rsl2 = binary_to_decimal(ins.substr(7, 5));

    string ins_type = instructionType(opcode);
    ControlWord CW = controlUnit(ins_type);

    // Handle stall recovery
    if (IFID.stall)
    {
        if (CW.regRead && hazardUnit(EXMO, MOWB, rsl1, rsl2))
        {
            return;
        }
        else
        {
            IM.stall = false;
            IFID.stall = false;
        }
    }

    // NOP handling
    if (ins == NOP && IFID.DPC == 0)
    {
        IDEX = PipeLineReg3();
        return;
    }

    // RAW hazard detection
    if (CW.regRead && hazardUnit(EXMO, MOWB, rsl1, rsl2))
    {
        IM.stall = true;
        IFID.stall = true;
        return;
    }

    string func3 = ins.substr(17, 3);
    string func7 = ins.substr(0, 7);
    int rdl = binary_to_decimal(ins.substr(20, 5));
    int imm = immGen(ins_type, ins);

    int rs1 = 0, rs2 = 0;
    if (CW.regRead)
    {
        rs1 = RegisterFetch::regRead(rsl1);
        rs2 = RegisterFetch::regRead(rsl2);
    }

    IDEX = PipeLineReg3(
        IFID.DPC,
        imm,
        rs1,
        rs2,
        rsl1,
        rsl2,
        func3,
        func7,
        rdl,
        CW);

    IFID = PipeLineReg2();
}

// ========================== EXECUTE ==========================

void execute(PipeLineReg3 &IDEX,
             PipeLineReg4 &EXMO,
             PipeLineReg5 &MOWB,
             bool &flush)
{
    int rs1 = RegisterFetch::regRead(IDEX.rsl1);
    int rs2 = RegisterFetch::regRead(IDEX.rsl2);

    int select1 = forwarder1(IDEX.rsl1, EXMO, MOWB);
    int select2 = forwarder2(IDEX.rsl2, EXMO, MOWB);

    int alusrc1 = MUX(select1,
                      rs1,
                      EXMO.ALUResult,
                      MOWB.LDResult,
                      MOWB.ALUResult);

    int alusrc2 = IDEX.CW.ALUSrc
                      ? IDEX.imm
                      : MUX(select2,
                            rs2,
                            EXMO.ALUResult,
                            MOWB.LDResult,
                            MOWB.ALUResult);

    ALUControl(IDEX.CW, IDEX.func3, IDEX.func7);

    auto it = ALU(IDEX.CW.ALUSelect, alusrc1, alusrc2);
    int ALUResult = it.first;
    bool BranchFlag = it.second;

    int TPC;
    if (IDEX.CW.branch && BranchFlag)
    {
        TPC = IDEX.DPC + IDEX.imm;
    }
    else if (IDEX.CW.jump)
    {
        TPC = IDEX.DPC + IDEX.imm;
    }
    else if (IDEX.CW.jumpr)
    {
        TPC = ALUResult;
    }
    else
    {
        TPC = IDEX.DPC + 4;
    }

    flush = (TPC != (IDEX.DPC + 4));

    int new_rs2 = MUX(select2,
                      rs2,
                      EXMO.ALUResult,
                      MOWB.LDResult,
                      MOWB.ALUResult);

    EXMO = PipeLineReg4(
        TPC,
        IDEX.DPC + 4,
        ALUResult,
        new_rs2,
        IDEX.rdl,
        IDEX.CW);

    IDEX = PipeLineReg3();
}

// ========================== MEMORY ==========================

void MemoryOperation(PipeLineReg4 &EXMO,
                     PipeLineReg5 &MOWB)
{
    int LDResult = 0;

    if (EXMO.CW.memRead)
    {
        LDResult = MemoryBlock::memRead(EXMO.ALUResult);
    }

    if (EXMO.CW.memWrite)
    {
        MemoryBlock::memWrite(EXMO.ALUResult, EXMO.rs2);
    }

    MOWB = PipeLineReg5(
        EXMO.TPC,
        EXMO.NPC,
        EXMO.ALUResult,
        LDResult,
        EXMO.rdl,
        EXMO.CW);

    EXMO = PipeLineReg4();
}

// ========================== WRITE BACK ==========================

void WriteBack(PipeLineReg5 &MOWB,
               PipeLineReg1 &IM,
               int NPC)
{
    if (MOWB.CW.regWrite)
    {
        int select = 2 * (MOWB.CW.jump || MOWB.CW.jumpr) + MOWB.CW.memToReg;

        RegisterFetch::regWrite(
            MOWB.rdl,
            MUX(select,
                MOWB.ALUResult,
                MOWB.LDResult,
                MOWB.NPC));
    }

    if (!IM.stall)
    {
        IM = PipeLineReg1(NPC);
    }

    MOWB = PipeLineReg5();
}
