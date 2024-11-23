#ifndef COMPILER_EXPINFO_H
#define COMPILER_EXPINFO_H
#include "token.h"
#include "value.h"

struct ExpInfo {
    bool is_const; // 表示是不是一个常量, 不是指是不是使用const修饰的
    bool is_array;
    bool is_bool; // i1 type
    Token::TokenType type; // int/char
    int value;
    Value* ir_value;

    ExpInfo() = default;

    ExpInfo(bool is_bool, bool is_array, int value, Token::TokenType type) {
        this->is_const = true;
        this->is_bool = is_bool;
        this->is_array = is_array;
        this->value = value;
        this->type = type;
        if (type == Token::INTTK)
            this->ir_value = new IntConst(value);
        else
            this->ir_value = new CharConst(value);
    }

    ExpInfo(bool is_bool, bool is_array, Value* ir_value) {
        this->is_const = false;
        this->is_bool = is_bool;
        this->is_array = is_array;
        this->type = Token::END; //! attention
        this->ir_value = ir_value;
    }
};

#endif //COMPILER_EXPINFO_H
