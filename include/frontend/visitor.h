#ifndef COMPILER_VISITOR_H
#define COMPILER_VISITOR_H
#include "ast.h"
#include "symboltable.h"
#include "error.h"
#include "expinfo.h"
#include "type.h"
#include "value.h"
#include "instr.h"
#include <algorithm>
#include <deque>

class Visitor {
public:
    Visitor();
    void visit(const CompUnit &comp_unit);
    void print_symbol_list(std::ostream &os);

private:
    std::shared_ptr<SymbolTable> cur_scope;
    int loop_cnt;
    bool is_void_func;
    int scope_cnt;
    std::deque<Symbol> symbol_list;
    Function* cur_ir_function;
    BasicBlock* cur_ir_basic_block;
    Value* cur_ir_lval; // lval = exp
    //! if_stack is like | normal block | (else block) | if block |
    std::deque<BasicBlock*> if_stack;
    BasicBlock* if_true_block;
    BasicBlock* if_false_block;
    //! for_stack is like | cond block | stmt block | (assign2 block) | next normal block | 
    std::deque<BasicBlock*> for_stack;
    void visit_decl(const Decl &decl);
    void visit_func_def(const FuncDef &func_def);
    void prepare_ir_funcparam_stack(const FuncFParams &func_fparams);
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
    void visit_break_stmt(const BreakStmt &break_stmt);
    void visit_continue_stmt(const ContinueStmt &continue_stmt);
    void visit_return_stmt(const ReturnStmt &return_stmt);
    void visit_get_int_stmt(const GetIntStmt &get_int_stmt);
    void visit_get_char_stmt(const GetCharStmt &get_char_stmt);
    void visit_printf_stmt(const PrintfStmt &printf_stmt);
    int control_cnt(const std::string &str);
    // Stmt finish
    std::shared_ptr<Symbol> visit_lval(const LVal &lval);
    void visit_main_func(const MainFunc &main_func);
    void visit_const_decl(const ConstDecl &const_decl);
    void visit_const_def(const ConstDef &const_def, Token::TokenType type);
    void visit_var_decl(const VarDecl &var_decl);
    void visit_var_def(const VarDef &var_def, Token::TokenType type);
    ExpInfo visit_exp(const Exp &exp);
    ExpInfo visit_constexp(const ConstExp &const_exp);
    ExpInfo visit_add_exp(const AddExp &add_exp);
    ExpInfo visit_mul_exp(const MulExp &mul_exp);
    ExpInfo visit_unary_exp(const UnaryExp &unary_exp);
    ExpInfo visit_primary_exp(const PrimaryExp &primary_exp);
    void visit_cond(const Cond &cond);
    void visit_lor_exp(const LOrExp &lor_exp);
    void visit_land_exp(const LAndExp &land_exp);
    void visit_eq_exp(const EqExp &eq_exp);
    void visit_rel_exp(const RelExp &rel_exp);
};

#endif //COMPILER_VISITOR_H
