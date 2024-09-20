#include "lexer.h"

Lexer::Lexer(std::string source) {
    this->source = source;
    this->line_number = 0;
    this->pos = 0;
    for(int i = 0; i < static_cast<int>(Token::Token::ReserveWord::COUNT); i++) {
        Token::ReserveWord type = static_cast<Token::Token::ReserveWord>(i);
        std::string type_string = type_to_string(type);
        Token::TokenType token_type = transfer_type(type);
        this->reserve_words.insert({type_string, token_type});
    }
}

std::string Lexer::type_to_string(Token::ReserveWord type) {
    switch (type) {
        case Token::ReserveWord::MAINTK: return "main"; break;
        case Token::ReserveWord::CONSTTK: return "const"; break;
        case Token::ReserveWord::INTTK: return "int"; break;
        case Token::ReserveWord::CHARTK: return "char"; break;
        case Token::ReserveWord::BREAKTK: return "break"; break;
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

Token::TokenType Lexer::transfer_type(Token::ReserveWord type) {
    switch (type) {
        case Token::ReserveWord::MAINTK: return Token::TokenType::MAINTK; break;
        case Token::ReserveWord::CONSTTK: return Token::TokenType::CONSTTK; break;
        case Token::ReserveWord::INTTK: return Token::TokenType::INTTK; break;
        case Token::ReserveWord::CHARTK: return Token::TokenType::CHARTK; break;
        case Token::ReserveWord::BREAKTK: return Token::TokenType::BREAKTK; break;
        case Token::ReserveWord::CONTINUETK: return Token::TokenType::CONTINUETK; break;
        case Token::ReserveWord::IFTK: return Token::TokenType::IFTK; break;
        case Token::ReserveWord::ELSETK: return Token::TokenType::ELSETK; break;
        case Token::ReserveWord::FORTK: return Token::TokenType::FORTK; break;
        case Token::ReserveWord::GETINTTK: return Token::TokenType::GETINTTK; break;
        case Token::ReserveWord::GETCHARTK: return Token::TokenType::GETCHARTK; break;
        case Token::ReserveWord::PRINTFTK: return Token::TokenType::PRINTFTK; break;
        case Token::ReserveWord::RETURNTK: return Token::TokenType::RETURNTK; break;
        case Token::ReserveWord::VOIDTK: return Token::TokenType::VOIDTK; break;                                       
        default: return Token::TokenType::COUNT; break;
    }
}

Lexer::~Lexer() {

}

Token Lexer::next() {
    char ch = source[pos];
    if (isdigit(ch)) // number
        return intcon();
    else if (isalpha(ch) || ch == '_') // identifier start with alpha or _
        return idenfr();     
}

Token Lexer::intcon() {
    std::string number = "";
    while (pos < source.length() && isdigit(source[pos])) {
        number.push_back(source[pos++]);
    }
    return Token{number, Token::TokenType::INTCON, line_number};
}

Token Lexer::idenfr() {
    std::string identifier = "";
    while (pos < source.length() && (isalnum(source[pos]) || source[pos] == '_')) { // in the middle of identifier can be digit/alpha/_
        identifier.push_back(source[pos++]);
    }
    auto it = reserve_words.find(identifier); //  iterator; end?
    if(it != reserve_words.end()) { // find!
        Token::TokenType type = it->second;
        return Token{identifier, type, line_number};
    } else {
        return Token{identifier, Token::TokenType::IDENFR, line_number};
    }
}