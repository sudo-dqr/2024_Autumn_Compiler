#include "mips_utils.h"

int ir_type_size(ValueType* ir_type) {
    if (auto int_type = dynamic_cast<IntType*>(ir_type)) {
        return 4;
    } else if (auto char_type = dynamic_cast<CharType*>(ir_type)) {
        return 1;
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

int get_const_value(Value* value) {
    if (auto intconst_ptr = dynamic_cast<IntConst*>(value)) {
        return intconst_ptr->value;
    } else if (auto charconst_ptr = dynamic_cast<CharConst*>(value)) {
        return charconst_ptr->value;
    } else {
        std::cout << "Get Const Value : Invalid Value!" << std::endl;
        return -1;
    }
}

MipsReg* parse_id_to_reg(int id) {
    if (id == 0) return new ZeroReg();
    else if (id == 1) return new AtReg();
    else if (id >= 2 && id <= 3) return new RetValReg(id - 2);
    else if (id >= 4 && id <= 7) return new ArgReg(id - 4);
    else if (id >= 8 && id <= 15) return new TempReg(id - 8);
    else if (id >= 16 && id <= 24) return new SavedReg(id - 16);
    else {
        std::cout << "Invalid Register ID!" << std::endl;
        return nullptr;
    }
}

int parse_reg_to_id(MipsReg* reg) {
    if (auto zero_reg = dynamic_cast<ZeroReg*>(reg)) return 0;
    else if (auto at_reg = dynamic_cast<AtReg*>(reg)) return 1;
    else if (auto retval_reg = dynamic_cast<RetValReg*>(reg)) return retval_reg->index + 2;
    else if (auto arg_reg = dynamic_cast<ArgReg*>(reg)) return arg_reg->index + 4;
    else if (auto temp_reg = dynamic_cast<TempReg*>(reg)) return temp_reg->index + 8;
    else if (auto saved_reg = dynamic_cast<SavedReg*>(reg)) return saved_reg->index + 16;
    else {
        std::cout << "Invalid Register!" << std::endl;
        return -1;
    }
}