#ifndef COMPILER_EXPINFO_H
#define COMPILER_EXPINFO_H

struct ExpInfo {
    bool is_const;
    bool is_array;
    int array_size;
    Token::TokenType type;

    ExpInfo(bool is_const, bool is_array, int array_size, Token::TokenType type)
        : is_const(is_const), is_array(is_array), array_size(array_size), type(type) {}
};

#endif //COMPILER_EXPINFO_H
