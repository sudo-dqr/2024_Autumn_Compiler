#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "lexer.h"
#include "parser.h"
#include "visitor.h"
using namespace std;

int main() {
    ifstream file("testfile.txt");
    if (!file) {
        cout << "testfile not found!" << endl;
        return 1;
    }
    ofstream error_out("error.txt", ios::trunc);
    error_out.close();
    stringstream buffer;
    buffer << file.rdbuf();
    string text = buffer.str();
    Lexer lexer = Lexer(text);
    Parser parser = Parser(lexer);
    auto comp_unit = parser.parse();
    Visitor visitor = Visitor();
    visitor.visit(*comp_unit);
    std::ofstream symbol_table_out("symboltable.txt", ios::trunc);
    visitor.print_symbol_list(symbol_table_out);
    symbol_table_out.close();
    ErrorList::print_errors();
    return 0;
}

