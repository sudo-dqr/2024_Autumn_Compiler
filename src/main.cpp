#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "lexer.h"
#include "parser.h"
#include "visitor.h"
#include "mips_generate.h"

int main() {
    std::ifstream file("testfile.txt");
    if (!file) {
        std::cout << "testfile not found!" << std::endl;
        return 1;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();
    Lexer lexer = Lexer(text);
    Parser parser = Parser(lexer);
    auto comp_unit = parser.parse();
    Visitor visitor = Visitor();
    visitor.visit(*comp_unit);
    visitor.print_symbol_list();
    Module::get_instance().print_llvm_ir();
    MipsBackend backend = MipsBackend();
    backend.start_generate_mips_code(Module::get_instance(), MipsBackend::ONLY_MULT_DIV);
    backend.print_mips_code();
    ErrorList::print_errors();
    return 0;
}

