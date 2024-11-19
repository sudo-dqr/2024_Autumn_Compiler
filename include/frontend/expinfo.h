#ifndef COMPILER_EXPINFO_H
#define COMPILER_EXPINFO_H
#include "token.h"
#include "value.h"

struct ExpInfo {
    bool is_const;
    bool is_array;
    bool is_bool; // i1 type
    Token::TokenType type;
    int int_value;
    char char_value;
    Value* ir_value;

    ExpInfo() = default;
    ExpInfo(bool is_bool, bool is_array, Token::TokenType type, Value* ir_value) {
        this->is_const = false;
        this->is_bool = is_bool;
        this->is_array = is_array;
        this->type = type;
        this->ir_value = ir_value;
    }

    ExpInfo(bool is_bool, bool is_array, int int_value, Token::TokenType type) {
        this->is_const = true;
        this->is_bool = is_bool;
        this->is_array = is_array;
        this->int_value = int_value;
        this->type = type;
        this->ir_value = new IntConst(int_value);
    }

    ExpInfo(bool is_bool, bool is_array, Value* ir_value) {
        this->is_const = false;
        this->is_bool = false;
        this->is_array = is_array;
        this->type = Token::END;
        this->ir_value = ir_value;
    }
};

#endif //COMPILER_EXPINFO_H
