#ifndef COMPILER_SYMBOLTABLE_H
#define COMPILER_SYMBOLTABLE_H

#include <string>
#include <memory>
#include <unordered_map>
#include <deque>
#include "token.h"
#include <vector>
#include "value.h"

struct Symbol;

enum Category {
    BASIC, ARRAY, FUNC
};

struct SymbolType {
    Category category;
    Token::TokenType btype;
    bool is_const;
    bool is_array;
    int array_size;
    std::deque<Symbol> params;

    // BASIC
    SymbolType(bool is_const, Token::TokenType type) : category(BASIC), btype(type), is_const(is_const), is_array(false), array_size(0) {}
    // ARRAY
    SymbolType(bool is_const, Token::TokenType type, int size) : category(ARRAY), btype(type), is_const(is_const), is_array(true), array_size(size) {}
    // FUNC
    SymbolType(Token::TokenType type, std::deque<Symbol> params) : category(FUNC), btype(type), is_const(false), is_array(false), array_size(0), params(params) {}

    std::string to_string() const;
};

struct Symbol {
    SymbolType type;
    std::string name;
    int scope_cnt;
    int int_value;
    char char_value;
    Value* ir_value;
    std::vector<int> int_values;
    std::vector<char> char_values;
    std::string string_value;
    
    Symbol(SymbolType type, std::string name, int scope_cnt)
        : type(type), name(name), scope_cnt(scope_cnt) {}
};

class SymbolTable : public std::enable_shared_from_this<SymbolTable> {
private:
    std::unordered_map<std::string, std::shared_ptr<Symbol>> symbols;
    std::shared_ptr<SymbolTable> father;
    int scope = 1;

public:
    SymbolTable() : father(nullptr), scope(1) {}
    std::shared_ptr<Symbol> get_symbol(const std::string &name);
    bool exist_in_scope(const std::string &name);
    bool add_symbol(std::shared_ptr<Symbol> symbol);
    std::shared_ptr<SymbolTable> push_scope();
    std::shared_ptr<SymbolTable> pop_scope();
    bool is_in_global_scope();
    void set_scope(int scope) { this->scope = scope; }
    int get_scope() { return scope; }
};




#endif //COMPILER_SYMBOLTABLE_H
