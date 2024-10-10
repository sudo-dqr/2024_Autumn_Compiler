#include "ast.h"
//! this file is used to print the ast tree
//! 实际上是输出语法树的后序遍历

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
    os << "SEMICN ;" << std::endl;
    os << "<ConstDecl>" << std::endl;
}

void VarDecl::print(std::ostream &os) { // VarDecl → BType VarDef { ',' VarDef } ';'
    this->btype->print(os);
    for (auto &var_def : this->var_defs) {
        var_def->print(os);
    }
    os << "SEMICN ;" << std::endl;
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

void ConstExp::print(std::ostream &os) { // ConstExp → AddExp
    this->add_exp->print(os);
    os << "<ConstExp>" << std::endl;
}

void ConstExps::print(std::ostream &os) { // ConstExps → ConstExp { ',' ConstExp }
    for (size_t i = 0; i < this->const_exps.size(); ++i) {
        this->const_exps[i]->print(os);
        if (i < this->const_exps.size() - 1) {
            os << "COMMA ," << std::endl;
        }
    }
}

void VarDef::print(std::ostream &os) { //VarDef → Ident [ '[' ConstExp ']' ] | Ident [ '[' ConstExp ']' ] '='InitVal
    this->ident->print(os);
    if (this->const_exp) {
        os << "LBRACK [" << std::endl;
        this->const_exp->print(os);
        os << "RBRACK ]" << std::endl;
    }
    if (this->init_val) {
        os << "ASSIGN =" << std::endl;
        std::visit(
            [&os](auto &arg) {
                arg.print(os);
            },
            (*init_val)
        );
        os << "<InitVal>" << std::endl;
    }
    os << "<VarDef>" << std::endl;
}

void Exp::print(std::ostream &os) { // Exp → AddExp
    this->add_exp->print(os);
    os << "<Exp>" << std::endl;
}

void Exps::print(std::ostream &os) { // Exps → Exp { ',' Exp }
    for (size_t i = 0; i < this->exps.size(); ++i) {
        this->exps[i]->print(os);
        if (i < this->exps.size() - 1) {
            os << "COMMA ," << std::endl;
        }
    }
}

void StringConst::print(std::ostream &os) {
    os << "STRCON " << this->str->get_token() << std::endl;
}

void FuncDef::print(std::ostream &os) { //FuncDef → FuncType Ident '(' [FuncFParams] ')' Block
    this->func_type->print(os);
    this->ident->print(os);
    os << "LPARENT (" << std::endl;
    if (this->func_fparams) {
        this->func_fparams->print(os);
    }
    os << "RPARENT )" << std::endl;
    this->block->print(os);
    os << "<FuncDef>" << std::endl;
}

void MainFunc::print(std::ostream &os) { //'int' 'main' '(' ')' Block
    os << "INTTK int" << std::endl;
    os << "MAINTK main" << std::endl;
    os << "LPARENT (" << std::endl;
    os << "RPARENT )" << std::endl;
    this->block->print(os);
    os << "<MainFuncDef>" << std::endl;
}

void FuncType::print(std::ostream &os) {
    if (this->func_type->get_type() == Token::INTTK) {
        os << "INTTK int" << std::endl;
    } else {
        os << "CHARTK char" << std::endl;
    }
}

void Ident::print(std::ostream &os) {
    os << "IDENFR " << this->ident->get_token() << std::endl;
}

void FuncFParams::print(std::ostream &os) { // FuncFParams → FuncFParam { ',' FuncFParam }
    for (size_t i = 0; i < this->func_fparams.size(); ++i) {
        this->func_fparams[i]->print(os);
        if (i < this->func_fparams.size() - 1) {
            os << "COMMA ," << std::endl;
        }
    }
}

void FuncFParam::print(std::ostream &os) { //FuncFParam → BType Ident [ '[' ']' ]
    this->btype->print(os);
    this->ident->print(os);
    if (this->is_array) {
        os << "LBRACK [" << std::endl;
        os << "RBRACK ]" << std::endl;
    }
    os << "<FuncFParam>" << std::endl;
}

void Block::print(std::ostream &os) { // Block → '{' {BlockItem} '}'
    os << "LBRACE {" << std::endl;
    for (auto &block_item : this->block_items) { //!这里是一个嵌套的variant 需要对每一层进行visit
        std::visit(
            [&os](auto &arg) {
                std::visit(
                    [&os](auto &arg) {
                        arg.print(os);
                    },
                    (arg)
                );
            },
            (*block_item)
        );
    }
    os << "RBRACE }" << std::endl;
    os << "<Block>" << std::endl;
}

void AssignStmt::print(std::ostream &os) { // AssignStmt → LVal '=' Exp ';'
    this->lval->print(os);
    os << "ASSIGN =" << std::endl;
    this->exp->print(os);
    os << "SEMICN ;" << std::endl;
    os << "<Stmt>" << std::endl;
}

void ExpStmt::print(std::ostream &os) { // [Exp] ';'
    if (this->exp) {
        this->exp->print(os);
    }
    os << "SEMICN ;" << std::endl;
    os << "<Stmt>" << std::endl;
}

void BlockStmt::print(std::ostream &os) { // BlockStmt → Block
    this->block->print(os);
    os << "<Stmt>" << std::endl;
}

void IfStmt::print(std::ostream &os) { // IfStmt → 'if' '(' Cond ')' Stmt [ 'else' Stmt ]
    os << "IFTK if" << std::endl;
    os << "LPARENT (" << std::endl;
    this->condition->print(os);
    os << "RPARENT )" << std::endl;
    std::visit(
        [&os](auto &arg) {
            arg.print(os);
        },
        (*if_stmt)
    );
    if (this->else_stmt) {
        os << "ELSETK else" << std::endl;
        std::visit(
            [&os](auto &arg) {
                arg.print(os);
            },
            (*else_stmt)
        );
    }
    os << "<Stmt>" << std::endl;
}

void ForStmt::print(std::ostream &os) { // ForStmt → 'for' '(' [AssignStmt] ';' [Cond] ';' [AssignStmt] ')' Stmt
    os << "FORTK for" << std::endl;
    os << "LPARENT (" << std::endl;
    if (this->assign1) {
        this->assign1->print(os);
    }
    os << "SEMICN ;" << std::endl;
    if (this->condition) {
        this->condition->print(os);
    }
    os << "SEMICN ;" << std::endl;
    if (this->assign2) {
        this->assign2->print(os);
    }
    os << "RPARENT )" << std::endl;
    std::visit(
        [&os](auto &arg) {
            arg.print(os);
        },
        (*stmt)
    );
    os << "<Stmt>" << std::endl;

}

void Cond::print(std::ostream &os) { // Cond → LOrExp
    this->lor_exp->print(os);
    os << "<Cond>" << std::endl;
}

void BreakStmt::print(std::ostream &os) { // BreakStmt → 'break' ';'
    os << "BREAKTK break" << std::endl;
    os << "SEMICN ;" << std::endl;
    os << "<Stmt>" << std::endl;
}

void ContinueStmt::print(std::ostream &os) { // ContinueStmt → 'continue' ';'
    os << "CONTINUETK continue" << std::endl;
    os << "SEMICN ;" << std::endl;
    os << "<Stmt>" << std::endl;
}

void ReturnStmt::print(std::ostream &os) { // ReturnStmt → 'return' [Exp] ';'
    os << "RETURNTK return" << std::endl;
    if (this->return_exp) {
        this->return_exp->print(os);
    }
    os << "SEMICN ;" << std::endl;
    os << "<Stmt>" << std::endl;
}

void GetIntStmt::print(std::ostream &os) { // LVal '=' 'getint''('')'';' // i j
    this->lval->print(os);
    os << "ASSIGN =" << std::endl;
    os << "GETINTTK getint" << std::endl;
    os << "LPARENT (" << std::endl;
    os << "RPARENT )" << std::endl;
    os << "SEMICN ;" << std::endl;
    os << "<Stmt>" << std::endl;
}

void GetCharStmt::print(std::ostream &os) { // LVal '=' 'getchar''('')'';' // i j
    this->lval->print(os);
    os << "ASSIGN =" << std::endl;
    os << "GETCHARTK getchar" << std::endl;
    os << "LPARENT (" << std::endl;
    os << "RPARENT )" << std::endl;
    os << "SEMICN ;" << std::endl;
    os << "<Stmt>" << std::endl;
}

void PrintfStmt::print(std::ostream &os) { // PrintfStmt → 'printf''('StringConst{','Exp} ')' ';'
    os << "PRINTFTK printf" << std::endl;
    os << "LPARENT (" << std::endl;
    this->str->print(os);
    for (size_t i = 0; i < this->exps.size(); ++i) {
        os << "COMMA ," << std::endl;
        this->exps[i]->print(os);
    }
    os << "RPARENT )" << std::endl;
    os << "SEMICN ;" << std::endl;
    os << "<Stmt>" << std::endl;
}

void LVal::print(std::ostream &os) { // LVal -> Ident [ '[' Exp ']' ]
    this->ident->print(os);
    if (this->exp) {
        os << "LBRACK [" << std::endl;
        this->exp->print(os);
        os << "RBRACK ]" << std::endl;
    }
    os << "<LVal>" << std::endl;
}

void Number::print(std::ostream &os) {
    os << "INTCON " << this->num->get_token() << std::endl;
    os << "<Number>" << std::endl;
}

void Character::print(std::ostream &os) {
    os << "CHRCON " << this->ch->get_token() << std::endl;
    os << "<Character>" << std::endl;
}

void UnaryOp::print(std::ostream &os) {
    if (this->op->get_type() == Token::PLUS) {
        os << "PLUS +" << std::endl;
    } else if (this->op->get_type() == Token::MINU) {
        os << "MINU -" << std::endl;
    } else {
        os << "NOT !" << std::endl;
    }
    os << "<UnaryOp>" << std::endl;
}

void UnaryExp::print(std::ostream &os) { // UnaryExp → PrimaryExp | Ident '(' [FuncRParams] ')' | UnaryOp UnaryExp
    if (this->primary_exp) {
        //! 使用get_if<T>来判断当前的variant类型 如果成功则返回指向该类型的指针 否则返回nullptr
        //! 需要注意的是需要先对unique_ptr解引用获得实例之后再取地址
        if (auto exp_ptr = std::get_if<Exp>(&(*primary_exp))) {
            os << "LPARENT (" << std::endl;
            exp_ptr->print(os);
            os << "RPARENT )" << std::endl;
        } else if (auto lval_ptr = std::get_if<LVal>(&(*primary_exp))) {
            lval_ptr->print(os);
        } else if (auto num_ptr = std::get_if<Number>(&(*primary_exp))) {
            num_ptr->print(os);
        } else {
            auto char_ptr = std::get_if<Character>(&(*primary_exp));
            char_ptr->print(os);
        }
        os << "<PrimaryExp>" << std::endl;
    } else if (this->ident) {
        this->ident->print(os);
        os << "LPARENT (" << std::endl;
        if (this->func_rparams) {
            this->func_rparams->print(os);
        }
        os << "RPARENT )" << std::endl;
    } else {
        this->unary_op->print(os);
        this->unary_exp->print(os);
    }
    os << "<UnaryExp>" << std::endl;
}

void FuncRParams::print(std::ostream &os) { // FuncRParams → Exp { ',' Exp }
    for (size_t i = 0; i < this->exps.size(); ++i) {
        this->exps[i]->print(os);
        if (i < this->exps.size() - 1) {
            os << "COMMA ," << std::endl;
        }
    }
    os << "<FuncRParams>" << std::endl;
}

void MulExp::print(std::ostream &os) { // MulExp → UnaryExp | MulExp ('*' | '/' | '%') UnaryExp
    if (this->mulexp) {
        this->mulexp->print(os);
        if (this->op->get_type() == Token::MULT) {
            os << "MULT *" << std::endl;
        } else if (this->op->get_type() == Token::DIV) {
            os << "DIV /" << std::endl;
        } else {
            os << "MOD %" << std::endl;
        }
        this->unaryexp->print(os);
    } else {
        this->unaryexp->print(os);
    }
    os << "<MulExp>" << std::endl;
}

void AddExp::print(std::ostream &os) { // AddExp → MulExp | AddExp ('+' | '−') MulExp
    if (this->addexp) {
        this->addexp->print(os);
        if (this->op->get_type() == Token::PLUS) {
            os << "PLUS +" << std::endl;
        } else {
            os << "MINU -" << std::endl;
        }
        this->mulexp->print(os);
    } else {
        this->mulexp->print(os);
    }
    os << "<AddExp>" << std::endl;
}

void RelExp::print(std::ostream &os) { // RelExp → AddExp | RelExp ('<' | '>' | '<=' | '>=') AddExp
    if (this->relexp) {
        this->relexp->print(os);
        if (this->op->get_type() == Token::LSS) {
            os << "LSS <" << std::endl;
        } else if (this->op->get_type() == Token::LEQ) {
            os << "LEQ <=" << std::endl;
        } else if (this->op->get_type() == Token::GRE) {
            os << "GRE >" << std::endl;
        } else {
            os << "GEQ >=" << std::endl;
        }
        this->addexp->print(os);
    } else {
        this->addexp->print(os);
    }
    os << "<RelExp>" << std::endl;
}

void EqExp::print(std::ostream &os) { // EqExp → RelExp | EqExp ('==' | '!=') RelExp
    if (this->eqexp) {
        this->eqexp->print(os);
        if (this->op->get_type() == Token::EQL) {
            os << "EQL ==" << std::endl;
        } else {
            os << "NEQ !=" << std::endl;
        }
        this->relexp->print(os);
    } else {
        this->relexp->print(os);
    }
    os << "<EqExp>" << std::endl;
}

void LAndExp::print(std::ostream &os) { // LAndExp → EqExp | LAndExp '&&' EqExp
    if (this->landexp) {
        this->landexp->print(os);
        os << "AND &&" << std::endl;
        this->eqexp->print(os);
    } else {
        this->eqexp->print(os);
    }
    os << "<LAndExp>" << std::endl;
}

void LOrExp::print(std::ostream &os) { // LOrExp → LAndExp | LOrExp '||' LAndExp
    if (this->lorexp) {
        this->lorexp->print(os);
        os << "OR ||" << std::endl;
        this->landexp->print(os);
    } else {
        this->landexp->print(os);
    }
    os << "<LOrExp>" << std::endl;
}