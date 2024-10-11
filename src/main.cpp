#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "lexer.h"
#include "parser.h"
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
    ofstream parser_out("parser.txt", ios::trunc);
    auto comp_unit = parser.parse();
    comp_unit->print(parser_out);
    return 0;
}

