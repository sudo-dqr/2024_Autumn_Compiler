#ifndef COMPILER_VISITOR_H
#define COMPILER_VISITOR_H
#include "ast.h"
#include "symboltable.h"

class Visitor {
public:
    Visitor();
    void visit(const CompUnit &comp_unit);

private:
    std::shared_ptr<SymbolTable> cur_scope;
    int loop_cnt;
    bool is_void_func;
    void visit_decl(const Decl &decl);
    void visit_func_def(const FuncDef &func_def);
    void visit_block(const Block &block);
    static bool func_block_has_ending_return(const Block &block);
    void visit_block_item(const BlockItem &block_item);
    // Stmt
    void visit_stmt(const Stmt &stmt);
    void visit_assign_stmt(const AssignStmt &assign_stmt);
    void visit_exp_stmt(const ExpStmt &exp);
    void visit_block_stmt(const BlockStmt &block_stmt);
    void visit_if_stmt(const IfStmt &if_stmt);
    void visit_for_stmt(const ForStmt &for_stmt);
    void visit_for_assign_stmt(const ForAssignStmt &for_assign_stmt);
    void visit_cond(const Cond &cond);
    void visit_break_stmt(const BreakStmt &break_stmt);
    void visit_continue_stmt(const ContinueStmt &continue_stmt);
    void visit_return_stmt(const ReturnStmt &return_stmt);
    void visit_get_int_stmt(const GetIntStmt &get_int_stmt);
    void visit_get_char_stmt(const GetCharStmt &get_char_stmt);
    void visit_printf_stmt(const PrintfStmt &printf_stmt);
    // Stmt finish
    std::shared_ptr<Symbol> visit_lval(const LVal &lval);
    void visit_exp(const Exp &exp);
    void visit_main_func(const MainFunc &main_func);
    void visit_const_decl(const ConstDecl &const_decl);
    void visit_const_def(const ConstDef &const_def, Token::TokenType type);
    void visit_var_decl(const VarDecl &var_decl);
    void visit_var_def(const VarDef &var_def, Token::TokenType type);
    void visit_btype(const BType &btype);
    void visit_const_init_val(const ConstInitVal &const_init_val);

};

#endif //COMPILER_VISITOR_H
