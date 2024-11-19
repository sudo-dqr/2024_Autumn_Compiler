#include "value.h"
#include "type.h"
#include "instr.h"

void GlobalVariable::print(std::ostream &os) const {
    os << "@" << name << " = dso_local global ";
    type->print(os);
    os << " ";
    if (auto int_type = dynamic_cast<IntType*>(type)) {
        os << int_value;
    } else if (auto char_type = dynamic_cast<CharType*>(type)) {
        os << char_value;
    } else if (auto array_type = dynamic_cast<ArrayType*>(type)) {
        if (int_array_init_values.size() == 0) {
            os << "zeroinitializer";
        } else {
            os << "[";
            auto element_type = array_type->get_element_type();
            for (int i = 0; i < int_array_init_values.size(); i++) {
                element_type->print(os);
                os << int_array_init_values[i];
                if (i != int_array_init_values.size() - 1) {
                    os << ", ";
                }
            }
            os << "]";
        }
    }
}

void FParam::print(std::ostream &os) const {
    type->print(os);
    os << " %" << id;
}

void BasicBlock::print(std::ostream &os) const {
    if (instrs.empty()) return;
    for (auto &instr : instrs) {
        instr->print(os);
        os << "\n";
    }
}

void Function::print(std::ostream &os) const {
    os << "define dso_local ";
    type->print(os);
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