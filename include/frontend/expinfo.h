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
    ExpInfo(bool is_bool, bool is_array, int int_value, Token::TokenType type) 
    : is_bool(is_bool), is_array(is_array), type(type), int_value(int_value), char_value(0), ir_value(nullptr) {}
    ExpInfo(bool is_bool, bool is_array, char char_value, Token::TokenType type)
    : is_bool(is_bool), is_array(is_array), type(type), int_value(0), char_value(char_value), ir_value(nullptr) {}
};

#endif //COMPILER_EXPINFO_H
