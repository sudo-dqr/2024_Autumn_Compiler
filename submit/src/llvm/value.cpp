#include "value.h"
#include "type.h"
#include "instr.h"

void GlobalVariable::print(std::ostream &os) const {
    // 当前global variable的type是一个指针类型
    auto deref_type = ((PointerType*)this->type)->referenced_type;
    if (is_printf_str) {
        os << "@" << name << " = private unnamed_addr constant ";
        deref_type->print(os);
        os << " c\"" << array_string << "\\00\"";
    } else {
        os << "@" << name << " = dso_local global ";
        deref_type->print(os);
        os << " ";
        if (auto int_type = dynamic_cast<IntType*>(deref_type)) {
            os << value;
        } else if (auto char_type = dynamic_cast<CharType*>(deref_type)) {
            os << value;
        } else if (auto array_type = dynamic_cast<ArrayType*>(deref_type)) {
            if (array_values.size() == 0 && array_string.length() == 0) {
                os << "zeroinitializer";
            } else if (array_string.length() != 0) { // string const
                os << "c\"" << array_string;
                int array_size = array_type->size;
                for (int i = char_cnt; i <= array_size; i++) 
                    os << "\\00";
                os << "\"";
            } else {
                os << "[";
                auto element_type = array_type->element_type;
                if (auto int_type = dynamic_cast<IntType*>(element_type)) {
                    for (int i = 0; i < array_values.size(); i++) {
                        os << "i32 " << array_values[i];
                        if (i != array_values.size() - 1) os << ", ";
                    }
                } else if (auto char_type = dynamic_cast<CharType*>(element_type)) {
                    for (int i = 0; i < array_values.size(); i++) {
                        os << "i8 " << array_values[i];
                        if (i != array_values.size() - 1) os << ", ";
                    }
                }
                os << "]";
            }
        } else std::cout << "GlobalVariable Print : Not Supported Type of GlobalVariable" << std::endl;
    }
}

void FParam::print(std::ostream &os) const {
    type->print(os);
    os << " %" << id;
}

void BasicBlock::print(std::ostream &os) const {
    // if (instrs.empty()) return;
    os << id << ":\n";
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
    }
}

void Value::print(std::ostream &os) const {
    os << "<Abstract Value to string not supported>";
}

void User::print(std::ostream &os) const {
    os << "<Abstract User to string not supported>";
}

void IntConst::print(std::ostream &os) const {
    os << value;
}

void CharConst::print(std::ostream &os) const {
    os << value;
}