#include "ast.h"

UnaryExp::UnaryExp(std::unique_ptr<PrimaryExp> primary_exp) {
    this->primary_exp = std::move(primary_exp);
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
