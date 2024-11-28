#ifndef MIPS_INSTR_H
#define MIPS_INSTR_H
#include "mips_reg.h"

enum OpType {
    Add, Addu,
    Sub, Subu,
    Mul, Div,
    Sll, Srl,
    And, Or,
    Sw, Lw,
    Sb, Lb,
    Li, La,
    Beq, Bne,
    Bgt, Blt,
    Bge, Ble,
    J, Jal,
    Jr, Jalr,
    Label
};

struct MipsInstr {
    OpType op;

    MipsInstr(OpType op) : op(op) {}
    virtual void print(std::ostream &os) const = 0;
};

// R type is like
// | op | rs | rt | rd | shamt | funct |
struct RTypeInstr : public MipsInstr {
    MipsReg* rd;
    MipsReg* rs;
    MipsReg* rt;
    int shamt;
    RTypeInstr(OpType op, MipsReg* rs, MipsReg*rt, MipsReg* rd) 
    : MipsInstr(op), rd(rd), rs(rs), rt(rt), shamt(0) {}

    void print(std::ostream &os) const override;
};

// I type is like
// | op | rs | rt | imm(16) |
struct ITypeInstr : public MipsInstr{
    MipsReg* rt;
    MipsReg* rs;
    int imm;
    ITypeInstr(OpType op, MipsReg* rs, MipsReg* rt, int imm)
    : MipsInstr(op), rt(rt), rs(rs), imm(imm) {}

    void print(std::ostream &os) const override;
};

// J type is like
// | op | imm(26) |
struct JTypeInstr : public MipsInstr{
    int imm;
    JTypeInstr(OpType op, int imm)
    : MipsInstr(op), imm(imm) {}

    void print(std::ostream &os) const override;
};


struct MipsLabel : public MipsInstr {
    std::string label;
    MipsLabel(std::string label) : MipsInstr(Label), label(label) {}

    void print(std::ostream &os) const override;
};

#endif // MIPS_INSTR_H