#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include <string>
#include <unordered_map>

class Lexer {

    private:
        std::string source;
        int pos;
        Token::TokenType token_type;
        int line_number;
        int token_number;
        std::unordered_map <std::string, Token::TokenType> reserve_words;

    public:
        Lexer(std::string source);
        ~Lexer();
        Token next();

    private:
        Token::TokenType transfer_type(Token::ReserveWord type);
        Token intcon();
        Token idenfr();

    private:
        std::string type_to_string(Token::ReserveWord type);     
};


#endif