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
    std::string op_str;
    switch (op) {
    case Add:
        op_str = "add";
        break;
    case Addu:
        op_str = "addu";
        break;
    case Sub:
        op_str = "sub";
        break;
    case Subu:
        op_str = "subu";
        break;
    case Mul:
        op_str = "mul";
        break;
    case Div:
        op_str = "div";
        break;
    case Sll:
        op_str = "sll";
        break;
    case Srl:
        op_str = "srl";
        break;
    case And:
        op_str = "and";
        break;
    case Or:
        op_str = "or";
        break;
    case Jr:
        op_str = "jr";
        break;  
    case Slt:
        op_str = "slt";
        break;
    case Sle:
        op_str = "sle";
        break;
    case Seq:
        op_str = "seq";
        break;
    case Sne:
        op_str = "sne";
        break;
    case Sgt:
        op_str = "sgt";
        break;
    case Sge:
        op_str = "sge";
        break;
    default:
        break;
    }
    os << op_str << " ";
    if (op != Jr) {
        rs->printReg(os);
        os << ", ";
        rt->printReg(os);
        os << ", ";
        if (op == Sll || op == Srl) {
            os << shamt;
        } else {
            rd->printReg(os);
        }
    } else {
        rs->printReg(os);
    }
}

void ITypeInstr::print(std::ostream &os) const {
    MipsInstr::print(os);
    std::string op_str;
    switch (op) {
        case Addi:
            op_str = "addi";
            break;
        case Sw:
            op_str = "sw";
            break;
        case Lw:
            op_str = "lw";
            break;
        case Beq:
            op_str = "beq";
            break;
        case Bne:
            op_str = "bne";
            break;
        case Bgt:
            op_str = "bgt";
            break;
        case Blt:
            op_str = "blt";
            break;
        case Bge:
            op_str = "bge";
            break;
        case Ble:
            op_str = "ble";
            break;
        case Andi:
            op_str = "andi";
            break;
        case Ori:
            op_str = "ori";
            break;
        default:
            break;
    }
    os << op_str << " ";
    if (op == Sw || op == Lw) {
        rs->printReg(os);
        os << ", ";
        os << imm << "(";
        rt->printReg(os);
        os << ")";
    } else if (op == Beq || op == Bne || op == Bgt || op == Blt || op == Bge || op == Ble) {
        rs->printReg(os);
        os << ", ";
        rt->printReg(os);
        os << ", " << label;
    } else {
        rs->printReg(os);
        os << ", ";
        rt->printReg(os);
        os << ", " << imm;
    }
}

void JTypeInstr::print(std::ostream &os) const {
    MipsInstr::print(os);
    if (op == J) {
        os << "j " << label;
    } else if (op == Jal) {
        os << "jal " << label;
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
            os << ", " << imm;    
            break;
        default:
            break;
    }
}