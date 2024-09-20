#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include "multi_line_comment_fsm.h"
#include "error.h"
#include <string>
#include <vector>
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

    private:
        Token::TokenType transfer_type(Token::ReserveWord type);
        Token intcon();
        Token idenfr();
        Token strcon();
        Token chrcon();
        void skip_single_line_comment();
        void skip_multi_line_comment();

    private:
        std::string type_to_string(Token::ReserveWord type);     
};


#endif