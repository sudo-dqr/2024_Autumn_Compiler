#include "ast.h"
//! this file is used to print the ast tree
//! 实际上是输出语法树的后序遍历

void Ident::print(std::ostream &os) {
    os << "IDENFR " << this->ident->get_token() << std::endl;
}

void StringConst::print(std::ostream &os) {
    os << "STRCON " << this->str->get_token() << std::endl;
}

void Number::print(std::ostream &os) {
    os << "INTCON " << this->num->get_token() << std::endl;
}

void Character::print(std::ostream &os) {
    os << "CHARCON " << this->ch->get_token() << std::endl;
}

void CompUnit::print(std::ostream &os) { // CompUnit → {Decl} {FuncDef} MainFuncDef
    for (auto &decl : this->decls) {
        std::visit(
            [&os](auto &arg){
                arg.print(os);
            }, 
            (*decl) //!需要注意的是数组中保存的是unique_ptr类型的元素, visit不能访问unique_ptr, 必须直接拿到元素类型，所以解引用
        );
    }
    for (auto &func_def : this->func_defs) { // 对容器中元素的引用 避免unique_ptr拷贝
        func_def->print(os);
    }
    main_func->print(os);
    os << "<CompUnit>" << std::endl;
}

void ConstDecl::print(std::ostream &os) { // ConstDecl → 'const' BType ConstDef { ',' ConstDef } ';'
    os << "CONSTTK const" << std::endl;
    this->btype->print(os);
    for (auto &const_def : this->const_defs) {
        const_def->print(os);
    }
    os << "<ConstDecl>" << std::endl;
}

void VarDecl::print(std::ostream &os) { // VarDecl → BType VarDef { ',' VarDef } ';'
    this->btype->print(os);
    for (auto &var_def : this->var_defs) {
        var_def->print(os);
    }
    os << "<VarDecl>" << std::endl;
}

void BType::print(std::ostream &os) {
    if (this->btype->get_type() == Token::INTTK) {
        os << "INTTK int" << std::endl;
    } else {
        os << "CHARTK char" << std::endl;
    }
}

void ConstDef::print(std::ostream &os) { // ConstDef → Ident [ '[' ConstExp ']' ] '=' ConstInitVal
    this->ident->print(os);
    if (this->const_exp) {
        os << "LBRACK [" << std::endl;
        this->const_exp->print(os);
        os << "RBRACK ]" << std::endl;
    }
    os << "ASSIGN =" << std::endl;
    std::visit(
        [&os](auto &arg){
            arg.print(os);
        },
        (*const_init_val) //需要解引用, 从unique_ptr中取出元素
    );
    os << "<ConstDef>" << std::endl;
}


