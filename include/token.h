#ifndef TOKEN_H
#define TOKEN_H
#include <string>

class Token {

    public:
        enum TokenType {
            IDENFR, INTCON, STRCON, CHRCON, MAINTK, CONSTTK, INTTK, CHARTK, BREAKTK, CONTINUETK,
            IFTK, ELSETK, NOT, AND, OR, FORTK, GETINTTK, GETCHARTK, PRINTFTK, RETURNTK, PLUS, MINU,
            VOIDTK, MULT, DIV, MOD, LSS, LEQ, GRE, GEQ, EQL, NEQ, ASSIGN, SEMICN, COMMA, 
            LPARENT, RPARENT, LBRACK, RBRACK, LBRACE, RBRACE, COUNT // 变体数量;
        };

        enum ReserveWord {
            MAINTK, CONSTTK, INTTK, CHARTK, BREAKTK, CONTINUETK,IFTK, 
            ELSETK, FORTK, GETINTTK, GETCHARTK, PRINTFTK, RETURNTK, VOIDTK,
            COUNT
        };

    private:
        std::string token;
        TokenType type;
        int line_number;

    public:
        Token(std::string token, TokenType type, int line_number);
        ~Token();
        std::string get_token();
        TokenType get_type();
        int get_line_number();

};


#endif