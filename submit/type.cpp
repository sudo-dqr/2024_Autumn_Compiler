#include "type.h"
//! print methods for IR Types

void ArrayType::print(std::ostream &os) const {
    os << '[' << this->size << " x ";
    this->element_type->print(os);
    os << ']'; 
}

void FunctionType::print(std::ostream &os) const {

}

void IntType::print(std::ostream &os) const {
    if (this->is_logical) {
        os << "i1";
    } else {
        os << "i32";
    }
}

void CharType::print(std::ostream &os) const {
    os << "i8";
}

void LabelType::print(std::ostream &os) const {

}

void PointerType::print(std::ostream &os) const {
    this->referenced_type->print(os);
    os << '*';
}

void VoidType::print(std::ostream &os) const {
    os << "void";
}