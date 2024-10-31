#ifndef COMPILER_SYMBOLTABLE_H
#define COMPILER_SYMBOLTABLE_H

#include <string>
#include <memory>
#include <unordered_map>
#include <deque>
#include "token.h"

enum Category {
    BASIC, ARRAY, FUNC
};

struct SymbolType {
    Category category;
    Token::TokenType btype;
    bool is_const;
    bool is_array;
    int array_size;
    std::deque<SymbolType> params;

    // BASIC
    SymbolType(bool is_const, Token::TokenType type) : category(BASIC), btype(type), is_const(is_const), is_array(false), array_size(0) {}
    // ARRAY
    SymbolType(bool is_const, Token::TokenType type, int size) : category(ARRAY), btype(type), is_const(is_const), is_array(true), array_size(size) {}
    // FUNC
    SymbolType(Token::TokenType type, std::deque<SymbolType> params) : category(FUNC), btype(type), is_const(false), is_array(false), array_size(0), params(params) {}
};

struct Symbol {
    SymbolType type;
    std::string name;

    Symbol(SymbolType type, std::string name)
        : type(type), name(name) {}
};

class SymbolTable : public std::enable_shared_from_this<SymbolTable> {
private:
    std::unordered_map<std::string, std::shared_ptr<Symbol>> symbols;
    std::shared_ptr<SymbolTable> father;

public:
    SymbolTable() : father(nullptr) {}
    std::shared_ptr<Symbol> get_symbol(const std::string &name);
    bool exist_in_scope(const std::string &name);
    bool add_symbol(std::shared_ptr<Symbol> symbol);
    std::shared_ptr<SymbolTable> push_scope();
    std::shared_ptr<SymbolTable> pop_scope();
};




#endif //COMPILER_SYMBOLTABLE_H
