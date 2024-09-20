#include "lexer.h"

Lexer::Lexer(std::string source) {
    this->source = source;
    this->line_number = 0;
    this->pos = 0;
    for(int i = 0; i < static_cast<int>(Token::Token::ReserveWord::COUNT); i++) {
        Token::Token::ReserveWord type = static_cast<Token::Token::ReserveWord>(i);
        std::string type_string = type_to_string(type);
        this->reserve_words.insert({type_string, type});
    }
}

std::string Lexer::type_to_string(Token::ReserveWord type) {
    switch (type)
    {
    case Token::ReserveWord::MAINTK: return "main"; break;
    case Token::ReserveWord::CONSTTK: return "const"; break;
    case Token::ReserveWord::INTTK: return "int"; break;
    case Token::ReserveWord::CHARTK: return "char"; break;
    case Token::ReserveWord::BREAKTK: return "braek"; break;
    case Token::ReserveWord::CONTINUETK: return "continue"; break;
    case Token::ReserveWord::IFTK: return "if"; break;
    case Token::ReserveWord::ELSETK: return "else"; break;
    case Token::ReserveWord::FORTK: return "for"; break;
    case Token::ReserveWord::GETINTTK: return "getint"; break;
    case Token::ReserveWord::GETCHARTK: return "getchar"; break;
    case Token::ReserveWord::PRINTFTK: return "printf"; break;
    case Token::ReserveWord::RETURNTK: return "return"; break;
    case Token::ReserveWord::VOIDTK: return "void"; break;                                       
    default: return ""; break;
    }
}

Lexer::~Lexer() {

}

Token Lexer::next() {
    char ch = source[pos];
    if (isdigit(ch)) {
    }
}