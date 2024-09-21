#include "lexer.h"

Lexer::Lexer(std::string source) {
    this->source = source;
    this->line_number = 1;
    this->pos = 0;
    this->errors = std::vector<Error>();
    this->tokens = std::vector<Token>();
    initialize_reverse_word_map();
}

void Lexer::initialize_reverse_word_map() {
    reserve_words["if"] = Token::TokenType::IFTK;
    reserve_words["else"] = Token::TokenType::ELSETK;
    reserve_words["for"] = Token::TokenType::FORTK;
    reserve_words["return"] = Token::TokenType::RETURNTK;
    reserve_words["int"] = Token::TokenType::INTTK;
    reserve_words["char"] = Token::TokenType::CHARTK;
    reserve_words["void"] = Token::TokenType::VOIDTK;
    reserve_words["const"] = Token::TokenType::CONSTTK;
    reserve_words["main"] = Token::TokenType::MAINTK;
    reserve_words["break"] = Token::TokenType::BREAKTK;
    reserve_words["continue"] = Token::TokenType::CONTINUETK;
    reserve_words["getint"] = Token::TokenType::GETINTTK;
    reserve_words["getchar"] = Token::TokenType::GETCHARTK;
    reserve_words["printf"] = Token::TokenType::PRINTFTK;
}

Lexer::~Lexer() {

}

// jump over the comment
// windows: \r\n linux: \n

void Lexer::next() {
    char ch = source[pos];
    if (isdigit(ch)) // number
        intcon();
    else if (isalpha(ch) || ch == '_') // identifier start with alpha or _
        idenfr();
    else if (ch == '/') {
        pos++;
        if (source[pos] == '/') {// single-line comment 
            skip_single_line_comment();
        }
        else if (source[pos] == '*') {// multi-line comment
            pos++;
            skip_multi_line_comment();
        } else // DIV
            tokens.push_back(Token{"/", Token::TokenType::DIV, line_number});    
    }
    else if (ch == '\"') // strcon
        strcon();
    else if (ch == '\'') // chrcon
        chrcon();   
    else if (ch == '!') { // ! or !=
        if (source[pos + 1] == '=') {
            pos += 2;
            tokens.push_back(Token{"!=",Token::TokenType::NEQ, line_number});
        } else {
            pos++;
            tokens.push_back(Token{"!", Token::TokenType::NOT, line_number});
        }
    } else if (ch == '&') {
        if (source[pos + 1] == '&') {
            pos += 2;
            tokens.push_back(Token{"&&", Token::AND, line_number});
        } else { // Error! type: a
            pos++;
            errors.push_back(Error(line_number, 'a'));
        }
    } else if (ch == '|') {
        if (source[pos + 1] == '|') {
            pos += 2;
            tokens.push_back(Token{"||", Token::OR, line_number});
        } else { // Error! type: a
            pos++;
            errors.push_back(Error(line_number, 'a'));
        }
    } else if (ch == '+') {
        pos++;
        tokens.push_back(Token{"+", Token::TokenType::PLUS, line_number});
    } else if (ch == '-') {
        pos++;
        tokens.push_back(Token{"-", Token::TokenType::MINU, line_number});
    } else if (ch == '*') {
        pos++;
        tokens.push_back(Token{"*", Token::TokenType::MULT, line_number});
    } else if (ch == '%') {
        pos++;
        tokens.push_back(Token{"%", Token::TokenType::MOD, line_number});
    } else if (ch == '<') {
        if (source[pos + 1] == '=') {
            pos += 2;
            tokens.push_back(Token{"<=", Token::LEQ, line_number});
        } else {
            pos++;
            tokens.push_back(Token{"<", Token::LSS, line_number});
        }
    } else if (ch == '>') {
        if (source[pos + 1] == '=') {
            pos += 2;
            tokens.push_back(Token{">=", Token::GEQ, line_number});
        } else {
            pos++;
            tokens.push_back(Token{">", Token::GRE, line_number});
        }
    } else if (ch == '=') {
        if (source[pos + 1] == '=') {
            pos += 2;
            tokens.push_back(Token{"==", Token::EQL, line_number});
        } else {
            pos++;
            tokens.push_back(Token{"=", Token::ASSIGN, line_number});
        }
    } else if (ch == ';') {
        pos++;
        tokens.push_back(Token{";", Token::SEMICN, line_number});
    } else if (ch == ',') {
        pos++;
        tokens.push_back(Token{",", Token::COMMA, line_number});
    } else if (ch == '(') {
        pos++;
        tokens.push_back(Token{"(", Token::LPARENT, line_number});
    } else if (ch == ')') {
        pos++;
        tokens.push_back(Token{")", Token::RPARENT, line_number});
    } else if (ch == '[') {
        pos++;
        tokens.push_back(Token{"[", Token::LBRACK, line_number});
    } else if (ch == ']') {
        pos++;
        tokens.push_back(Token{"]", Token::RBRACK, line_number});
    } else if (ch == '{') {
        pos++;
        tokens.push_back(Token{"{", Token::LBRACE, line_number});
    } else if (ch == '}') {
        pos++;
        tokens.push_back(Token{"}", Token::RBRACE, line_number});
    } else if (ch == '\n') {
        line_number++;
        pos++;
    } else {
        pos++;
    }
}

void Lexer::intcon() {
    std::string number = "";
    while (pos < source.length() && isdigit(source[pos])) {
        number.push_back(source[pos++]);
    }
    tokens.push_back(Token{number, Token::TokenType::INTCON, line_number});
}

void Lexer::idenfr() {
    std::string identifier = "";
    while (pos < source.length() && (isalnum(source[pos]) || source[pos] == '_')) { // in the middle of identifier can be digit/alpha/_
        identifier.push_back(source[pos++]);
    }
    auto it = reserve_words.find(identifier); //  iterator; end?
    if(it != reserve_words.end()) { // find!
        Token::TokenType type = it->second;
        tokens.push_back(Token{identifier, type, line_number});
    } else { // not find!s
        tokens.push_back(Token{identifier, Token::TokenType::IDENFR, line_number});
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
        if (state == State::S3) break;
    }
}

void Lexer::strcon() {
    std::string str = "";
    pos++;
    while (pos < source.length() && source[pos] != '\"') {
        str.push_back(source[pos++]);
    }
    if (source[pos] == '\"') {
        pos++;
    } // else: error
    str = "\"" + str + "\"";
    tokens.push_back(Token{str, Token::TokenType::STRCON, line_number});
}

void Lexer::chrcon() {
    std::string chr = "";
    pos++;
    // 需要考虑转义字符
    if (source[pos] == '\\') {
        chr.push_back(source[pos++]);
    } 
    chr.push_back(source[pos]);
    pos +=2;
    chr = "\'" + chr + "\'";
    tokens.push_back(Token{chr, Token::TokenType::CHRCON, line_number});
}

void Lexer::run() {
    std::ofstream out("lexer.txt", std::ofstream::out);
    while (pos < source.length()) {
        next();
    }
    for (int i = 0; i < tokens.size(); i++) {
        out << tokens[i].to_string() << std::endl;
    }
    out.close();

    if (!errors.empty()) {
        std::ofstream error_out("error.txt", std::ofstream::out);
        error_out << errors[0].to_string() << std::endl;
        error_out.close();
    }
}