#ifndef MIPS_UTILS_H
#define MIPS_UTILS_H

int ir_type_size(ValueType* ir_type) {
    if (auto int_type = dynamic_cast<IntType*>(ir_type)) {
        return 4;
    } else if (auto char_type = dynamic_cast<CharType*>(ir_type)) {
        return 4;
    } else if (auto array_type = dynamic_cast<ArrayType*>(ir_type)) {
        return array_type->size * ir_type_size(array_type->element_type);
    } else if (auto pointer_type = dynamic_cast<PointerType*>(ir_type)) {
        return 4;
    } else {
        std::cout << "MIPS Alloca : Invalid Type!" << std::endl;
        return 0;
    }
}

bool is_const_value(Value* value) {
    if (auto intconst_ptr = dynamic_cast<IntConst*>(value)) {
        return true;
    } else if (auto charconst_ptr = dynamic_cast<CharConst*>(value)) {
        return true;
    } else {
        return false;
    }
}

#endif // MIPS_UTILS_H