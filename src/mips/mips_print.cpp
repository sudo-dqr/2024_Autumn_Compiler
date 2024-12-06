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
    case Addu:
        op_str = "addu";
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
    case Jr:
        op_str = "jr";
        break;  
    case Slt:
        op_str = "slt";
        break;
    default:
        std::cout << "Undefined RTypeInstr!" << std::endl;
        break;
    }
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
    std::string op_str;
    switch (op) {
        case Addi:
            op_str = "addi";
            break;
        case Addiu:
            op_str = "addiu";
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
        case Slti:
            op_str = "slti";
            break;
        default:
            std::cout << "Undefined ITypeInstr!" << std::endl;
            break;
    }
    os << op_str << " ";
    if (op == Sw || op == Lw) {
        rs->printReg(os);
        os << ", ";
        os << imm << "(";
        rt->printReg(os);
        os << ")";
    } else if (op == Beq) {
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
            os << ", " << imm;    
            break;
        case Rem:
            os << "rem ";
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
        case Sle:
            os << "sle ";
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
        case Seq:
            os << "seq ";
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
        case Sne:
            os << "sne ";
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
        case Sge:
            os << "sge ";
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
        case Sgt:
            os << "sgt ";
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
            os << "subu ";
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