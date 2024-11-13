#ifndef COMPILER_EXPINFO_H
#define COMPILER_EXPINFO_H
#include "token.h"
#include "value.h"

struct ExpInfo {
    bool is_const;
    bool is_array;
    bool is_bool; // i1 type
    int array_size;
    Token::TokenType type;
    int value;
    std::unique_ptr<Value> ir_value;

    ExpInfo(bool is_const, bool is_array, int array_size, Token::TokenType type)
        : is_const(is_const), is_array(is_array), array_size(array_size), type(type) {}
};

#endif //COMPILER_EXPINFO_H
