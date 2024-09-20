#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include "multi_line_comment_fsm.h"
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
        Token::TokenType token_type;
        int line_number;
        int token_number;
        std::unordered_map <std::string, Token::TokenType> reserve_words;
        std::vector <Error> errors;  // 保存a类错误

    public:
        Lexer(std::string source);
        ~Lexer();
        Token next();
        void run();

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