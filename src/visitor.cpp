#include <algorithm>
#include "visitor.h"

Visitor::Visitor() {
    this->cur_scope = std::make_shared<SymbolTable>();
    this->loop_cnt = 0;
    this->is_void_func= false;
    this->scope_cnt = 1; // global
    this->symbol_list = std::deque<Symbol>();
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
        auto symbol = std::make_shared<Symbol>(type, ident, get_scope_cnt());
        symbol_list.push_back(*symbol);
        if (!cur_scope->add_symbol(symbol)) { // b error : redefined identifier
            report_error(line_number, 'b');
        }
    } else { // array
        // 暂时忽略表示数组长度的exp
        SymbolType type = SymbolType(true, btype, 0);
        auto symbol = std::make_shared<Symbol>(type, ident, get_scope_cnt());
        symbol_list.push_back(*symbol);
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
        auto symbol = std::make_shared<Symbol>(type, ident, get_scope_cnt());
        symbol_list.push_back(*symbol);
        if (!cur_scope->add_symbol(symbol)) {
            report_error(line_number, 'b');
        }
    } else {
        // 暂时忽略表示数组长度的exp
        SymbolType type = SymbolType(false, btype, 0);
        auto symbol = std::make_shared<Symbol>(type, ident, get_scope_cnt());
        symbol_list.push_back(*symbol);
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
    std::deque<Symbol> params; // 记录参数类型 e error
    SymbolType type = SymbolType(func_type, params);
    auto func_symbol = std::make_shared<Symbol>(type, ident, get_scope_cnt());
    symbol_list.push_back(*func_symbol);
    if (!cur_scope->add_symbol(func_symbol)) {
        report_error(line_number, 'b');
    }
    cur_scope = cur_scope->push_scope();
    scope_cnt++;
    if (func_def.func_fparams) {
        for (const auto &func_fparam : func_def.func_fparams->func_fparams) {
            Token::TokenType param_type = func_fparam->btype->btype->get_type();
            std::string param_ident = func_fparam->ident->ident->get_token();
            if (func_fparam->is_array) {
                SymbolType param_symbol_type = SymbolType(false, param_type, 0);
                auto param_symbol = std::make_shared<Symbol>(param_symbol_type, param_ident, get_scope_cnt());
                func_symbol->type.params.push_back(*param_symbol);
                if (!cur_scope->add_symbol(param_symbol)) {
                    std::cout << "Funcdef FParam Error" << std::endl;
                }
                symbol_list.push_back(*param_symbol);
            } else {
                SymbolType param_symbol_type = SymbolType(false, param_type);
                auto param_symbol = std::make_shared<Symbol>(param_symbol_type, param_ident, get_scope_cnt());
                func_symbol->type.params.push_back(*param_symbol);
                if (!cur_scope->add_symbol(param_symbol)) {
                    std::cout << "Funcdef FParam Error" << std::endl;
                }
                symbol_list.push_back(*param_symbol);
            }
        }
    }
    visit_block(*func_def.block);
    cur_scope = cur_scope->pop_scope();
    bool has_ending_return = func_block_has_ending_return(*func_def.block);
    if ((!is_void_func) &&  (!has_ending_return)) {
        report_error(func_def.block->ending_line, 'g');
    }
}

void Visitor::visit_main_func(const MainFunc &main_func) {
    Token::TokenType func_type = Token::INTTK;
    this->is_void_func = false;
    std::string ident = "main";
    SymbolType type = SymbolType(func_type, std::deque<Symbol>());
    auto func_symbol = std::make_shared<Symbol>(type, ident, get_scope_cnt());
    symbol_list.push_back(*func_symbol);
    cur_scope->add_symbol(func_symbol); // main函数不会发生b错误
    cur_scope = cur_scope->push_scope();
    this->scope_cnt++;
    visit_block(*main_func.block);
    cur_scope = cur_scope->pop_scope();
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
    this->scope_cnt++;
    visit_block(*block_stmt.block);
    cur_scope = cur_scope->pop_scope();
}

void Visitor::visit_if_stmt(const IfStmt &if_stmt) {
    visit_cond(*if_stmt.condition);
    visit_stmt(*if_stmt.if_stmt);
    if (if_stmt.else_stmt) {
        visit_stmt(*if_stmt.else_stmt);
    }
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
    auto lval_symbol = visit_lval(*get_int_stmt.lval);
    if (lval_symbol) {
        if (lval_symbol->type.is_const) {
            report_error(get_int_stmt.lval->ident->ident->get_line_number(), 'h');
        }
    }
}

void Visitor::visit_get_char_stmt(const GetCharStmt &get_char_stmt) {
    auto lval_symbol = visit_lval(*get_char_stmt.lval);
    if (lval_symbol) {
        if (lval_symbol->type.is_const) {
            report_error(get_char_stmt.lval->ident->ident->get_line_number(), 'h');
        }
    }
}

void Visitor::visit_printf_stmt(const PrintfStmt &printf_stmt) {
    int cnt = control_cnt(printf_stmt.str->str->get_token());
    if (cnt != printf_stmt.exps.size()) {
        report_error(printf_stmt.str->str->get_line_number(), 'l');
    }
}

int Visitor::control_cnt(const std::string &str) { // %d | %c
    int cnt = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '%' && i + 1 < str.length()) {
            if (str[i + 1] == 'd' || str[i + 1] == 'c') {
                cnt++;
            }
        }
    }
    return cnt;
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

ExpInfo Visitor::visit_exp(const Exp &exp) {
    return visit_add_exp(*exp.add_exp);
}

ExpInfo Visitor::visit_add_exp(const AddExp &add_exp) {
    if (!add_exp.op) { // Add -> Mul
        return visit_mul_exp(*add_exp.mulexp);
    } else { // Add -> Mul {+/- Mul}
        ExpInfo info1 = visit_add_exp(*add_exp.addexp);
        ExpInfo info2 = visit_mul_exp(*add_exp.mulexp);
        return {info1.is_const && info2.is_const, false, 0, Token::INTTK};
    }
}

ExpInfo Visitor::visit_mul_exp(const MulExp &mul_exp) {
    if (!mul_exp.op) { // Mul -> Unary
        return visit_unary_exp(*mul_exp.unaryexp);
    } else { // Mul -> Unary {*/% Unary}
        ExpInfo info1 = visit_mul_exp(*mul_exp.mulexp);
        ExpInfo info2 = visit_unary_exp(*mul_exp.unaryexp);
        return {info1.is_const && info2.is_const, false, 0, Token::INTTK};
    }
}

ExpInfo Visitor::visit_unary_exp(const UnaryExp &unary_exp) { // c d e
    if (unary_exp.primary_exp) { // primary exp
        return visit_primary_exp(*unary_exp.primary_exp);
    } else if (unary_exp.ident) { // ident()
        std::string ident = unary_exp.ident->ident->get_token();
        std::shared_ptr<Symbol> ident_symbol = cur_scope->get_symbol(ident);
        if (!ident_symbol) { // c error : undefined identifier
            report_error(unary_exp.ident->ident->get_line_number(), 'c');
            return {false, false, 0, Token::END};
        }
        if (unary_exp.func_rparams) {
            if (unary_exp.func_rparams->exps.size() != ident_symbol->type.params.size()) {
                report_error(unary_exp.ident->ident->get_line_number(), 'd');
                return {false, false, 0, Token::END};
            } else { // e problem : how to know real param type?
                for (int i = 0; i < ident_symbol->type.params.size(); i++) {
                    SymbolType type = ident_symbol->type.params[i].type;
                    Token::TokenType f_param_type = type.btype;
                    bool f_param_is_array = type.is_array;
                    ExpInfo r_param_info = visit_exp(*unary_exp.func_rparams->exps[i]);
                    Token::TokenType r_param_type = r_param_info.type;
                    bool r_param_is_array = r_param_info.is_array;
                    if ((r_param_is_array && !f_param_is_array) || (!r_param_is_array && f_param_is_array)
                        || (r_param_is_array && f_param_is_array && (r_param_type != f_param_type))) {
                        report_error(unary_exp.ident->ident->get_line_number(), 'e');
                        return {false, false, 0, Token::END};
                    }
                }
            }
        } else {
            if (!ident_symbol->type.params.empty()) {
                report_error(unary_exp.ident->ident->get_line_number(), 'd');
                return {false, false, 0, Token::END};
            }
        }
        return {ident_symbol->type.is_const, false, 0, ident_symbol->type.btype};
    } else {
        return visit_unary_exp(*unary_exp.unary_exp);
    }
}

ExpInfo Visitor::visit_primary_exp(const PrimaryExp &primary_exp) {
    if (auto exp_ptr = std::get_if<Exp>(&primary_exp)) {
        return visit_exp(*exp_ptr);
    } else if (auto num_ptr = std::get_if<Number>(&primary_exp)) {
        return {true, false, 0, Token::INTTK};
    } else if (auto char_ptr = std::get_if<Character>(&primary_exp)) {
        return {false, false, 0, Token::CHARTK};
    } else if (auto lval_ptr = std::get_if<LVal>(&primary_exp)) {
        auto lval_symbol = visit_lval(*lval_ptr);
        if (lval_symbol) {
            return {lval_symbol->type.is_const, lval_symbol->type.is_array, lval_symbol->type.array_size, lval_symbol->type.btype};
        } else {
            return {false, false, 0, Token::END};
        }
    } else {
        std::cout << "visit_primary_exp error" << std::endl;
        return {false, false, 0, Token::END};
    }
}

void Visitor::visit_cond(const Cond &cond) {
    visit_lor_exp(*cond.lor_exp);
}

void Visitor::visit_lor_exp(const LOrExp &lor_exp) {
    if (lor_exp.lorexp) {
        visit_lor_exp(*lor_exp.lorexp);
    }
    visit_land_exp(*lor_exp.landexp);
}

void Visitor::visit_land_exp(const LAndExp &land_exp) {
    if (land_exp.landexp) {
        visit_land_exp(*land_exp.landexp);
    }
    visit_eq_exp(*land_exp.eqexp);
}

void Visitor::visit_eq_exp(const EqExp &eq_exp) {
    if (!eq_exp.op) {
        visit_rel_exp(*eq_exp.relexp);
    } else {
        visit_eq_exp(*eq_exp.eqexp);
        visit_rel_exp(*eq_exp.relexp);
    }
}

void Visitor::visit_rel_exp(const RelExp &rel_exp) {
    if (!rel_exp.op) {
        visit_add_exp(*rel_exp.addexp);
    } else {
        visit_rel_exp(*rel_exp.relexp);
        visit_add_exp(*rel_exp.addexp);
    }
}

int Visitor::get_scope_cnt() {
    if (cur_scope->is_in_global_scope()) return 1;
    else return scope_cnt;
}

void Visitor::print_symbol_list(std::ostream &os) {
    std::sort(symbol_list.begin(), symbol_list.end(), [](const Symbol &a, const Symbol &b) {
        return a.scope_cnt < b.scope_cnt;
    });
    for (const auto &symbol : symbol_list) {
        os << symbol.scope_cnt << " " << symbol.name << " " << symbol.type.to_string() << std::endl;
    }
}