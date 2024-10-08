#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"
#include "error.h"
#include <deque>

class Parser {

    private:
        Lexer &lexer;
        std::deque<Token> buffer; // 正常的token缓存区
        std::deque<Token> backbuf; // 保存预读的token

    public:    
        enum CompUnitType {
            DECL, FUNCDEF, MAINFUNC,
        };

    public:
        Parser(Lexer &lexer) : lexer(lexer) {};
        std::unique_ptr<CompUnit> parse();
        void next_token();
        Token get_curtoken();
        void unget_token();

    private:
        std::unique_ptr<CompUnit> parse_comp_unit();
        CompUnitType comp_unit_judge_next_type();
        std::unique_ptr<Decl> parse_decl();
        std::unique_ptr<FuncDef> parse_funcdef();
        std::unique_ptr<MainFunc> parse_mainfunc();
        std::unique_ptr<ConstDecl> parse_constdecl();
        std::unique_ptr<VarDecl> parse_vardecl();
        std::unique_ptr<BType> parse_btype();
        std::unique_ptr<ConstDef> parse_constdef();
        std::unique_ptr<VarDef> parse_vardef();

};

#endif