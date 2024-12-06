#ifndef MIPS_INSTR_H
#define MIPS_INSTR_H
#include "mips_reg.h"

enum OpType {
    Addu,
    Addi, Addiu,
    Subu, // R type or pseudo instruction
    Mul, Div,
    Rem, // pesudo instruction
    Sll, Srl,
    Slt, Slti,
    Sle, // pseudo instruction
    Seq, Sne,
    Sgt, Sge,
    Sw, Lw,
    Li, La,
    Beq,
    J, Jal, Jr,
    Label,
    Syscall
};

std::string transfer_op_to_string(OpType op);

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
    MipsReg* rs;
    MipsReg* rt;
    MipsReg* rd;
    int imm;
    std::string label = "";
    // syscall
    NonTypeInstr(OpType op) : MipsInstr(op) {}
    // li
    NonTypeInstr(OpType op, MipsReg* rt, int imm)
    : MipsInstr(op), rt(rt), imm(imm) {}
    // la
    NonTypeInstr(OpType op, MipsReg* rt, MipsReg* rs, std::string label)
    : MipsInstr(op), rt(rt), rs(rs), label(label) {}
    // rem,sle seq sne sgt sge(1,2) subu(2) la(2) Mul(2)
    NonTypeInstr(OpType op, MipsReg* rd, MipsReg* rs, MipsReg* rt)
    : MipsInstr(op), rd(rd), rs(rs), rt(rt) {}
    NonTypeInstr(OpType op, MipsReg* rs, MipsReg* rt, int imm)
    : MipsInstr(op), rs(rs), rt(rt), imm(imm), rd(nullptr) {}
    void print(std::ostream &os) const override;
};

#endif // MIPS_INSTR_H