#ifndef MIPS_UTILS_H
#define MIPS_UTILS_H
#include "type.h"
#include "value.h"

int ir_type_size(ValueType* ir_type);

bool is_const_value(Value* value);

int get_const_value(Value* value);

#endif // MIPS_UTILS_H