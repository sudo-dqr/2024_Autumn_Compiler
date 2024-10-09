#include "ast.h"

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