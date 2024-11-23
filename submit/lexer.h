#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include "error.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>

class Lexer {

    private:
        std::string source;
        int pos;
        int line_number;
        std::unordered_map <std::string, Token::TokenType> reserve_words;

    public:
        Lexer(std::string source);
        ~Lexer();
        Token next();
        bool has_next();

    private:
        Token intcon();
        Token idenfr();
        Token strcon();
        Token chrcon();
        void skip_single_line_comment();
        void skip_multi_line_comment();
        void initialize_reverse_word_map();    
};


#endif