#include "ast.h"
//! this file is used to define the constructors of the classes in ast.h

//! constructor of Ident
Ident::Ident(std::unique_ptr<Token> ident) {
    this->ident = std::move(ident);
}

//! constructor of StringConst
StringConst::StringConst(std::unique_ptr<Token> str) {
    this->str = std::move(str);
}

//! constructor of CompUnit
CompUnit::CompUnit(std::vector<std::unique_ptr<FuncDef>> func_defs, std::vector<std::unique_ptr<Decl>> decls, std::unique_ptr<MainFunc> main_func) {
    this->func_defs = std::move(func_defs);
    this->decls = std::move(decls);
    this->main_func = std::move(main_func);
}

//! constructor of FuncDef
FuncDef::FuncDef(std::unique_ptr<FuncType> func_type, std::unique_ptr<Ident> ident, std::unique_ptr<FuncFParams> func_fparams, std::unique_ptr<Block> block) {
    this->func_type = std::move(func_type);
    this->ident = std::move(ident);
    this->func_fparams = std::move(func_fparams);
    this->block = std::move(block);
}

//! constructor of MainFunc
MainFunc::MainFunc(std::unique_ptr<Block> block) {
    this->block = std::move(block);
}

//! constructor of ConstDecl
ConstDecl::ConstDecl(std::unique_ptr<BType> btype, std::vector<std::unique_ptr<ConstDef>> const_defs) {
    this->btype = std::move(btype);
    this->const_defs = std::move(const_defs);
}

//! constructor of BType
BType::BType(std::unique_ptr<Token> btype) {
    this->btype = std::move(btype);
}

//! constructor of FuncType
FuncType::FuncType(std::unique_ptr<Token> func_type) {
    this->func_type = std::move(func_type);
}

//! constructor of VarDecl
VarDecl::VarDecl(std::unique_ptr<BType> btype, std::vector<std::unique_ptr<VarDef>> var_defs) {
    this->btype = std::move(btype);
    this->var_defs = std::move(var_defs);
}

//! constructor of ConstDef
ConstDef::ConstDef(std::unique_ptr<Ident> ident, std::unique_ptr<ConstExp> const_exp, std::unique_ptr<ConstInitVal> const_init_val) {
    this->ident = std::move(ident);
    this->const_exp = std::move(const_exp);
    this->const_init_val = std::move(const_init_val);
}

//! constructor of VarDef
VarDef::VarDef(std::unique_ptr<Ident> ident, std::unique_ptr<ConstExp> const_exp, std::unique_ptr<InitVal> init_val) {
    this->ident = std::move(ident);
    this->const_exp = std::move(const_exp);
    this->init_val = std::move(init_val);
}

//! constructor of FuncFParams
FuncFParams::FuncFParams(std::vector<std::unique_ptr<FuncFParam>> func_fparams) {
    this->func_fparams = std::move(func_fparams);
}

//! constructor of FuncFParam
FuncFParam::FuncFParam(std::unique_ptr<BType> btype, std::unique_ptr<Ident> ident, bool is_array) {
    this->btype = std::move(btype);
    this->ident = std::move(ident);
    this->is_array = is_array;
}

//! constructor of Block
Block::Block(std::vector<std::unique_ptr<BlockItem>> block_items) {
    this->block_items = std::move(block_items);
}

//! constructor of LVal
LVal::LVal(std::unique_ptr<Ident> ident, std::unique_ptr<Exp> exp) {
    this->ident = std::move(ident);
    this->exp = std::move(exp);
}

//! constructor of AssignStmt
AssignStmt::AssignStmt(std::unique_ptr<LVal> lval, std::unique_ptr<Exp> exp) {
    this->lval = std::move(lval);
    this->exp = std::move(exp);
}

//! constructor of ExpStmt
ExpStmt::ExpStmt(std::unique_ptr<Exp> exp) {
    this->exp = std::move(exp);
}

//! constructor of IfStmt
IfStmt::IfStmt(std::unique_ptr<Cond> condition, std::unique_ptr<Stmt> if_stmt, std::unique_ptr<Stmt> else_stmt) {
    this->condition = std::move(condition);
    this->if_stmt = std::move(if_stmt);
    this->else_stmt = std::move(else_stmt);
}

//! constructor of ForStmt
ForStmt::ForStmt(std::unique_ptr<AssignStmt> assign1, std::unique_ptr<Cond> condition, std::unique_ptr<AssignStmt> assign2, std::unique_ptr<Stmt> stmt) {
    this->assign1 = std::move(assign1);
    this->condition = std::move(condition);
    this->assign2 = std::move(assign2);
    this->stmt = std::move(stmt);
}

//! constructor of BreakStmt
BreakStmt::BreakStmt(std::unique_ptr<Token> break_token) {
    this->break_token = std::move(break_token);
}

//! constructor of ContinueStmt
ContinueStmt::ContinueStmt(std::unique_ptr<Token> continue_token) {
    this->continue_token = std::move(continue_token);
}

//! constructor of ReturnStmt
ReturnStmt::ReturnStmt(std::unique_ptr<Token> return_token, std::unique_ptr<Exp> return_exp) {
    this->return_token = std::move(return_token);
    this->return_exp = std::move(return_exp);
}

//! constructor of GetIntStmt
GetIntStmt::GetIntStmt(std::unique_ptr<LVal> lval) {
    this->lval = std::move(lval);
}

//! constructor of GetCharStmt
GetCharStmt::GetCharStmt(std::unique_ptr<LVal> lval) {
    this->lval = std::move(lval);
}

//! constructor of PrintfStmt
PrintfStmt::PrintfStmt(std::unique_ptr<StringConst> str, std::vector<std::unique_ptr<Exp>> exps) {
    this->str = std::move(str);
    this->exps = std::move(exps);
}

//! constructor of Number
Number::Number(std::unique_ptr<Token> num) {
    this->num = std::move(num);
}

//! constructor of Character
Character::Character(std::unique_ptr<Token> ch) {
    this->ch = std::move(ch);
}

//! constructor of UnaryOp
UnaryOp::UnaryOp(std::unique_ptr<Token> op) {
    this->op = std::move(op);
}

//! constructor of FuncRParams
FuncRParams::FuncRParams(std::vector<std::unique_ptr<Exp>> exps) {
    this->exps = std::move(exps);
}

//! constructor of UnaryExp
UnaryExp::UnaryExp(std::unique_ptr<PrimaryExp> primary_exp) {
    this->primary_exp = std::move(primary_exp); //!从参数中转移所有权
    this->ident = nullptr;this->func_rparams = nullptr;
    this->unary_op = nullptr;this->unary_exp = nullptr;
}

UnaryExp::UnaryExp(std::unique_ptr<Ident> ident, std::unique_ptr<FuncRParams> func_rparams) {
    this->primary_exp = nullptr;
    this->ident = std::move(ident);this->func_rparams = std::move(func_rparams);
    this->unary_op = nullptr;this->unary_exp = nullptr;
}

UnaryExp::UnaryExp(std::unique_ptr<UnaryOp> unary_op, std::unique_ptr<UnaryExp> unary_exp) {
    this->unary_op = std::move(unary_op);
    this->unary_exp = std::move(unary_exp);
    this->primary_exp = nullptr; this->ident = nullptr; this->func_rparams = nullptr;
}

//! constructor of MulExp
MulExp::MulExp(std::unique_ptr<MulExp> mulexp, std::unique_ptr<Token> op, std::unique_ptr<UnaryExp> unaryexp) {
    this->mulexp = std::move(mulexp);
    this->op = std::move(op);
    this->unaryexp = std::move(unaryexp);
}

MulExp::MulExp(std::unique_ptr<UnaryExp> unaryexp) {
    this->mulexp = nullptr;
    this->op = nullptr;
    this->unaryexp = std::move(unaryexp);
}

//! constructor of AddExp
AddExp::AddExp(std::unique_ptr<AddExp> addexp, std::unique_ptr<Token> op, std::unique_ptr<MulExp> mulexp) {
    this->addexp = std::move(addexp);
    this->op = std::move(op);
    this->mulexp = std::move(mulexp);
}

AddExp::AddExp(std::unique_ptr<MulExp> mulexp) {
    this->addexp = nullptr;
    this->op = nullptr;
    this->mulexp = std::move(mulexp);
}

//! constructor of RelExp
RelExp::RelExp(std::unique_ptr<RelExp> relexp, std::unique_ptr<Token> op, std::unique_ptr<AddExp> addexp) {
    this->relexp = std::move(relexp);
    this->op = std::move(op);
    this->addexp = std::move(addexp);
}

RelExp::RelExp(std::unique_ptr<AddExp> addexp) {
    this->relexp = nullptr;
    this->op = nullptr;
    this->addexp = std::move(addexp);
}

//! constructor of EqExp
EqExp::EqExp(std::unique_ptr<EqExp> eqexp, std::unique_ptr<Token> op, std::unique_ptr<RelExp> relexp) {
    this->eqexp = std::move(eqexp);
    this->op = std::move(op);
    this->relexp = std::move(relexp);
}

EqExp::EqExp(std::unique_ptr<RelExp> relexp) {
    this->eqexp = nullptr;
    this->op = nullptr;
    this->relexp = std::move(relexp);
}

//! constructor of LAndExp
LAndExp::LAndExp(std::unique_ptr<LAndExp> landexp, std::unique_ptr<EqExp> eqexp) {
    this->landexp = std::move(landexp);
    this->eqexp = std::move(eqexp);
}

LAndExp::LAndExp(std::unique_ptr<EqExp> eqexp) {
    this->landexp = nullptr;
    this->eqexp = std::move(eqexp);
}

//! constructor of LOrExp
LOrExp::LOrExp(std::unique_ptr<LOrExp> lorexp, std::unique_ptr<LAndExp> landexp) {
    this->lorexp = std::move(lorexp);
    this->landexp = std::move(landexp);
}

LOrExp::LOrExp(std::unique_ptr<LAndExp> landexp) {
    this->lorexp = nullptr;
    this->landexp = std::move(landexp);
}

//! constructor of Exp
Exp::Exp(std::unique_ptr<AddExp> add_exp) {
    this->add_exp = std::move(add_exp);
}

//! constructor of ConstExp
ConstExp::ConstExp(std::unique_ptr<AddExp> add_exp) {
    this->add_exp = std::move(add_exp);
}

//! constructor of Cond
Cond::Cond(std::unique_ptr<LOrExp> lor_exp) {
    this->lor_exp = std::move(lor_exp);
}