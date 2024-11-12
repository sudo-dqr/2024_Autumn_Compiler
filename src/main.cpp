#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "lexer.h"
#include "parser.h"
#include "visitor.h"

int main() {
    std::ifstream file("testfile.txt");
    if (!file) {
        std::cout << "testfile not found!" << std::endl;
        return 1;
    }
    std::ofstream error_out("error.txt", std::ios::trunc);
    error_out.close();
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();
    Lexer lexer = Lexer(text);
    Parser parser = Parser(lexer);
    auto comp_unit = parser.parse();
    Visitor visitor = Visitor();
    visitor.visit(*comp_unit);
    std::ofstream symbol_table_out("symbol.txt", std::ios::trunc);
    visitor.print_symbol_list(symbol_table_out);
    symbol_table_out.close();
    ErrorList::print_errors();
    return 0;
}

