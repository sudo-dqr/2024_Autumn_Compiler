#include <ostream>
#include "mips_data.h"
#include "mips_instr.h"


void MipsData::print(std::ostream &os) const {
    os << "\t";
}

void WordData::print(std::ostream &os) const {
    MipsData::print(os);
    os << name << ": .word ";
    if (array_values.size() == 0 && !is_array) {
        os << value;
    } else if (array_values.size() == 0 && is_array) {
        os << "0:" << value;
    } else {
        for (int i = 0; i < array_values.size(); i++) {
            os << array_values[i];
            if (i != array_values.size() - 1) os << ", ";
        }
    }
}

void ByteData::print(std::ostream &os) const {
    MipsData::print(os);
    os << name << ": .byte ";
    if (array_values.size() == 0 && !is_array) {
        os << value;
    } else if (array_values.size() == 0 && is_array) {
        os << "0:" << value;
    } else {
        for (int i = 0; i < array_values.size(); i++) {
            os << array_values[i];
            if (i != array_values.size() - 1) os << ", ";
        }
    }
}

void AsciizData::print(std::ostream &os) const {
    MipsData::print(os);
    os << name << ": .asciiz \"" << value << "\"";
}

void MipsInstr::print(std::ostream &os) const {
    os << "\t";
}

void RTypeInstr::print(std::ostream &os) const {
    MipsInstr::print(os);
    std::string op_str = transfer_op_to_string(op);
    os << op_str << " ";
    if (op != Jr) {
        rd->printReg(os);
        os << ", ";
        rs->printReg(os);
        os << ", ";
        if (op == Sll || op == Srl) {
            os << shamt;
        } else {
            rt->printReg(os);
        }
    } else {
        rs->printReg(os);
    }
}

void ITypeInstr::print(std::ostream &os) const {
    MipsInstr::print(os);
    std::string op_str = transfer_op_to_string(op);
    os << op_str << " ";
    if (op == Sw || op == Lw || op == Sb || op == Lbu) {
        if (label != "") {
            rt->printReg(os);
            os << ", " << label;
            os << "(";
            rs->printReg(os);
            os << ")";
        } else {
            rt->printReg(os);
            os << ", " << imm;
            os << "(";
            rs->printReg(os);
            os << ")";
        }
    } else if (op == Beq) {
        rt->printReg(os);
        os << ", ";
        rs->printReg(os);
        os << ", " << label;
    } else {
        rt->printReg(os);
        os << ", ";
        rs->printReg(os);
        os << ", " << imm;
    }
}

void JTypeInstr::print(std::ostream &os) const {
    MipsInstr::print(os);
    if (op == J) {
        os << "j " << label;
    } else if (op == Jal) {
        os << "jal " << label;
    } else {
        std::cout << "Undefined JTypeInstr!" << std::endl;
    }
}

void MipsLabel::print(std::ostream &os) const {
    os << label << ":";
}

void NonTypeInstr::print(std::ostream &os) const {
    MipsInstr::print(os);
    switch (op) {
        case Syscall:
            os << "syscall";
            break;
        case Li:
            os << "li ";
            rt->printReg(os);
            os << ", " << imm;
            break;
        case La:
            os << "la ";
            rt->printReg(os);
            if (label != "") {
                os << ", " << label;
                os << "(";
                rs->printReg(os);
                os << ")";
            } else {
                os << ", " << imm;
                os << "(";
                rs->printReg(os);
                os << ")";
            }
            break;
        case Rem:
        case Sle:
        case Seq:
        case Sne:
        case Sge:
        case Sgt:
            os << transfer_op_to_string(op) << " ";
            if (rd) {
                rd->printReg(os);
                os << ", ";
                rs->printReg(os);
                os << ", ";
                rt->printReg(os);
            } else {
                rt->printReg(os);
                os << ", ";
                rs->printReg(os);
                os << ", " << imm;
            }
            break;
        case Subu:
        case Mul:
            os << transfer_op_to_string(op) << " ";
            rt->printReg(os);
            os << ", ";
            rs->printReg(os);
            os << ", " << imm;
            break;
        default:
            std::cout << "Undefined NonTypeInstr!" << std::endl;
            break;
    }
}

std::string transfer_op_to_string(OpType op) {
    switch (op) {
        case Addu: return "addu"; break;
        case Addi: return "addi"; break;
        case Addiu: return "addiu"; break;
        case Subu: return "subu"; break;
        case Mul: return "mul"; break;
        case Div: return "div"; break;
        case Rem: return "rem"; break;
        case Sll: return "sll"; break;
        case Srl: return "srl"; break;
        case Slt: return "slt"; break;
        case Slti: return "slti"; break;
        case Sle: return "sle"; break;
        case Seq: return "seq"; break;
        case Sne: return "sne"; break;
        case Sgt: return "sgt"; break;
        case Sge: return "sge"; break;
        case Sw: return "sw"; break;
        case Lw: return "lw"; break;
        case Sb: return "sb"; break;
        case Lbu: return "lbu"; break;
        case Li: return "li"; break;
        case La: return "la"; break;
        case Beq: return "beq"; break;
        case J: return "j"; break;
        case Jal: return "jal"; break;
        case Jr: return "jr"; break;
        case Label: return "label"; break;
        case Syscall: return "syscall"; break;
        default: return "Undefined MIPS Instr"; break;
    }
}