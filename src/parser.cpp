#include "parser.h"

void Parser::next_token() {
    if (!backbuf.empty()) { // 将预读的token从backbuf移回buffer
        buffer.push_back(backbuf.back());
        backbuf.pop_back();
    } else if (lexer.has_next()) {
        buffer.push_back(lexer.next());
    } else {
        std::cout << "Error! No Lexer Read!" << std::endl;
    }

    // backbuf是不断消耗的 不需要关心内存
    // buffer需要不断从头部移除旧元素来控制内存
    if (buffer.size() > 5) {
        buffer.pop_front();
    }
}

Token Parser::get_curtoken() {
    return buffer.back();
}

void Parser::unget_token() { // 将预读的token从buffer转移到backbuf
    backbuf.push_back(buffer.back());
    buffer.pop_back();
}

std::unique_ptr<CompUnit> Parser::parse() {
    auto comp_unit = parse_comp_unit();
    return comp_unit;
}

std::unique_ptr<CompUnit> Parser::parse_comp_unit() {
    next_token();
    auto comp_unit = std::make_unique<CompUnit>();
    while (comp_unit_judge_next_type() == CompUnitType::DECL) {
        comp_unit->decls.push_back(parse_decl());
    }
    while (comp_unit_judge_next_type() == CompUnitType::FUNCDEF) {
        comp_unit->func_defs.push_back(parse_funcdef());
    }
    comp_unit->main_func = parse_mainfunc();
    return comp_unit;
}

Parser::CompUnitType Parser::comp_unit_judge_next_type() {
    Token t = get_curtoken();
    if (t.get_type() == Token::CONSTTK) {
        return CompUnitType::DECL;
    } else if (t.get_type() == Token::VOIDTK) {
        return CompUnitType::FUNCDEF;
    }
    next_token();
    t = get_curtoken();
    if (t.get_type() == Token::MAINTK) {
        return CompUnitType::MAINFUNC;
    }
    next_token();
    t = get_curtoken();
    unget_token(); // 回退预读的token
    unget_token();
    if (t.get_type() == Token::LPARENT) {
        return CompUnitType::FUNCDEF;
    } else {
        return CompUnitType::DECL;
    }
}