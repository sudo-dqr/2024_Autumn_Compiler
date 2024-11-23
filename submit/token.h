#ifndef TOKEN_H
#define TOKEN_H
#include <string>

class Token {

    public:
        enum TokenType {
            IDENFR, INTCON, STRCON, CHRCON, MAINTK, CONSTTK, INTTK, CHARTK, BREAKTK, CONTINUETK,
            IFTK, ELSETK, NOT, AND, OR, FORTK, GETINTTK, GETCHARTK, PRINTFTK, RETURNTK, PLUS, MINU,
            VOIDTK, MULT, DIV, MOD, LSS, LEQ, GRE, GEQ, EQL, NEQ, ASSIGN, SEMICN, COMMA, 
            LPARENT, RPARENT, LBRACK, RBRACK, LBRACE, RBRACE, END
        };

    private:
        std::string token;
        TokenType type;
        int line_number;

    public:
        Token(std::string token, TokenType type, int line_number);
        ~Token();
        int get_int();
        char get_char();
        std::string get_token();
        TokenType get_type();
        int get_line_number();
        std::string to_string();
        char get_escape_char(const std::string &str);

};


#endif