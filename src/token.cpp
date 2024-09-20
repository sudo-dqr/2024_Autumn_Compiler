#include "token.h"

Token::Token(std::string token, TokenType type, int line_number) {
    this->token = token;
    this->type = type;
    this->line_number = line_number;
}

Token::~Token() {

}

std::string Token::get_token() {
    return this->token;
}

Token::TokenType Token::get_type() {
    return this->type;
}

int Token::get_line_number() {
    return this->line_number;
}