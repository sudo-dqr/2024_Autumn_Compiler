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
        std::deque<Token> recoverybuf; // 保存stmt处理中读LVal的token 这部分实际上是可能解析错误的, 见parser.cpp中的注释
        bool is_recovering = false; // 是否正在恢复

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
        void start_recovery();
        void done_recovery();
        void abort_recovery();

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
        std::unique_ptr<ConstExp> parse_constexp();
        std::unique_ptr<Exp> parse_exp();
        std::unique_ptr<ConstInitVal> parse_const_initval();
        std::unique_ptr<InitVal> parse_initval();
        std::unique_ptr<AddExp> parse_addexp();
        std::unique_ptr<FuncDef> parse_funcdef();
        std::unique_ptr<FuncType> parse_functype();
        std::unique_ptr<Ident> parse_ident();
        std::unique_ptr<StringConst> parse_stringconst();
        std::unique_ptr<FuncFParams> parse_funcfparams();
        std::unique_ptr<Block> parse_block();
        std::unique_ptr<BlockItem> parse_blockitem();
        std::unique_ptr<MainFunc> parse_mainfunc();
        std::unique_ptr<FuncFParam> parse_funcfparam();
        std::unique_ptr<Stmt> parse_stmt();
        std::unique_ptr<IfStmt> parse_ifstmt();
        std::unique_ptr<Cond> parse_cond();
        std::unique_ptr<ForStmt> parse_forstmt();
        std::unique_ptr<AssignStmt> parse_assignstmt();
        std::unique_ptr<BreakStmt> parse_breakstmt();
        std::unique_ptr<ContinueStmt> parse_continuestmt();
        std::unique_ptr<ReturnStmt> parse_returnstmt();
        std::unique_ptr<PrintfStmt> parse_printfstmt();
        std::unique_ptr<LVal> parse_lval();
        std::unique_ptr<LOrExp> parse_lorexp();
        std::unique_ptr<Number> parse_number();
        std::unique_ptr<Character> parse_character();
        std::unique_ptr<PrimaryExp> parse_primaryexp();
        std::unique_ptr<UnaryOp> parse_unaryop();
        std::unique_ptr<UnaryExp> parse_unaryexp();
        std::unique_ptr<CallFunc> parse_callfunc();
        std::unique_ptr<FuncRParams> parse_funcrparams();

};

#endif