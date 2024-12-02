#ifndef MIPS_INSTR_H
#define MIPS_INSTR_H
#include "mips_reg.h"

enum OpType {
    Add, Addu, Addi,
    Sub, Subu,
    Mul, Div,
    Sll, Srl,
    Slt, Sle,
    Seq, Sne,
    Sgt, Sge,
    And, Or,
    Andi, Ori,
    Sw, Lw,
    Li, La,
    Beq, Bne,
    Bgt, Blt,
    Bge, Ble,
    J, Jal, Jr,
    Label,
    Syscall
};

struct MipsInstr {
    OpType op;

    MipsInstr(OpType op) : op(op) {}
    virtual void print(std::ostream &os) const = 0;
};

// R type is like
// | op | rs | rt | rd | shamt | funct |
// Instrs: add, addu, sub, subu, mul, div, sll, srl, and, or, jr
struct RTypeInstr : public MipsInstr {
    MipsReg* rd;
    MipsReg* rs;
    MipsReg* rt;
    int shamt;
    RTypeInstr(OpType op, MipsReg* rd, MipsReg*rs, MipsReg* rt) 
    : MipsInstr(op), rd(rd), rs(rs), rt(rt), shamt(0) {}
    RTypeInstr(OpType op, MipsReg* rd, MipsReg* rt, int shamt)
    : MipsInstr(op), rd(rd), rt(rt), shamt(shamt) {}
    RTypeInstr(OpType op, MipsReg* rs)
    : MipsInstr(op), rs(rs) {}

    void print(std::ostream &os) const override;
};

// I type is like
// | op | rs | rt | imm(16) |
// Instrs: addi, sw, lw, beq, bne, bgt, blt, bge, ble, andi, ori
struct ITypeInstr : public MipsInstr{
    MipsReg* rt;
    MipsReg* rs;
    int imm;
    std::string label;
    ITypeInstr(OpType op, MipsReg* rs, MipsReg* rt, int imm)
    : MipsInstr(op), rt(rt), rs(rs), imm(imm) {}
    ITypeInstr(OpType op, MipsReg* rs, MipsReg* rt, std::string label)
    : MipsInstr(op), rt(rt), rs(rs), label(label) {}
    void print(std::ostream &os) const override;
};

// J type is like
// | op | imm(26) |
// Instrs: j, jal
struct JTypeInstr : public MipsInstr{
    std::string label;
    JTypeInstr(OpType op, std::string label) : MipsInstr(op), label(label) {}

    void print(std::ostream &os) const override;
};


struct MipsLabel : public MipsInstr {
    std::string label;
    MipsLabel(std::string label) : MipsInstr(Label), label(label) {}

    void print(std::ostream &os) const override;
};

struct NonTypeInstr : public MipsInstr {
    MipsReg* rt;
    int imm;
    std::string label;
    // syscall
    NonTypeInstr(OpType op) : MipsInstr(op) {}
    // li
    NonTypeInstr(OpType op, MipsReg* rt, int imm)
    : MipsInstr(op), rt(rt), imm(imm) {}
    // la
    NonTypeInstr(OpType op, MipsReg* rt, std::string label)
    : MipsInstr(op), rt(rt), label(label) {}
    void print(std::ostream &os) const override;
};

#endif // MIPS_INSTR_H