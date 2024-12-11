#ifndef MIPS_UTILS_H
#define MIPS_UTILS_H
#include "type.h"
#include "value.h"
#include "mips_reg.h"

int ir_type_size(ValueType* ir_type);

bool is_const_value(Value* value);

int get_const_value(Value* value);

MipsReg* parse_id_to_reg(int id);

int parse_reg_to_id(MipsReg* reg);

#endif // MIPS_UTILS_H