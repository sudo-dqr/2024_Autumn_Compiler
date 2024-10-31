#include "visitor.h"
#include "error.h"

Visitor::Visitor() {
    this->cur_scope = std::make_shared<SymbolTable>();
    this->loop_cnt = 0;
    this->is_void_func= false;
}


void Visitor::visit(const CompUnit &comp_unit) {
    for (const auto &decl : comp_unit.decls) {
        visit_decl(*decl);
    }
    for (const auto &func_def : comp_unit.func_defs) {
        visit_func_def(*func_def);
    }
    visit_main_func(*comp_unit.main_func);
}

void Visitor::visit_decl(const Decl &decl) {
    if (auto const_decl_ptr = std::get_if<ConstDecl>(&decl)) {
        visit_const_decl(*const_decl_ptr);
    } else if (auto var_decl_ptr = std::get_if<VarDecl>(&decl)) {
        visit_var_decl(*var_decl_ptr);
    } else {
        std::cout << "visit_decl error" << std::endl;
    }
}

void Visitor::visit_const_decl(const ConstDecl &const_decl) {
    // const
    auto type = const_decl.btype->btype->get_type(); // int/char
    for (const auto &const_def : const_decl.const_defs) {
        visit_const_def(*const_def, type);
    }
}

void Visitor::visit_const_def(const ConstDef &const_def, Token::TokenType btype) {
    auto ident = const_def.ident->ident->get_token();
    int line_number = const_def.ident->ident->get_line_number();
    if (!const_def.const_exp) { // constant
        SymbolType type = SymbolType(true, btype);
        auto symbol = std::make_shared<Symbol>(type, ident);
        if (!cur_scope->add_symbol(symbol)) { // b error : redefined identifier
            report_error(line_number, 'b');
        }
    } else { // array
        // 暂时忽略表示数组长度的exp
        SymbolType type = SymbolType(true, btype, 0);
        auto symbol = std::make_shared<Symbol>(type, ident);
        if (!cur_scope->add_symbol(symbol)) {
            report_error(line_number, 'b');
        }
    }
}

void Visitor::visit_var_decl(const VarDecl &var_decl) {
    auto type = var_decl.btype->btype->get_type();
    for (const auto &var_def : var_decl.var_defs) {
        visit_var_def(*var_def, type);
    }
}

void Visitor::visit_var_def(const VarDef &var_def, Token::TokenType btype) {
    auto ident = var_def.ident->ident->get_token();
    int line_number = var_def.ident->ident->get_line_number();
    if (!var_def.const_exp) { // variant
        SymbolType type = SymbolType(false, btype);
        auto symbol = std::make_shared<Symbol>(type, ident);
        if (!cur_scope->add_symbol(symbol)) {
            report_error(line_number, 'b');
        }
    } else {
        // 暂时忽略表示数组长度的exp
        SymbolType type = SymbolType(false, btype, 0);
        auto symbol = std::make_shared<Symbol>(type, ident);
        if (!cur_scope->add_symbol(symbol)) {
            report_error(line_number, 'b');
        }
    }
}

void Visitor::visit_func_def(const FuncDef &func_def) {
    Token::TokenType func_type = func_def.func_type->func_type->get_type();
    this->is_void_func = (func_type == Token::VOIDTK);
    int line_number = func_def.func_type->func_type->get_line_number();
    std::string ident = func_def.ident->ident->get_token();
    std::deque<SymbolType> params;
    cur_scope = cur_scope->push_scope();
    if (func_def.func_fparams) {
        for (const auto &func_fparam : func_def.func_fparams->func_fparams) {
            Token::TokenType param_type = func_fparam->btype->btype->get_type();
            std::string param_ident = func_fparam->ident->ident->get_token();
            if (func_fparam->is_array) {
                // 暂时忽略表示数组长度的exp
                SymbolType param_symbol_type = SymbolType(false, param_type, 0);
                params.push_back(param_symbol_type);
            } else {
                SymbolType param_symbol_type = SymbolType(false, param_type);
                params.push_back(param_symbol_type);
            }
        }
    }
    SymbolType type = SymbolType(func_type, params);
    auto symbol = std::make_shared<Symbol>(type, ident);
    if (!cur_scope->add_symbol(symbol)) {
        report_error(line_number, 'b');
    }
    visit_block(*func_def.block);
    bool has_ending_return = func_block_has_ending_return(*func_def.block);
    if ((func_type != Token::VOIDTK) &&  (!has_ending_return)) {
        report_error(func_def.block->ending_line, 'g');
    }
}

void Visitor::visit_main_func(const MainFunc &main_func) {
    Token::TokenType func_type = Token::INTTK;
    this->is_void_func = false;
    std::string ident = "main";
    SymbolType type = SymbolType(func_type, std::deque<SymbolType>());
    auto symbol = std::make_shared<Symbol>(type, ident);
    cur_scope->add_symbol(symbol); // main函数不会发生b错误
    cur_scope = cur_scope->push_scope();
    visit_block(*main_func.block);
    if (!func_block_has_ending_return(*main_func.block)) {
        report_error(main_func.block->ending_line, 'g');
    }
}

bool Visitor::func_block_has_ending_return(const Block &block) {
    if (block.block_items.empty()) {
        return false;
    } else {
        size_t last = block.block_items.size() - 1;
        if (auto stmt_ptr = std::get_if<Stmt>(&(*block.block_items[last]))) { // Stmt
            if (auto return_stmt_ptr = std::get_if<ReturnStmt>(stmt_ptr)) { // return
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
}

void Visitor::visit_block(const Block &block) {
    for (const auto &block_item : block.block_items) {
        visit_block_item(*block_item);
    }
}

void Visitor::visit_block_item(const BlockItem &block_item) {
    if (auto stmt_ptr = std::get_if<Stmt>(&block_item)) {
        visit_stmt(*stmt_ptr);
    } else if (auto decl_ptr = std::get_if<Decl>(&block_item)) {
        visit_decl(*decl_ptr);
    } else {
        std::cout << "visit_block_item error" << std::endl;
    }
}

void Visitor::visit_stmt(const Stmt &stmt) {
    if (auto assign_ptr = std::get_if<AssignStmt>(&stmt)) {
        visit_assign_stmt(*assign_ptr);
    } else if (auto exp_ptr = std::get_if<ExpStmt>(&stmt)) {
        visit_exp_stmt(*exp_ptr);
    } else if (auto block_ptr = std::get_if<BlockStmt>(&stmt)) {
        visit_block_stmt(*block_ptr);
    } else if (auto if_ptr = std::get_if<IfStmt>(&stmt)) {
        visit_if_stmt(*if_ptr);
    } else if (auto for_stmt = std::get_if<ForStmt>(&stmt)) {
        visit_for_stmt(*for_stmt);
    } else if (auto break_stmt = std::get_if<BreakStmt>(&stmt)) {
        visit_break_stmt(*break_stmt);
    } else if (auto continue_stmt = std::get_if<ContinueStmt>(&stmt)) {
        visit_continue_stmt(*continue_stmt);
    } else if (auto return_stmt = std::get_if<ReturnStmt>(&stmt)) {
        visit_return_stmt(*return_stmt);
    } else if (auto get_int_stmt = std::get_if<GetIntStmt>(&stmt)) {
        visit_get_int_stmt(*get_int_stmt);
    } else if (auto get_char_stmt = std::get_if<GetCharStmt>(&stmt)) {
        visit_get_char_stmt(*get_char_stmt);
    } else if (auto printf_stmt = std::get_if<PrintfStmt>(&stmt)) {
        visit_printf_stmt(*printf_stmt);
    } else {
        std::cout << "visit_stmt error" << std::endl;
    }
}

void Visitor::visit_assign_stmt(const AssignStmt &assign_stmt) {
    auto lval_symbol = visit_lval((*assign_stmt.lval));
    if (lval_symbol) {
        if (lval_symbol->type.is_const) {
            report_error(assign_stmt.lval->ident->ident->get_line_number(), 'h');
        } else {
            visit_exp(*assign_stmt.exp);
        }
    }
}

void Visitor::visit_for_assign_stmt(const ForAssignStmt &for_assign_stmt) {
    auto lval_symbol = visit_lval((*for_assign_stmt.lval));
    if (lval_symbol) {
        if (lval_symbol->type.is_const) {
            report_error(for_assign_stmt.lval->ident->ident->get_line_number(), 'h');
        } else {
            visit_exp(*for_assign_stmt.exp);
        }
    }
}

void Visitor::visit_exp_stmt(const ExpStmt &exp) {
    if (exp.exp)
        visit_exp(*exp.exp);
}

void Visitor::visit_block_stmt(const BlockStmt &block_stmt) {
    cur_scope = cur_scope->push_scope();
    visit_block(*block_stmt.block);
}

void Visitor::visit_if_stmt(const IfStmt &if_stmt) {
    visit_cond(*if_stmt.condition);
    visit_stmt(*if_stmt.if_stmt);
    if (if_stmt.else_stmt) {
        visit_stmt(*if_stmt.else_stmt);
    }
}

void Visitor::visit_cond(const Cond &cond) {

}

void Visitor::visit_for_stmt(const ForStmt &for_stmt) {
    if (for_stmt.assign1) {
        visit_for_assign_stmt(*for_stmt.assign1);
    }
    if (for_stmt.condition) {
        visit_cond(*for_stmt.condition);
    }
    if (for_stmt.assign2) {
        visit_for_assign_stmt(*for_stmt.assign2);
    }
    this->loop_cnt++;
    visit_stmt(*for_stmt.stmt);
    this->loop_cnt--;
}

void Visitor::visit_break_stmt(const BreakStmt &break_stmt) {
    if (this->loop_cnt == 0) {
        report_error(break_stmt.break_token->get_line_number(), 'm');
    }
}

void Visitor::visit_continue_stmt(const ContinueStmt &continue_stmt) {
    if (this->loop_cnt == 0) {
        report_error(continue_stmt.continue_token->get_line_number(), 'm');
    }
}

void Visitor::visit_return_stmt(const ReturnStmt &return_stmt) {
    if (return_stmt.return_exp) {
        if(this->is_void_func) {
            report_error(return_stmt.return_token->get_line_number(), 'f');
        }
    }
}

void Visitor::visit_get_int_stmt(const GetIntStmt &get_int_stmt) {

}

void Visitor::visit_get_char_stmt(const GetCharStmt &get_char_stmt) {

}

void Visitor::visit_printf_stmt(const PrintfStmt &printf_stmt) {

}

std::shared_ptr<Symbol> Visitor::visit_lval(const LVal &lval) {
    auto ident = lval.ident->ident->get_token();
    auto ident_symbol = cur_scope->get_symbol(ident);
    if (!ident_symbol) { // c error : undefined identifier
        report_error(lval.ident->ident->get_line_number(), 'c');
        return nullptr;
    }
    if (lval.exp) {
        visit_exp(*lval.exp);
    }
    return ident_symbol;
}

void Visitor::visit_exp(const Exp &exp) {

}