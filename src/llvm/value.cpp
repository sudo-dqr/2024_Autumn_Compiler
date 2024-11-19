#include "value.h"
#include "type.h"
#include "instr.h"

void GlobalVariable::print(std::ostream &os) const {
    if (auto int_type = dynamic_cast<IntType*>(type)) {
        os << "@" << name << " = dso_local global ";
        type->print(os);
        os << " ";
        os << int_value;
    } else if (auto char_type = dynamic_cast<CharType*>(type)) {
        os << "@" << name << " = dso_local global ";
        type->print(os);
        os << " ";
        os << char_value;
    } else if (auto array_type = dynamic_cast<ArrayType*>(type)) {
        if (array_type->element_type == &IR_INT
            && int_array_init_values.size() == 0) {
                os << "@" << name << " = dso_local global ";
                type->print(os);
                os << " ";
                os << "zeroinitializer";
        } else if (array_type->element_type == &IR_CHAR
            && char_array_init_values.size() == 0 && char_array_init_string.length() == 0) {
                os << "@" << name << " = dso_local global ";
                type->print(os);
                os << " ";
                os << "zeroinitializer";
        } else if (char_array_init_string.length() != 0) { // string const
        os << "@" << name << " = private unnamed_addr constant ";
            type->print(os);
            os << " c\"" << char_array_init_string << "\\00\"";
        } else {
            os << "@" << name << " = dso_local global ";
            type->print(os);
            os << " ";
            os << "[";
            auto element_type = array_type->element_type;
            if (auto int_type = dynamic_cast<IntType*>(element_type)) {
                for (int i = 0; i < int_array_init_values.size(); i++) {
                    os << "i32 " << int_array_init_values[i];
                    if (i != int_array_init_values.size() - 1) os << ", ";
                }
            } else if (auto char_type = dynamic_cast<CharType*>(element_type)) {
                for (int i = 0; i < char_array_init_values.size(); i++) {
                    os << "i8 " << char_array_init_values[i];
                    if (i != char_array_init_values.size() - 1) os << ", ";
                }
            }
            os << "]";
        }
    } else std::cout << "GlobalVariable type not supported" << std::endl;
}

void FParam::print(std::ostream &os) const {
    type->print(os);
    os << " %" << id;
}

void BasicBlock::print(std::ostream &os) const {
    if (instrs.empty()) return;
    for (auto &instr : instrs) {
        instr->print(os);
        os << std::endl;
    }
}

void Function::print(std::ostream &os) const {
    os << "define dso_local ";
    ((FunctionType*)type)->return_type->print(os);
    os << " @" << name << "(";
    for (int i = 0; i < fparams.size(); i++) {
        fparams[i]->print(os);
        if (i != fparams.size() - 1) {
            os << ", ";
        }
    }
    os << ") {\n";
    for (auto &basic_block : basic_blocks) {
        basic_block->print(os);
    }
    os << "}\n";
}

void Module::print(std::ostream &os) const {
    os << "declare i32 @getchar()\n"
       << "declare i32 @getint()\n"
       << "declare void @putint(i32)\n"
       << "declare void @putch(i32)\n"
       << "declare void @putstr(i8*)\n";
       os << std::endl;
    for (auto &global_variable : global_variables) {
        global_variable->print(os);
        os << std::endl;
    }
    os << std::endl;
    for (auto &function : functions) {
        function->print(os);
        os << std::endl;
        os << std::endl;
    }
}

void Value::print(std::ostream &os) const {
    os << "<Abstract Value to string not supported>";
}

void User::print(std::ostream &os) const {
    os << "<Abstract User to string not supported>";
}

void IntConst::print(std::ostream &os) const {
    os << this->value;
}

void CharConst::print(std::ostream &os) const {
    os << this->value;
}