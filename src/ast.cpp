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