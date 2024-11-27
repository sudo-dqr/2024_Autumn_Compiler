#ifdef MIPS_INSTR_H
#define MIPS_INSTR_H

enum OpType {

};

struct MipsInstr {
    OpType op;
    MipsReg* rd; // 5
    MipsReg* rs; // 5
    MipsReg* rt; // 5
    int imm; // 16
    int shamt; // 5

    MipsInstr(OpType op, MipsReg* rd, MipsReg* rs, MipsReg* rt, int imm, int shamt) 
    : op(op), rd(rd), rs(rs), rt(rt), imm(imm), shamt(shamt) {}
    virtual void print(std::ostream &os) const = 0;
};

struct RTypeInstr : public MipsInstr {
    RTypeInstr(OpType op, MipsReg* rd, MipsReg*rs, MipsReg* rt) 
    : MipsInstr(op, rd, rs, rt, 0, 0) {}

    void print(std::ostream &os) const override;
};

struct ITypeInstr : public MipsInstr{
    ITypeInstr(OpType op, MipsReg* rd, MipsReg* rs, int imm)
    : MipsInstr(op, rd, rs, nullptr, imm, 0) {}

    void print(std::ostream &os) const override;
};

struct JTypeInstr : public MipsInstr{
    JTypeInstr(OpType op, int imm)
    : MipsInstr(op, nullptr, nullptr, nullptr, imm, 0) {}

    void print(std::ostream &os) const override;
};

#endif // MIPS_INSTR_H