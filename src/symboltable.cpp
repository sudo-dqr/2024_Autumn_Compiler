#include "symboltable.h"

std::shared_ptr<SymbolTable> SymbolTable::push_scope() {
    auto new_table = std::make_shared<SymbolTable>();
    new_table->father = shared_from_this();
    return new_table;
}

std::shared_ptr<SymbolTable> SymbolTable::pop_scope() {
    return father;
}

bool SymbolTable::exist_in_scope(const std::string &name) {
    return (symbols.find(name) != symbols.end());
}

bool SymbolTable::add_symbol(std::shared_ptr<Symbol> symbol) {
    if (exist_in_scope(symbol->name))
        return false;
    else {
        symbols[symbol->name] = symbol;
        return true;
    }
}

std::shared_ptr<Symbol> SymbolTable::get_symbol(const std::string &name) {
    auto symbol = symbols.find(name);
    if (symbol != symbols.end())
        return symbol->second;
    else if (father)
        return father->get_symbol(name);
    else
        return nullptr;
}
