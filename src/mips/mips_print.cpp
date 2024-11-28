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
}

void ITypeInstr::print(std::ostream &os) const {
    MipsInstr::print(os);
}

void JTypeInstr::print(std::ostream &os) const {
    MipsInstr::print(os);
}

void MipsLabel::print(std::ostream &os) const {
    os << label << ":";
}