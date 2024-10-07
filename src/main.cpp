#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "lexer.h"
using namespace std;

int main() {
    ifstream file("testfile.txt");
    if (!file) {
        cout << "testfile not found!" << endl;
        return 1;
    }
    stringstream buffer;
    buffer << file.rdbuf();
    string text = buffer.str();
    Lexer lexer = Lexer(text);
    // 输出到lexer.txt中
    ofstream lexer_out("lexer.txt", std::ofstream::trunc);
    while (lexer.has_next()) {
        lexer_out << lexer.next().to_string() << endl;
    }
    lexer_out.close();

    return 0;
}

