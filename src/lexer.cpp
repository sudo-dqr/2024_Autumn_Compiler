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

// jump over the comment
// windows: \r\n linux: \n

Token Lexer::next() {
    char ch = source[pos];
    if (isdigit(ch)) // number
        return intcon();
    else if (isalpha(ch) || ch == '_') // identifier start with alpha or _
        return idenfr();     
    else if (ch == '/') {
        pos++;
        if (source[pos] == '/') // single-line comment 
            skip_single_line_comment();
        else if (source[pos] == '*') {// multi-line comment
            pos++;
            skip_multi_line_comment();
        } else
            return Token{"/", Token::TokenType::DIV, line_number};    
    }    
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

void Lexer::skip_single_line_comment() {
    while (pos < source.length() && source[pos] != '\n') {
        pos++;
    }
    if (source[pos] == '\n') {
        line_number++;
        pos++;
    }
}

void Lexer::skip_multi_line_comment() {
    State state = State::S1; // start state
    while (pos < source.length()) {
        switch (state) {
            case State::S1:
                if (source[pos] == '*')
                    state = State::S2;
                break;
            case State::S2:
                if (source[pos] == '/')
                    state = State::S3;
                else if (source[pos] == '*')
                    state = State::S2;
                else
                    state = State::S1;
                break;    
            case State::S3:
                break;
            default:
                break;
        }
        pos++;
        if (state == State::S3) {
            pos++;
            break;
        }
    }
}