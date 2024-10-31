#ifndef COMPILER_SYMBOLTABLE_H
#define COMPILER_SYMBOLTABLE_H

#include <string>
#include <memory>
#include <unordered_map>
#include <deque>

enum SymbolType {
    CHARFUNC, INTFUNC, VOIDFUNC,
    CONSTCHAR, CONSTINT, CONSTINTARRAY, CONSTCHARARRAY,
    CHAR, INT, CHARARRAY, INTARRAY
};

struct Symbol {
    SymbolType type;
    std::string name;
    int line_number;

    Symbol(SymbolType type, std::string name, int line_number)
        : type(type), name(name), line_number(line_number) {}
};

struct CharFuncSymbol : public Symbol {
    std::deque<Symbol> params;

    CharFuncSymbol(std::string name, int line_number, std::deque<Symbol>)
        : Symbol(SymbolType::CHARFUNC, name, line_number) {}
};

struct IntFuncSymbol : public Symbol {
    std::deque<Symbol> params;

    IntFuncSymbol(std::string name, int line_number, std::deque<Symbol>)
        : Symbol(SymbolType::INTFUNC, name, line_number) {}
};

struct VoidFuncSymbol : public Symbol {
    std::deque<Symbol> params;

    VoidFuncSymbol(std::string name, int line_numer, std::deque<Symbol>)
        : Symbol(SymbolType::VOIDFUNC, name, line_numer) {}
};

struct ConstCharSymbol : public Symbol {
    ConstCharSymbol(std::string name, int line_number)
        : Symbol(SymbolType::CONSTCHAR, name, line_number) {}
};

struct ConstIntSymbol : public Symbol {
    ConstIntSymbol(std::string name, int line_number)
        : Symbol(SymbolType::CONSTINT, name, line_number) {}
};

struct ConstIntArraySymbol :public Symbol {
    ConstIntArraySymbol(std::string name, int line_number)
        : Symbol(SymbolType::CONSTINTARRAY, name, line_number) {}
};

struct ConstCharArraySymbol : public Symbol {
    ConstCharArraySymbol(std::string name, int line_number)
        : Symbol(SymbolType::CONSTCHARARRAY, name, line_number) {}
};

struct IntSymbol : public Symbol {
    IntSymbol(std::string name, int line_number)
        : Symbol(SymbolType::INT, name, line_number) {}
};

struct CharSymbol : public Symbol {
    CharSymbol(std::string name, int line_number)
        : Symbol(SymbolType::CHAR, name, line_number) {}
};

struct CharArraySymbol : public Symbol {
    CharArraySymbol(std::string name, int line_number)
        : Symbol(SymbolType::CHARARRAY, name, line_number) {}
};

struct IntArraySymbol : public Symbol {
    IntArraySymbol(std::string name, int line_number)
        : Symbol(SymbolType::INTARRAY, name, line_number) {}
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
