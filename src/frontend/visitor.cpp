#include "visitor.h"

Function* Visitor::getint_func = new Function("getint", new FunctionType(&IR_INT, std::vector<ValueType*>()));
Function* Visitor::getchar_func = new Function("getchar", new FunctionType(&IR_CHAR, std::vector<ValueType*>()));
Function* Visitor::putint_func = new Function("putint", new FunctionType(&IR_VOID, std::vector<ValueType*>{&IR_INT}));
Function* Visitor::putch_func = new Function("putch", new FunctionType(&IR_VOID, std::vector<ValueType*>{&IR_CHAR}));
Function* Visitor::putstr_func = new Function("putstr", new FunctionType(&IR_VOID, std::vector<ValueType*>{new PointerType(&IR_CHAR)}));

Visitor::Visitor() {
    cur_scope = std::make_shared<SymbolTable>();
    loop_cnt = 0;
    is_void_func= false;
    scope_cnt = 1; // global
    symbol_list = std::deque<Symbol>();
    cur_ir_function = nullptr;
    cur_ir_basic_block = nullptr;
    cur_ir_lval = nullptr;
    if_stack = std::deque<BasicBlock*>();
    if_true_block = nullptr;
    if_false_block = nullptr;
    for_stack = std::deque<BasicBlock*>();
}


void Visitor::visit(const CompUnit &comp_unit) {
    for (const auto & decl : comp_unit.decls) {
        visit_decl(*decl);
    }
    for (const auto & func_def : comp_unit.func_defs) {
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
    ExpInfo exp_info;
    std::shared_ptr<Symbol> symbol = nullptr;
    if (!const_def.const_exp) { // constant
        SymbolType type = SymbolType(true, btype);
        symbol = std::make_shared<Symbol>(type, ident, cur_scope->get_scope());
        if (auto constant = std::get_if<ConstExp>(&(*const_def.const_init_val))) {
            exp_info = visit_constexp(*constant);
            if (btype == Token::CHARTK) {
                symbol->char_value = exp_info.char_value;
            } else if (btype == Token::INTTK) {
                symbol->int_value = exp_info.int_value;
            }
        } else {
            std::cout << "Invalid Const Initval!" << std::endl;
        }
    } else { // array
        exp_info = visit_constexp(*const_def.const_exp); // array size
        int array_size = exp_info.int_value;
        SymbolType type = SymbolType(true, btype, array_size);
        symbol = std::make_shared<Symbol>(type, ident, cur_scope->get_scope());
        ValueType* ir_element_type; // base is valuetype; base pointer to son
        if (btype == Token::CHARTK) ir_element_type = &IR_CHAR;
        else if (btype == Token::INTTK) ir_element_type = &IR_INT;
        auto array_type = new ArrayType(ir_element_type, array_size);
        if (this->cur_scope->is_in_global_scope()) {
            // '{' [ ConstExp { ',' ConstExp } ] '}' | StringConst
            GlobalVariable* global_variable = nullptr;
            if (auto const_exps_ptr = std::get_if<ConstExps>(&(*const_def.const_init_val))) {
                if (btype == Token::CHARTK) {
                    for (const auto &const_exp : const_exps_ptr->const_exps) {
                        exp_info = visit_constexp(*const_exp);
                        symbol->char_values.push_back(exp_info.char_value);
                    }
                    global_variable = new GlobalVariable(ident, array_type, symbol->char_values);
                    symbol->ir_value = global_variable;
                    Module::get_instance().global_variables.push_back(global_variable);
                } else {
                    for (const auto &const_exp : const_exps_ptr->const_exps) {
                        exp_info = visit_constexp(*const_exp);
                        symbol->int_values.push_back(exp_info.int_value);
                    }
                    global_variable = new GlobalVariable(ident, array_type, symbol->int_values);
                    symbol->ir_value = global_variable;
                    Module::get_instance().global_variables.push_back(global_variable);
                }
            } else if (auto string_const_ptr = std::get_if<StringConst>(&(*const_def.const_init_val))) {
                symbol->string_value = string_const_ptr->str->get_token();
                global_variable = new GlobalVariable(ident, array_type, symbol->string_value);
                symbol->ir_value = global_variable;
                Module::get_instance().global_variables.push_back(global_variable);
            } else {
                std::cout << "Invalid Const Array Initval!" << std::endl;
            }
        } else {
            auto alloc_instr = new AllocaInstr(Utils::get_next_counter(), array_type);
            symbol->ir_value = alloc_instr;
            cur_ir_basic_block->instrs.push_back(alloc_instr);
            if (auto const_exps_ptr = std::get_if<ConstExps>(&(*const_def.const_init_val))) {
                for (int i = 0; i < const_exps_ptr->const_exps.size(); i++) {
                    auto index = std::vector<Value*>{new IntConst(i)};
                    PointerType* pointer_type = nullptr;
                    if (btype == Token::CHARTK) pointer_type = new PointerType(&IR_CHAR);
                    else pointer_type = new PointerType(&IR_INT);
                    auto getelementptr_instr = new GetelementptrInstr(Utils::get_next_counter(), pointer_type, alloc_instr, index);
                    cur_ir_basic_block->instrs.push_back(getelementptr_instr);
                    ExpInfo exp_info = visit_constexp(*const_exps_ptr->const_exps[i]);
                    auto store_instr = new StoreInstr(exp_info.ir_value, getelementptr_instr);
                    cur_ir_basic_block->instrs.push_back(store_instr);
                }
            } else { //局部字符数组则也需要通过 alloca 指令分配内存空间，逐个元素初始化
                auto string_const_ptr = std::get_if<StringConst>(&(*const_def.const_init_val));
                auto string_const = string_const_ptr->str->get_token();
                for (int i = 0; i < string_const.length(); i++) { 
                    auto pointer_type = PointerType(&IR_CHAR);
                    auto index = std::vector<Value*>{new IntConst(i)};
                    auto getelementptr_instr = new GetelementptrInstr(Utils::get_next_counter(), &pointer_type, alloc_instr, index);
                    cur_ir_basic_block->instrs.push_back(getelementptr_instr);
                    auto store_instr = new StoreInstr(new CharConst(string_const[i]), getelementptr_instr);
                    cur_ir_basic_block->instrs.push_back(store_instr);
                }
            }
        }
    }
    symbol_list.push_back(*symbol);
    if (!cur_scope->add_symbol(symbol)) { // b error : redefined identifier
        ErrorList::report_error(line_number, 'b');
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
    ExpInfo exp_info;
    std::shared_ptr<Symbol> symbol = nullptr;
    if (!var_def.const_exp) { // variant
        SymbolType type = SymbolType(false, btype);
        symbol = std::make_shared<Symbol>(type, ident, cur_scope->get_scope());
        if (cur_scope->is_in_global_scope()) {
            if (var_def.init_val) {
                if (auto exp_ptr = std::get_if<Exp>(&(*var_def.init_val))) {
                    exp_info = visit_exp(*exp_ptr);
                    if (btype == Token::CHARTK) {
                        symbol->char_value = exp_info.char_value;
                    } else if (btype == Token::INTTK) {
                        symbol->int_value = exp_info.int_value;
                    }
                } else {
                    std::cout << "Invalid Variable Initval!" << std::endl;
                }
            } // else 全局变量未初始化默认为0
            GlobalVariable* global_variable = nullptr;
            if (btype == Token::CHARTK) {
                global_variable = new GlobalVariable(ident, &IR_CHAR, (var_def.init_val) ? symbol->char_value : 0);
            } else if (btype == Token::INTTK) {
                global_variable = new GlobalVariable(ident, &IR_INT, (var_def.init_val) ? symbol->int_value : 0);
            }
            symbol->ir_value = global_variable;
            Module::get_instance().global_variables.push_back(global_variable);
        } else { // 局部变量未初始化就是不store
            ValueType* type = nullptr;
            if (btype == Token::CHARTK) type = &IR_CHAR;
            else if (btype == Token::INTTK) type = &IR_INT;
            auto alloc_instr = new AllocaInstr(Utils::get_next_counter(), type);
            symbol->ir_value = alloc_instr;
            cur_ir_basic_block->instrs.push_back(alloc_instr);
            if (var_def.init_val) {
                if (auto exp_ptr = std::get_if<Exp>(&(*var_def.init_val))) {
                    exp_info = visit_exp(*exp_ptr);
                    auto store_instr = new StoreInstr(exp_info.ir_value, alloc_instr);
                    cur_ir_basic_block->instrs.push_back(store_instr);
                } else {
                    std::cout << "Invalid Variable Initval!" << std::endl;
                }
            }
        }
    } else { // array
        //'{' [ Exp { ',' Exp } ] '}' | StringConst
        exp_info = visit_constexp(*var_def.const_exp);
        int array_size = exp_info.int_value;
        SymbolType type = SymbolType(false, btype, array_size);
        symbol  = std::make_shared<Symbol>(type, ident, cur_scope->get_scope());
        ValueType* ir_element_type = nullptr;
        if (btype == Token::CHARTK) ir_element_type = &IR_CHAR;
        else if (btype == Token::INTTK) ir_element_type = &IR_INT;
        auto array_type = new ArrayType(ir_element_type, array_size);
        if (cur_scope->is_in_global_scope()) {
            GlobalVariable* global_variable = nullptr;
            if (var_def.init_val) {
                if (auto exps_ptr = std::get_if<Exps>(&(*var_def.init_val))) {
                    if (btype == Token::CHARTK) {
                        for (const auto &exp : exps_ptr->exps) {
                            exp_info = visit_exp(*exp);
                            symbol->char_values.push_back(exp_info.char_value);
                        }
                    } else if (btype == Token::INTTK) {
                        for (const auto &exp : exps_ptr->exps) {
                            exp_info = visit_exp(*exp);
                            symbol->int_values.push_back(exp_info.int_value);
                        }
                    }
                    if (btype == Token::CHARTK) global_variable = new GlobalVariable(ident, array_type, symbol->char_values);
                    else global_variable = new GlobalVariable(ident, array_type, symbol->int_values);
                    symbol->ir_value = global_variable;
                    Module::get_instance().global_variables.push_back(global_variable);
                } else {
                    auto string_const_ptr = std::get_if<StringConst>(&(*var_def.init_val));
                    global_variable = new GlobalVariable(ident, array_type, string_const_ptr->str->get_token());
                    symbol->ir_value = global_variable;
                    Module::get_instance().global_variables.push_back(global_variable);
                }
            } // else 全局字符数组未初始化默认为"", 全局整型数组默认为0
        } else {
            auto alloc_instr = new AllocaInstr(Utils::get_next_counter(), array_type);
            symbol->ir_value = alloc_instr;
            cur_ir_basic_block->instrs.push_back(alloc_instr);
            if (var_def.init_val) {
                if (auto exps_ptr = std::get_if<Exps>(&(*var_def.init_val))) {
                    for (int i = 0; i < exps_ptr->exps.size(); i++) {
                        auto index = std::vector<Value*>{new IntConst(i)};
                        PointerType* pointer_type = nullptr;
                        if (btype == Token::CHARTK) pointer_type = new PointerType(&IR_CHAR);
                        else pointer_type = new PointerType(&IR_INT);
                        auto getelementptr_instr = new GetelementptrInstr(Utils::get_next_counter(), pointer_type, alloc_instr, index);
                        cur_ir_basic_block->instrs.push_back(getelementptr_instr);
                        exp_info = visit_exp(*exps_ptr->exps[i]);
                        auto store_instr = new StoreInstr(exp_info.ir_value, getelementptr_instr);
                        cur_ir_basic_block->instrs.push_back(store_instr);
                    }
                } else { // stringconst
                    auto string_const_ptr = std::get_if<StringConst>(&(*var_def.init_val));
                    auto string_const = string_const_ptr->str->get_token();
                    for (int i = 0; i < string_const.length(); i++) {
                        auto pointer_type = new PointerType(&IR_CHAR);
                        auto index = std::vector<Value*>{new IntConst(i)};
                        auto getelementptr_instr = new GetelementptrInstr(Utils::get_next_counter(), pointer_type, alloc_instr, index);
                        cur_ir_basic_block->instrs.push_back(getelementptr_instr);
                        auto store_instr = new StoreInstr(new CharConst(string_const[i]), getelementptr_instr);
                        cur_ir_basic_block->instrs.push_back(store_instr);
                    }
                }
            } // else 没有初始化则不store
        }
    }
    symbol_list.push_back(*symbol);
    if (!cur_scope->add_symbol(symbol)) {
        ErrorList::report_error(line_number, 'b');
    }
}

void Visitor::visit_func_def(const FuncDef &func_def) {
    Token::TokenType func_type = func_def.func_type->func_type->get_type();
    this->is_void_func = (func_type == Token::VOIDTK);
    int line_number = func_def.func_type->func_type->get_line_number();
    std::string ident = func_def.ident->ident->get_token();
    std::deque<Symbol> params; // 记录参数类型 e error
    SymbolType type = SymbolType(func_type, params);
    auto func_symbol = std::make_shared<Symbol>(type, ident, cur_scope->get_scope());
    symbol_list.push_back(*func_symbol);
    if (!cur_scope->add_symbol(func_symbol)) {
        ErrorList::report_error(line_number, 'b');
    }
    cur_scope = cur_scope->push_scope();
    scope_cnt++;
    cur_scope->set_scope(scope_cnt);
    Utils::reset_counter(); // 进入新的函数作用域，重置计数器，从0开始编号虚拟寄存器
    std::vector<ValueType*> ir_param_types = std::vector<ValueType*>();
    if (func_def.func_fparams) {
        for (const auto &func_fparam : func_def.func_fparams->func_fparams) {
            Token::TokenType param_type = func_fparam->btype->btype->get_type();
            std::string param_ident = func_fparam->ident->ident->get_token();
            ValueType* ir_param_type = nullptr;
            SymbolType param_symbol_type = SymbolType();
            if (func_fparam->is_array) {
                param_symbol_type = SymbolType(false, param_type, -1); // 形参不必解析数组大小(后面有检查是否为形参数组的方法)
                if (param_type == Token::CHARTK) ir_param_type = new PointerType(&IR_CHAR);
                else ir_param_type = new PointerType(&IR_INT);
            } else {
                param_symbol_type = SymbolType(false, param_type);
                if (param_type == Token::CHARTK) ir_param_type = &IR_CHAR;
                else ir_param_type = &IR_INT;
            }
            auto param_symbol = std::make_shared<Symbol>(param_symbol_type, param_ident, cur_scope->get_scope());
            if (!cur_scope->add_symbol(param_symbol)) {
                ErrorList::report_error(func_fparam->ident->ident->get_line_number(), 'b');
            } else {
                func_symbol->type.params.push_back(*param_symbol);
                ir_param_types.push_back(ir_param_type);
                symbol_list.push_back(*param_symbol);
            }
        }
    }
    ValueType* ir_return_type = nullptr;
    if (func_type == Token::VOIDTK) ir_return_type = &IR_VOID;
    else if (func_type == Token::CHARTK) ir_return_type = &IR_CHAR;
    else if (func_type == Token::INTTK) ir_return_type = &IR_INT;
    FunctionType* ir_func_type = new FunctionType(ir_return_type, ir_param_types);
    cur_ir_function = new Function(func_symbol->name, ir_func_type);
    func_symbol->ir_value = cur_ir_function;
    cur_ir_basic_block = new BasicBlock(Utils::get_next_counter());
    cur_ir_function->basic_blocks.push_back(cur_ir_basic_block);
    if (func_def.func_fparams) {
        prepare_ir_funcparam_stack(*func_def.func_fparams);
    }
    visit_block(*func_def.block);
    cur_scope = cur_scope->pop_scope();
    bool has_ending_return = func_block_has_ending_return(*func_def.block);
    if ((!is_void_func) &&  (!has_ending_return)) {
        ErrorList::report_error(func_def.block->ending_line, 'g');
    } else if (is_void_func && (!has_ending_return)) { // 没有return语句的void函数，自动添加return
        cur_ir_basic_block->instrs.push_back(new RetInstr());
    }
    Module::get_instance().functions.push_back(cur_ir_function);
}

// 函数参数压栈
void Visitor::prepare_ir_funcparam_stack(const FuncFParams &funcfparams) { 
    auto ir_params = cur_ir_function->fparams;
    std::vector<Instruction*> instr_alloc_stack = std::vector<Instruction*>(); // 记录alloca指令 用于后续store
    for (int i = 0; i < funcfparams.func_fparams.size(); i++) {
        auto alloc_instr = new AllocaInstr(Utils::get_next_counter(), ir_params[i]->type);
        cur_scope->get_symbol(funcfparams.func_fparams[i]->ident->ident->get_token())->ir_value = alloc_instr;
        cur_ir_basic_block->instrs.push_back(alloc_instr);
        instr_alloc_stack.push_back(alloc_instr);
    }

    for (int i = 0; i < ir_params.size(); i++) {
        auto store_instr = new StoreInstr(ir_params[i], instr_alloc_stack[i]);
        cur_ir_basic_block->instrs.push_back(store_instr);
    }
}

void Visitor::visit_main_func(const MainFunc &main_func) {
    Token::TokenType func_type = Token::INTTK;
    this->is_void_func = false;
    std::string ident = "main";
    SymbolType type = SymbolType(func_type, std::deque<Symbol>());
    auto func_symbol = std::make_shared<Symbol>(type, ident, cur_scope->get_scope());
    symbol_list.push_back(*func_symbol);
    cur_scope->add_symbol(func_symbol); // main函数不会发生b错误
    Utils::reset_counter();
    cur_scope = cur_scope->push_scope();
    auto function_type = new FunctionType(&IR_INT, std::vector<ValueType*>());
    cur_ir_function = new Function(ident, function_type);
    func_symbol->ir_value = cur_ir_function;
    cur_ir_basic_block = new BasicBlock(Utils::get_next_counter());
    cur_ir_function->basic_blocks.push_back(cur_ir_basic_block);
    this->scope_cnt++;
    cur_scope->set_scope(scope_cnt);
    visit_block(*main_func.block);
    cur_scope = cur_scope->pop_scope();
    if (!func_block_has_ending_return(*main_func.block)) {
        ErrorList::report_error(main_func.block->ending_line, 'g');
    }
    Module::get_instance().functions.push_back(cur_ir_function);
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
    ExpInfo exp_info;
    auto lval_symbol = visit_lval((*assign_stmt.lval));
    if (lval_symbol) {
        if (lval_symbol->type.is_const) {
            ErrorList::report_error(assign_stmt.lval->ident->ident->get_line_number(), 'h');
        } else {
            exp_info = visit_exp(*assign_stmt.exp);
            auto store_instr = new StoreInstr(exp_info.ir_value, lval_symbol->ir_value);
            cur_ir_basic_block->instrs.push_back(store_instr);
        }
    }
}

void Visitor::visit_for_assign_stmt(const ForAssignStmt &for_assign_stmt) {
    ExpInfo exp_info;
    auto lval_symbol = visit_lval((*for_assign_stmt.lval));
    if (lval_symbol) {
        if (lval_symbol->type.is_const) {
            ErrorList::report_error(for_assign_stmt.lval->ident->ident->get_line_number(), 'h');
        } else {
            exp_info = visit_exp(*for_assign_stmt.exp);
            auto store_instr = new StoreInstr(exp_info.ir_value, lval_symbol->ir_value);
            cur_ir_basic_block->instrs.push_back(store_instr);
        }
    }
}

void Visitor::visit_exp_stmt(const ExpStmt &exp) {
    if (exp.exp) visit_exp(*exp.exp);
}

void Visitor::visit_block_stmt(const BlockStmt &block_stmt) {
    cur_scope = cur_scope->push_scope();
    this->scope_cnt++;
    cur_scope->set_scope(scope_cnt);
    visit_block(*block_stmt.block);
    cur_scope = cur_scope->pop_scope();
}

//! 注意这里一定要使用pop_back()弹出所有basicblock, 保证if_stack为空
void Visitor::visit_if_stmt(const IfStmt &if_stmt) {
    // if basicblock stack
    if_stack.push_back(new BasicBlock(-1)); // next normal block
    if (if_stmt.else_stmt) if_stack.push_back(new BasicBlock(-1)); // else block if exists
    if_stack.push_back(new BasicBlock(-1)); // if block
    if_true_block = if_stack.back();
    if_false_block = if_stack[if_stack.size() - 2]; // 这里没法给出一个确定的index 因为可能是else block/normal block
    visit_cond(*if_stmt.condition);
    cur_ir_basic_block = if_stack.back();
    cur_ir_basic_block->id = Utils::get_next_counter();
    if_stack.pop_back();
    cur_ir_function->basic_blocks.push_back(cur_ir_basic_block);
    visit_stmt(*if_stmt.if_stmt);
    cur_ir_basic_block->instrs.push_back(new BrInstr(if_stack[0])); // jump to next normal block 这里是确定的
    if (if_stmt.else_stmt) {
        cur_ir_basic_block = if_stack.back();
        if_stack.pop_back();
        cur_ir_basic_block->id = Utils::get_next_counter();
        cur_ir_function->basic_blocks.push_back(cur_ir_basic_block);
        visit_stmt(*if_stmt.else_stmt);
        cur_ir_basic_block->instrs.push_back(new BrInstr(if_stack[0])); // jump to next normal block
    }
    cur_ir_basic_block = if_stack[0];
    cur_ir_basic_block->id = Utils::get_next_counter();
    cur_ir_function->basic_blocks.push_back(cur_ir_basic_block);
    if_stack.pop_back();
}

void Visitor::visit_for_stmt(const ForStmt &for_stmt) {
    if (for_stmt.assign1) visit_for_assign_stmt(*for_stmt.assign1);
    for_stack.push_back(new BasicBlock(-1)); // condition block
    cur_ir_basic_block->instrs.push_back(new BrInstr(for_stack.back())); // jump to condition block
    cur_ir_basic_block = for_stack.back();
    cur_ir_basic_block->id = Utils::get_next_counter();
    cur_ir_function->basic_blocks.push_back(cur_ir_basic_block);
    if (for_stmt.assign2) for_stack.push_back(new BasicBlock(-1)); // assign2 block
    for_stack.push_back(new BasicBlock(-1)); // stmt block
    for_stack.push_back(new BasicBlock(-1)); // next normal block
    if_true_block = for_stack[for_stack.size() - 2]; // stmt block
    if_false_block = for_stack.back(); // next normal block
    if (for_stmt.condition) {
        visit_cond(*for_stmt.condition);
    } else {
        cur_ir_basic_block->instrs.push_back(new BrInstr(if_true_block)); // jump to stmt block
    }
    cur_ir_basic_block = if_true_block;
    cur_ir_basic_block->id = Utils::get_next_counter();
    cur_ir_function->basic_blocks.push_back(cur_ir_basic_block);
    this->loop_cnt++;
    visit_stmt(*for_stmt.stmt);
    cur_ir_basic_block->instrs.push_back(new BrInstr(for_stack[for_stack.size() - 3])); 
    this->loop_cnt--;
    if (for_stmt.assign2) {
        cur_ir_basic_block = for_stack[1];
        cur_ir_basic_block->id = Utils::get_next_counter();
        cur_ir_function->basic_blocks.push_back(cur_ir_basic_block);
        visit_for_assign_stmt(*for_stmt.assign2);
        cur_ir_basic_block->instrs.push_back(new BrInstr(for_stack[0])); // jump to condition block
    }
    cur_ir_basic_block = for_stack.back();
    cur_ir_basic_block->id = Utils::get_next_counter();
    cur_ir_function->basic_blocks.push_back(cur_ir_basic_block);
    for_stack.clear(); 
}

void Visitor::visit_break_stmt(const BreakStmt &break_stmt) {
    if (this->loop_cnt == 0) {
        ErrorList::report_error(break_stmt.break_token->get_line_number(), 'm');
    } else {
        cur_ir_basic_block->instrs.push_back(new BrInstr(for_stack.back())); // jump to next normal block
    }
}

void Visitor::visit_continue_stmt(const ContinueStmt &continue_stmt) {
    if (this->loop_cnt == 0) {
        ErrorList::report_error(continue_stmt.continue_token->get_line_number(), 'm');
    } else {
        cur_ir_basic_block->instrs.push_back(new BrInstr(for_stack[for_stack.size() - 3])); // cond block or assign2 block
    }
}

void Visitor::visit_return_stmt(const ReturnStmt &return_stmt) {
    if (return_stmt.return_exp) {
        if(this->is_void_func) {
            ErrorList::report_error(return_stmt.return_token->get_line_number(), 'f');
        } else {
            ExpInfo exp_info = visit_exp(*return_stmt.return_exp);
            cur_ir_basic_block->instrs.push_back(new RetInstr(exp_info.ir_value));
        }
    } else {
        cur_ir_basic_block->instrs.push_back(new RetInstr());
    }
}

void Visitor::visit_get_int_stmt(const GetIntStmt &get_int_stmt) {
    auto lval_symbol = visit_lval(*get_int_stmt.lval);
    if (lval_symbol) {
        if (lval_symbol->type.is_const) {
            ErrorList::report_error(get_int_stmt.lval->ident->ident->get_line_number(), 'h');
        } else {
            auto lval = cur_ir_lval;
            auto call_instr = new CallInstr(Utils::get_next_counter(), &IR_INT, getint_func, std::vector<Value*>{});
            cur_ir_basic_block->instrs.push_back(call_instr);
        }
    }
}

void Visitor::visit_get_char_stmt(const GetCharStmt &get_char_stmt) {
    auto lval_symbol = visit_lval(*get_char_stmt.lval);
    if (lval_symbol) {
        if (lval_symbol->type.is_const) {
            ErrorList::report_error(get_char_stmt.lval->ident->ident->get_line_number(), 'h');
        } else {
            auto lval = cur_ir_lval;
            auto call_instr = new CallInstr(Utils::get_next_counter(), &IR_CHAR, getchar_func, std::vector<Value*>{});
            cur_ir_basic_block->instrs.push_back(call_instr);
        }
    }
}


// 目前没有用putstr, 使用多个putch代替
// void Visitor::visit_printf_stmt(const PrintfStmt &printf_stmt) {
//     int cnt = control_cnt(printf_stmt.str->str->get_token());
//     if (cnt != printf_stmt.exps.size()) {
//         ErrorList::report_error(printf_stmt.str->str->get_line_number(), 'l');
//     } else {
//         std::vector<ExpInfo> exp_infos;
//         for (const auto &exp : printf_stmt.exps) {
//             exp_infos.push_back(visit_exp(*exp));
//             std::string format_str = printf_stmt.str->str->get_token();
//             int pos = 0;
//             for (int i = 0; i < format_str.length() && pos < exp_infos.size(); ) {
//                 if (format_str[i] == '%' && i + 1 < format_str.length() && format_str[i + 1] == 'd') {
//                     auto call_instr = new CallInstr(Utils::get_next_counter(), putint, std::vector<Value*>{exp_infos[pos++].ir_value});
//                     cur_ir_basic_block->instrs.push_back(call_instr);
//                     i += 2;
//                 } else if (format_str[i] == '%' && i + 1 < format_str.length() && format_str[i + 1] == 'c') {
//                     auto call_instr = new CallInstr(Utils::get_next_counter(), putchar, std::vector<Value*>{exp_infos[pos++].ir_value});
//                     cur_ir_basic_block->instrs.push_back(call_instr);
//                     i += 2;
//                 } else if (format_str[i] == '\\') { // printf中转义字符只会有\n
//                     auto call_instr = new CallInstr(Utils::get_next_counter(), putchar, std::vector<Value*>{new CharConst('\n')});
//                     cur_ir_basic_block->instrs.push_back(call_instr);
//                     i += 2;
//                 } else {
//                     auto call_instr = new CallInstr(Utils::get_next_counter(), putchar, std::vector<Value*>{new CharConst(format_str[i])});
//                     cur_ir_basic_block->instrs.push_back(call_instr);
//                     i++;
//                 }
//             }
//         }
//     }
// }

void Visitor::visit_printf_stmt(const PrintfStmt &printf_stmt) {
    int cnt = Utils::control_cnt(printf_stmt.str->str->get_token());
    if (cnt != printf_stmt.exps.size()) {
        ErrorList::report_error(printf_stmt.str->str->get_line_number(), 'l');
    } else {
        std::vector<ExpInfo> exp_infos;
        for (const auto &exp : printf_stmt.exps) {
            exp_infos.push_back(visit_exp(*exp));
        }
        std::string format_str = printf_stmt.str->str->get_token();
        int pos = 0, i = 1;
        while (i < format_str.length() - 1) {
            int str_end = Utils::cut_str(format_str, i);
            if (str_end == i) { // %d | %c | \n
                CallInstr* call_instr = nullptr;
                if (format_str[i] == '\\')
                    call_instr = new CallInstr(putch_func, std::vector<Value*>{new IntConst('\n')});
                else if (format_str[i + 1] == 'd') 
                    call_instr = new CallInstr(putint_func, std::vector<Value*>{exp_infos[pos++].ir_value});
                else if (format_str[i + 1] == 'c') 
                    call_instr = new CallInstr(putch_func, std::vector<Value*>{exp_infos[pos++].ir_value});
                cur_ir_basic_block->instrs.push_back(call_instr);
                i += 2;
            } else if (str_end == i + 1) { // single char
                CallInstr* call_instr = new CallInstr(putch_func, std::vector<Value*>{new IntConst(format_str[i])});
                cur_ir_basic_block->instrs.push_back(call_instr);
                i += 1;
            } else { // global variable
                int length = str_end - i;
                int global_var_id = Utils::get_next_str_cnt();
                std::string global_var_name = "dqr" + std::to_string(global_var_id);
                std::string global_var_value = format_str.substr(i, length);
                auto global_var_type = new ArrayType(&IR_CHAR, length + 1);
                auto *global_var = new GlobalVariable(global_var_name, global_var_type, global_var_value);
                Module::get_instance().global_variables.push_back(global_var);
                std::vector<Value*> indices = std::vector<Value*>();
                // 这里的全局变量是一个一维数组指针, 需要两个index
                indices.push_back(new IntConst(0));
                indices.push_back(new IntConst(0));
                auto getelementptr_instr = new GetelementptrInstr(Utils::get_next_counter(), new PointerType(&IR_CHAR), global_var, indices);
                cur_ir_basic_block->instrs.push_back(getelementptr_instr);
                auto call_instr = new CallInstr(putstr_func, std::vector<Value*>{getelementptr_instr});
                cur_ir_basic_block->instrs.push_back(call_instr);
                i += length; 
            }
        }
    }
}


std::shared_ptr<Symbol> Visitor::visit_lval(const LVal &lval) {
    auto ident = lval.ident->ident->get_token();
    auto ident_symbol = cur_scope->get_symbol(ident);
    if (!ident_symbol) { // c error : undefined identifier
        ErrorList::report_error(lval.ident->ident->get_line_number(), 'c');
        cur_ir_lval = nullptr;
        return nullptr;
    }
    if (ident_symbol->type.is_array) {
        Value* array = nullptr;
        if (ident_symbol->type.is_param_array()) { //TODO: 参数数组需要load, but WHY?
            auto load_instr = new LoadInstr(Utils::get_next_counter(), ident_symbol->ir_value); 
            cur_ir_basic_block->instrs.push_back(load_instr);
            array = load_instr;
        } else {
            array = ident_symbol->ir_value;
        }
        if (lval.exp) {
            ExpInfo exp_info = visit_exp(*lval.exp);
            auto index = std::vector<Value*>{new IntConst(exp_info.int_value)};
            auto pointer_type = new PointerType(array->type);
            auto getelementptr_instr = new GetelementptrInstr(Utils::get_next_counter(), pointer_type, array, index);
            cur_ir_basic_block->instrs.push_back(getelementptr_instr);
            cur_ir_lval = getelementptr_instr;
        } else {
            cur_ir_lval = array;
        }
    } else {
        if (ident_symbol->type.is_const) {
            if (ident_symbol->type.btype == Token::CHARTK) {
                cur_ir_lval = new CharConst(ident_symbol->char_value);
            } else if (ident_symbol->type.btype == Token::INTTK) {
                cur_ir_lval = new IntConst(ident_symbol->int_value);
            }
        } else {
            cur_ir_lval = ident_symbol->ir_value;
        }
    }
    // if (lval.exp) {
    //     visit_exp(*lval.exp);
    //     SymbolType type = SymbolType(ident_symbol->type.is_const, ident_symbol->type.btype);
    //     return std::make_shared<Symbol>(type, ident, cur_scope->get_scope());
    // } else {
    //     return ident_symbol;
    // }
    return ident_symbol;
}

ExpInfo Visitor::visit_exp(const Exp &exp) {
    return visit_add_exp(*exp.add_exp);
}

ExpInfo Visitor::visit_constexp(const ConstExp &const_exp) {
    return visit_add_exp(*const_exp.add_exp);
}

ExpInfo Visitor::visit_add_exp(const AddExp &add_exp) {
    if (!add_exp.op) { // Add -> Mul
        return visit_mul_exp(*add_exp.mulexp);
    } else { // Add -> Mul {+/- Mul}
        ExpInfo info1 = visit_add_exp(*add_exp.addexp);
        ExpInfo info2 = visit_mul_exp(*add_exp.mulexp);
        if (info1.is_const && info2.is_const) { // constant optimization
            if (add_exp.op->get_type() == Token::PLUS)
                return {false, false, info1.int_value + info2.int_value, Token::INTTK};
            else
                return {false, false, info1.int_value - info2.int_value, Token::INTTK};
        } else {
            Value* instr = nullptr;
            if (add_exp.op->get_type() == Token::PLUS && info1.is_const && info1.int_value == 0) { // 0 + info2
                instr = info2.ir_value;
            } else if (info2.is_const && info2.int_value == 0) { // info1 +/- 0
                instr = info1.ir_value;
            } else {
                if (add_exp.op->get_type() == Token::PLUS) {
                    instr = new ArithmeticInstr(Utils::get_next_counter(), ArithmeticInstr::ADD, info1.ir_value, info2.ir_value);
                } else {
                    instr = new ArithmeticInstr(Utils::get_next_counter(), ArithmeticInstr::SUB, info1.ir_value, info2.ir_value);
                }
                cur_ir_basic_block->instrs.push_back(dynamic_cast<Instruction*>(instr));
            }
            return {false, false, Token::INTTK, instr};
        }
    }
}

ExpInfo Visitor::visit_mul_exp(const MulExp &mul_exp) {
    if (!mul_exp.op) { // Mul -> Unary
        return visit_unary_exp(*mul_exp.unaryexp);
    } else { // Mul -> Unary {*/% Unary}
        ExpInfo info1 = visit_mul_exp(*mul_exp.mulexp);
        ExpInfo info2 = visit_unary_exp(*mul_exp.unaryexp);
        if (info1.is_const && info2.is_const) { // constant optimization
            if (mul_exp.op->get_type() == Token::MULT) {
                return {false, false, info1.int_value * info2.int_value, Token::INTTK};
            } else if (mul_exp.op->get_type() == Token::DIV) {
                return {false, false, info1.int_value / info2.int_value, Token::INTTK};
            } else {
                return {false, false, info1.int_value % info2.int_value, Token::INTTK};
            }
        } else {
            Value* instr = nullptr;
            if (info1.is_const && info1.int_value == 0) { // 0 *|/|% info2
                return {false, false, 0, Token::INTTK};
            } else if (mul_exp.op->get_type() == Token::MULT && info1.is_const && info1.int_value == 1) { // 1 * info2
                instr = info2.ir_value;
            } else if (mul_exp.op->get_type() == Token::DIV && info2.is_const && info2.int_value == 1) { // info1 / 1
                instr = info1.ir_value;
            } else if (mul_exp.op->get_type() == Token::MULT && info2.is_const && info2.int_value == 1) { // info1 * 1
                instr = info1.ir_value;
            } else if (mul_exp.op->get_type() == Token::MOD && info2.is_const && info2.int_value == 1) { // info1 % 1
                return {false, false, 0, Token::INTTK};
            } else {
                if (mul_exp.op->get_type() == Token::MULT) {
                    instr = new ArithmeticInstr(Utils::get_next_counter(), ArithmeticInstr::MUL, info1.ir_value, info2.ir_value);
                } else if (mul_exp.op->get_type() == Token::DIV) {
                    instr = new ArithmeticInstr(Utils::get_next_counter(), ArithmeticInstr::SDIV, info1.ir_value, info2.ir_value);
                } else {
                    instr = new ArithmeticInstr(Utils::get_next_counter(), ArithmeticInstr::SREM, info1.ir_value, info2.ir_value);
                }
                cur_ir_basic_block->instrs.push_back(dynamic_cast<Instruction*>(instr));
            }
            return {false, false, Token::INTTK, instr};
        }
    }
}

ExpInfo Visitor::visit_unary_exp(const UnaryExp &unary_exp) { // c d e
    if (unary_exp.primary_exp) { // primary exp
        return visit_primary_exp(*unary_exp.primary_exp);
    } else if (unary_exp.ident) { // ident()
        std::string ident = unary_exp.ident->ident->get_token();
        std::shared_ptr<Symbol> ident_symbol = cur_scope->get_symbol(ident);
        if (!ident_symbol) { // c error : undefined identifier
            ErrorList::report_error(unary_exp.ident->ident->get_line_number(), 'c');
            return ExpInfo(false, false, 0, Token::END);
        } else {
            std::vector<Value*> ir_rparams;
            if (unary_exp.func_rparams) {
                if (unary_exp.func_rparams->exps.size() != ident_symbol->type.params.size()) {
                    ErrorList::report_error(unary_exp.ident->ident->get_line_number(), 'd');
                    return ExpInfo(false, false, 0, Token::END);
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
                            ErrorList::report_error(unary_exp.ident->ident->get_line_number(), 'e');
                            return ExpInfo(false, false, 0, Token::END);
                        } else {
                            ir_rparams.push_back(r_param_info.ir_value);
                        }
                    }
                }
            } else if (!ident_symbol->type.params.empty()) {
                ErrorList::report_error(unary_exp.ident->ident->get_line_number(), 'd');
                return ExpInfo(false, false, 0, Token::END);
            }
            Instruction* call_instr = nullptr;
            if (is_void_func)
                call_instr = new CallInstr(dynamic_cast<Function*>(ident_symbol->ir_value), ir_rparams);
            else if (ident_symbol->type.btype == Token::INTTK)
                call_instr = new CallInstr(Utils::get_next_counter(), &IR_INT, dynamic_cast<Function*>(ident_symbol->ir_value), ir_rparams);
            else 
                call_instr = new CallInstr(Utils::get_next_counter(), &IR_CHAR, dynamic_cast<Function*>(ident_symbol->ir_value), ir_rparams);
            cur_ir_basic_block->instrs.push_back(call_instr);
            return ExpInfo(false, false, Token::INTTK, call_instr);
        }
    } else { // + - ! UnaryExp
        ExpInfo unary_info = visit_unary_exp(*unary_exp.unary_exp);
        if (unary_info.is_const) { // constant optimazation
            if ((*unary_exp.unary_op->op).get_type() == Token::PLUS) {
                return ExpInfo(false, false, unary_info.int_value, Token::INTTK);
            } else if ((*unary_exp.unary_op->op).get_type() == Token::MINU) {
                return ExpInfo(false, false, -unary_info.int_value, Token::INTTK);
            } else {
                return ExpInfo(false, false, !unary_info.int_value, Token::INTTK);
            }
        } else if ((*unary_exp.unary_op->op).get_type() == Token::PLUS) {
            return unary_info;
        } else if ((*unary_exp.unary_op->op).get_type() == Token::MINU) {
            auto instr = new ArithmeticInstr(Utils::get_next_counter(), ArithmeticInstr::SUB, new IntConst(0), unary_info.ir_value);
            cur_ir_basic_block->instrs.push_back(instr);
            return ExpInfo(false, false, Token::INTTK, instr);
        } else if ((*unary_exp.unary_op->op).get_type() == Token::NOT) {
            // 运算指令中没有 ! 操作, 首先使用icmp指令判断是否为0, 然后使用zext将结果转换为int
            auto icmp_instr = new IcmpInstr(Utils::get_next_counter(), IcmpInstr::EQ, unary_info.ir_value, new IntConst(0));
            cur_ir_basic_block->instrs.push_back(icmp_instr);
            auto zext_instr = new ZextInstr(Utils::get_next_counter(), icmp_instr, &IR_INT);
            cur_ir_basic_block->instrs.push_back(zext_instr);
            return ExpInfo(false, false, Token::INTTK, zext_instr);
        } else {
            std::cout << "Invalid operate in unary_exp" << std::endl;
            return ExpInfo(false, false, 0, Token::END);
        }
    }
}

ExpInfo Visitor::visit_primary_exp(const PrimaryExp &primary_exp) {
    if (auto exp_ptr = std::get_if<Exp>(&primary_exp)) {
        return visit_exp(*exp_ptr);
    } else if (auto num_ptr = std::get_if<Number>(&primary_exp)) {
        return ExpInfo(true, false, num_ptr->num->get_int(), Token::INTTK);
    } else if (auto char_ptr = std::get_if<Character>(&primary_exp)) {
        return ExpInfo(true, false, char_ptr->ch->get_char(), Token::CHARTK);
    } else if (auto lval_ptr = std::get_if<LVal>(&primary_exp)) {
        auto lval_symbol = visit_lval(*lval_ptr);
        if (lval_symbol) {
            if (auto intconst_ptr = dynamic_cast<IntConst*>(lval_symbol->ir_value)) {
                return ExpInfo(true, false, intconst_ptr->value, Token::INTTK);
            } else {
                if (lval_ptr->exp) { // int / char 
                    auto load_instr = new LoadInstr(Utils::get_next_counter(), lval_symbol->ir_value);
                    cur_ir_basic_block->instrs.push_back(load_instr);
                    return ExpInfo(false, false, Token::INTTK, load_instr);
                } else { // may be array
                    return ExpInfo(false, true, Token::INTTK, lval_symbol->ir_value);
                }
            }
        } else {
            std::cout << "Invalid LVal in PrimaryExp Variant" << std::endl;
            return ExpInfo(false, false, 0, Token::END);
        }
    } else {
        std::cout << "Invalid Type of PrimaryExp Variant" << std::endl;
        return ExpInfo(false, false, 0, Token::END);
    }
}

void Visitor::visit_cond(const Cond &cond) {
    visit_lor_exp(*cond.lor_exp);
}

void Visitor::visit_lor_exp(const LOrExp &lor_exp) {
    if (lor_exp.lorexp) { // short-circuit evaluation
        if_stack.push_back(if_false_block); // save the orginal if_false_block
        if_false_block = new BasicBlock(-1);
        visit_lor_exp(*lor_exp.lorexp);
        if_false_block->id = Utils::get_next_counter();
        cur_ir_basic_block = if_false_block;
        cur_ir_function->basic_blocks.push_back(if_false_block);
        if_false_block = if_stack.back();
        if_stack.pop_back();
    }
    visit_land_exp(*lor_exp.landexp);
}

void Visitor::visit_land_exp(const LAndExp &land_exp) {
    if (land_exp.landexp) {
        if_stack.push_back(if_true_block); // save the orginal if_true_block
        if_true_block = new BasicBlock(-1);
        visit_land_exp(*land_exp.landexp);
        if_true_block->id = Utils::get_next_counter();
        cur_ir_basic_block = if_true_block;
        cur_ir_function->basic_blocks.push_back(if_true_block);
        if_true_block = if_stack.back();
        if_stack.pop_back();
    }
    ExpInfo exp_info = visit_eq_exp(*land_exp.eqexp);
    if (exp_info.is_const) {
        if (exp_info.int_value == 0) cur_ir_basic_block->instrs.push_back(new BrInstr(if_false_block));
        else cur_ir_basic_block->instrs.push_back(new BrInstr(if_true_block));
    } else if (exp_info.is_bool) {
        cur_ir_basic_block->instrs.push_back(new BrInstr(exp_info.ir_value, if_true_block, if_false_block));
    } else { // int -> bool
        auto icmp_instr = new IcmpInstr(Utils::get_next_counter(), IcmpInstr::NE, exp_info.ir_value, new IntConst(0));
        cur_ir_basic_block->instrs.push_back(icmp_instr);
        cur_ir_basic_block->instrs.push_back(new BrInstr(icmp_instr, if_true_block, if_false_block));
    }
}

ExpInfo Visitor::visit_eq_exp(const EqExp &eq_exp) { // == !=
    ExpInfo expinfo1, expinfo2;
    if (!eq_exp.op) {
        return visit_rel_exp(*eq_exp.relexp);
    } else {
        expinfo1 = visit_eq_exp(*eq_exp.eqexp);
        expinfo2 = visit_rel_exp(*eq_exp.relexp);
    }
    if (expinfo1.is_const && expinfo2.is_const) {
        if (eq_exp.op->get_type() == Token::EQL)
            return {true, false, expinfo1.int_value == expinfo2.int_value, Token::INTTK};
        else
            return {true, false, expinfo1.int_value != expinfo2.int_value, Token::INTTK};
    } else {
        Instruction* instr = nullptr;
        if (!expinfo1.is_const && expinfo1.is_bool) {
            instr = new ZextInstr(Utils::get_next_counter(), expinfo1.ir_value, &IR_INT);
            cur_ir_basic_block->instrs.push_back(instr);
            expinfo1.ir_value = instr;
        }
        if (!expinfo2.is_const && expinfo2.is_bool) {
            instr = new ZextInstr(Utils::get_next_counter(), expinfo2.ir_value, &IR_INT);
            cur_ir_basic_block->instrs.push_back(instr);
            expinfo2.ir_value = instr;
        }
        instr = new IcmpInstr(Utils::get_next_counter(), (eq_exp.op->get_type() == Token::EQL) ? IcmpInstr::EQ : IcmpInstr::NE, expinfo1.ir_value, expinfo2.ir_value);
        cur_ir_basic_block->instrs.push_back(instr);
        return {false, false, Token::INTTK, instr};
    }
}

ExpInfo Visitor::visit_rel_exp(const RelExp &rel_exp) { // > < >= <=
    if (!rel_exp.op) {
        return visit_add_exp(*rel_exp.addexp);
    } else {
        ExpInfo expinfo1 = visit_rel_exp(*rel_exp.relexp);
        ExpInfo expinfo2 = visit_add_exp(*rel_exp.addexp);
        if (expinfo1.is_const && expinfo2.is_const) { // constant optimization
            switch (rel_exp.op->get_type()) {
                case Token::LSS:
                    return ExpInfo(true, false, expinfo1.int_value < expinfo2.int_value, Token::INTTK);
                    break;
                case Token::LEQ:
                    return ExpInfo(true, false, expinfo1.int_value <= expinfo2.int_value, Token::INTTK);
                    break;
                case Token::GRE:
                    return ExpInfo(true, false, expinfo1.int_value > expinfo2.int_value, Token::INTTK);
                    break;
                case Token::GEQ:
                    return ExpInfo(true, false, expinfo1.int_value >= expinfo2.int_value, Token::INTTK);
                    break;       
                default:
                    std::cout << "Invalid Operater in rel_exp" << std::endl;
                    return ExpInfo(false, false, 0, Token::END);
                    break;
            }
        } else {
            if (!expinfo1.is_const && expinfo1.is_bool) {
                auto instr = new ZextInstr(Utils::get_next_counter(), expinfo1.ir_value, &IR_INT);
                cur_ir_basic_block->instrs.push_back(instr);
                expinfo1.ir_value = instr;
            }
            Instruction* instr = nullptr;
            switch (rel_exp.op->get_type()) {
                case Token::LSS:
                    instr = new IcmpInstr(Utils::get_next_counter(), IcmpInstr::SLT, expinfo1.ir_value, expinfo2.ir_value);
                    break;
                case Token::LEQ:
                    instr = new IcmpInstr(Utils::get_next_counter(), IcmpInstr::SLE, expinfo1.ir_value, expinfo2.ir_value);
                    break;
                case Token::GRE:
                    instr = new IcmpInstr(Utils::get_next_counter(), IcmpInstr::SGT, expinfo1.ir_value, expinfo2.ir_value);
                    break;
                case Token::GEQ:
                    instr = new IcmpInstr(Utils::get_next_counter(), IcmpInstr::SGE, expinfo1.ir_value, expinfo2.ir_value);
                    break;        
                default:
                    break;
            }
            cur_ir_basic_block->instrs.push_back(instr);
            return ExpInfo(false, false, Token::INTTK, instr);
        }
    }
}

void Visitor::print_symbol_list() {
    // bubble_sort by scope_cnt
    std::ofstream symbol_out("symbol_list.txt", std::ios::trunc);
    for (int i = 0; i < symbol_list.size(); i++) {
        for (int j = 0; j < symbol_list.size() - i - 1; j++) {
            if (symbol_list[j].scope_cnt > symbol_list[j + 1].scope_cnt) {
                std::swap(symbol_list[j], symbol_list[j + 1]);
            }
        }
    }
    for (const auto &symbol : symbol_list) {
        symbol_out << symbol.scope_cnt << " " << symbol.name << " " << symbol.type.to_string() << std::endl;
    }
    symbol_out.close();
}