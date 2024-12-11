#include "mips_generate.h"
#include "mips_utils.h"

void MipsBackend::start_generate_mips_code(Module &module, Mode mode) {
    if (mode == NORMAL) generate_mips_code(module);
    else generate_optimized_mips_code(module);
}

void MipsBackend::generate_mips_code(Module &module) {
    for (auto &data : module.global_variables) {
        generate_mips_code(*data);
    }
    for (auto &function: module.functions) {
        generate_mips_code(*function);
    }
}

void MipsBackend::generate_mips_code(GlobalVariable &data) {
    auto deref_type = ((PointerType*)data.type)->referenced_type;
    if (data.is_printf_str) {
        auto asciiz_data = new AsciizData(data.name, data.array_string);
        manager->data_list.push_back(asciiz_data);
    } else {
        if (auto int_type = dynamic_cast<IntType*>(deref_type)) {
            auto word_data = new WordData(data.name, data.value, false);
            manager->data_list.push_back(word_data);
        } else if (auto char_type = dynamic_cast<CharType*>(deref_type)) {
            auto byte_data = new ByteData(data.name, data.value, false);
            manager->data_list.push_back(byte_data);
        } else if (auto array_type = dynamic_cast<ArrayType*>(deref_type)) {
            if (data.array_values.size() == 0 && data.array_string.length() == 0) {
                int array_size = array_type->size;
                if (auto int_type = dynamic_cast<IntType*>(array_type->element_type)) {
                    auto word_data = new WordData(data.name, array_size, true);
                    manager->data_list.push_back(word_data);
                } else if (auto char_type = dynamic_cast<CharType*>(array_type->element_type)) {
                    auto byte_data = new ByteData(data.name, array_size, true);
                    manager->data_list.push_back(byte_data);
                } else 
                    std::cout << "Invalid Type of Array Element!" << std::endl;
            } else if (data.array_string.length() != 0) {
                auto asciiz_data = new AsciizData(data.name, data.array_string);
                manager->data_list.push_back(asciiz_data);
            } else {
                auto array_size = array_type->size;
                if (auto int_type = dynamic_cast<IntType*>(array_type->element_type)) {
                    auto word_data = new WordData(data.name, data.array_values);
                    manager->data_list.push_back(word_data);
                } else if (auto char_type = dynamic_cast<CharType*>(array_type->element_type)) {
                    auto byte_data = new ByteData(data.name, data.array_values);
                    manager->data_list.push_back(byte_data);
                } else 
                    std::cout << "Invalid Type of Array Element!" << std::endl;
            }
        }
    }
}

void MipsBackend::generate_mips_code(Function &function) {
    auto label_instr = new MipsLabel("func_" + function.name);
    // std::cout << "Function Name : " << function.name << std::endl;
    manager->instr_list.push_back(label_instr);
    cur_func_param_num = function.fparams.size();
    cur_func_name = function.name;
    cur_local_var_offset = std::unordered_map<int, int>();
    cur_virtual_reg_offset = std::unordered_map<int, int>();
    cur_sp_offset = -4;
    auto sw_instr = new ITypeInstr(Sw, manager->ra_reg, manager->sp_reg, cur_sp_offset);
    manager->instr_list.push_back(sw_instr);
    for (const auto &basic_block : function.basic_blocks) {
        generate_mips_code(*basic_block);
    }
}

void MipsBackend::generate_mips_code(BasicBlock &basic_block) {
    // if (basic_block.instrs.empty()) return;
    auto label_instr = new MipsLabel("func_" + cur_func_name + "_block_" + std::to_string(basic_block.id));
    manager->instr_list.push_back(label_instr);
    for (const auto &instr : basic_block.instrs) {
        if (auto alloca_ir = dynamic_cast<AllocaInstr*>(instr)) {
            generate_mips_code(*alloca_ir);
        } else if (auto arith_ir = dynamic_cast<ArithmeticInstr*>(instr)) {
            generate_mips_code(*arith_ir);
        } else if (auto br_ir = dynamic_cast<BrInstr*>(instr)) {
            generate_mips_code(*br_ir);
        } else if (auto call_ir = dynamic_cast<CallInstr*>(instr)) {
            generate_mips_code(*call_ir);
        } else if (auto icmp_ir = dynamic_cast<IcmpInstr*>(instr)) {
            generate_mips_code(*icmp_ir);
        } else if (auto load_ir = dynamic_cast<LoadInstr*>(instr)) {
            generate_mips_code(*load_ir);
        } else if (auto store_ir = dynamic_cast<StoreInstr*>(instr)) {
            generate_mips_code(*store_ir);
        } else if (auto zext_ir = dynamic_cast<ZextInstr*>(instr)) {
            generate_mips_code(*zext_ir);
        } else if (auto trunc_ir = dynamic_cast<TruncInstr*>(instr)) {
            generate_mips_code(*trunc_ir);
        } else if (auto ret_ir = dynamic_cast<RetInstr*>(instr)) {
            generate_mips_code(*ret_ir);
        } else if (auto gep_ir = dynamic_cast<GetelementptrInstr*>(instr)) {
            generate_mips_code(*gep_ir);
        }
    }
}

void MipsBackend::generate_mips_code(AllocaInstr &alloca_instr) {
    auto deref_type = ((PointerType*)alloca_instr.type)->referenced_type;
    int size = ir_type_size(deref_type);
    if (size % 4 != 0) size = (size / 4 + 1) * 4;
    cur_sp_offset -= size;
    cur_local_var_offset[alloca_instr.id] = cur_sp_offset;
    // std::cout << "Alloca : " << alloca_instr.id << " " << cur_sp_offset << std::endl;
}


// 算数运算操作 每一种操作至多使用三种寄存器
// 使用$v1存储结果, 使用$t8存储op1, 使用$t9存储op2
void MipsBackend::generate_mips_code(ArithmeticInstr &arith_instr) {
    switch (arith_instr.arith_type) {
    case ArithmeticInstr::ADD:
        if ((!is_const_value(arith_instr.op1)) && (!is_const_value(arith_instr.op2))) {
            load_to_register(arith_instr.op1->id, manager->temp_regs_pool[8]);
            load_to_register(arith_instr.op2->id, manager->temp_regs_pool[9]);
            auto addu_instr = new RTypeInstr(Addu, manager->retval_regs_pool[1], manager->temp_regs_pool[8], manager->temp_regs_pool[9]);
            manager->instr_list.push_back(addu_instr);
        } else if (is_const_value(arith_instr.op1)) {
            load_to_register(arith_instr.op2->id, manager->temp_regs_pool[9]);
            int op1 = get_const_value(arith_instr.op1);
            auto addiu_instr = new ITypeInstr(Addiu, manager->retval_regs_pool[1], manager->temp_regs_pool[9], op1);
            manager->instr_list.push_back(addiu_instr);
        } else {
            load_to_register(arith_instr.op1->id, manager->temp_regs_pool[8]);
            int op2 = get_const_value(arith_instr.op2);
            auto addiu_instr = new ITypeInstr(Addiu, manager->retval_regs_pool[1], manager->temp_regs_pool[8], op2);
            manager->instr_list.push_back(addiu_instr);
        }
        break;
    case ArithmeticInstr::SUB:
        if ((!is_const_value(arith_instr.op1)) && (!is_const_value(arith_instr.op2))) {
            load_to_register(arith_instr.op1->id, manager->temp_regs_pool[8]);
            load_to_register(arith_instr.op2->id, manager->temp_regs_pool[9]);
            auto subu_instr = new RTypeInstr(Subu, manager->retval_regs_pool[1], manager->temp_regs_pool[8], manager->temp_regs_pool[9]);
            manager->instr_list.push_back(subu_instr);
        } else if (is_const_value(arith_instr.op1)) {
            load_to_register(arith_instr.op2->id, manager->temp_regs_pool[9]);
            int op1 = get_const_value(arith_instr.op1);
            auto li_instr = new NonTypeInstr(Li, manager->temp_regs_pool[8], op1);
            manager->instr_list.push_back(li_instr);
            auto subu_instr = new RTypeInstr(Subu, manager->retval_regs_pool[1], manager->temp_regs_pool[8], manager->temp_regs_pool[9]);
            manager->instr_list.push_back(subu_instr);
        } else {
            load_to_register(arith_instr.op1->id, manager->temp_regs_pool[8]);
            int op2 = get_const_value(arith_instr.op2);
            auto subu_instr = new NonTypeInstr(Subu, manager->retval_regs_pool[1], manager->temp_regs_pool[8], op2);
            manager->instr_list.push_back(subu_instr);
        }
        break;
    case ArithmeticInstr::MUL:
        if ((!is_const_value(arith_instr.op1)) && (!is_const_value(arith_instr.op2))) {
            load_to_register(arith_instr.op1->id, manager->temp_regs_pool[8]);
            load_to_register(arith_instr.op2->id, manager->temp_regs_pool[9]);
            auto mul_instr = new RTypeInstr(Mul, manager->retval_regs_pool[1], manager->temp_regs_pool[8], manager->temp_regs_pool[9]);
            manager->instr_list.push_back(mul_instr);
        } else if (is_const_value(arith_instr.op1)) {
            load_to_register(arith_instr.op2->id, manager->temp_regs_pool[9]);
            int op1 = get_const_value(arith_instr.op1);
            auto mul_instr = new ITypeInstr(Mul, manager->retval_regs_pool[1], manager->temp_regs_pool[9], op1);
            manager->instr_list.push_back(mul_instr);
        } else {
            load_to_register(arith_instr.op1->id, manager->temp_regs_pool[8]);
            int op2 = get_const_value(arith_instr.op2);
            auto mul_instr = new ITypeInstr(Mul, manager->retval_regs_pool[1], manager->temp_regs_pool[8], op2);
            manager->instr_list.push_back(mul_instr);
        }
        break;
    case ArithmeticInstr::SDIV:
        if ((!is_const_value(arith_instr.op1)) && (!is_const_value(arith_instr.op2))) {
            load_to_register(arith_instr.op1->id, manager->temp_regs_pool[8]);
            load_to_register(arith_instr.op2->id, manager->temp_regs_pool[9]);
            auto div_instr = new RTypeInstr(Div, manager->retval_regs_pool[1], manager->temp_regs_pool[8], manager->temp_regs_pool[9]);
            manager->instr_list.push_back(div_instr);
        } else if (is_const_value(arith_instr.op1)) {
            load_to_register(arith_instr.op2->id, manager->temp_regs_pool[9]);
            int op1 = get_const_value(arith_instr.op1);
            auto li_instr = new NonTypeInstr(Li, manager->temp_regs_pool[8], op1);
            manager->instr_list.push_back(li_instr);
            auto div_instr = new RTypeInstr(Div, manager->retval_regs_pool[1], manager->temp_regs_pool[8], manager->temp_regs_pool[9]);
            manager->instr_list.push_back(div_instr);
        } else {
            load_to_register(arith_instr.op1->id, manager->temp_regs_pool[8]);
            int op2 = get_const_value(arith_instr.op2);
            auto div_instr = new NonTypeInstr(Div, manager->retval_regs_pool[1], manager->temp_regs_pool[8], op2);
            manager->instr_list.push_back(div_instr);
        }
        break;
    case ArithmeticInstr::SREM:
        //! mips中没有求余指令 可以通过div指令得到余数
        //! 商在lo寄存器中 余数在hi寄存器中
        //! but pesudo instruction REM is provided by MARS
        if ((!is_const_value(arith_instr.op1)) && (!is_const_value(arith_instr.op2))) {
            load_to_register(arith_instr.op1->id, manager->temp_regs_pool[8]);
            load_to_register(arith_instr.op2->id, manager->temp_regs_pool[9]);
            auto rem_instr = new NonTypeInstr(Rem, manager->retval_regs_pool[1], manager->temp_regs_pool[8], manager->temp_regs_pool[9]);
            manager->instr_list.push_back(rem_instr);
        } else if (is_const_value(arith_instr.op1)) {
            load_to_register(arith_instr.op2->id, manager->temp_regs_pool[9]);
            int op1 = get_const_value(arith_instr.op1);
            auto rem_instr = new NonTypeInstr(Rem, manager->retval_regs_pool[1], manager->temp_regs_pool[9], op1);
            manager->instr_list.push_back(rem_instr);
        } else {
            load_to_register(arith_instr.op1->id, manager->temp_regs_pool[8]);
            int op2 = get_const_value(arith_instr.op2);
            auto rem_instr = new NonTypeInstr(Rem, manager->retval_regs_pool[1], manager->temp_regs_pool[8], op2);
            manager->instr_list.push_back(rem_instr);
        }
        break;
    default: 
        std::cout << "Undefined ArithmeticInstr!" << std::endl;
        break;
    }
    cur_sp_offset -= 4;
    cur_virtual_reg_offset[arith_instr.id] = cur_sp_offset;
    auto sw_instr = new ITypeInstr(Sw, manager->retval_regs_pool[1], manager->sp_reg, cur_sp_offset);
    manager->instr_list.push_back(sw_instr);
}

//! this function is used to load value stored in virtual register (memory) to a physical register
void MipsBackend::load_to_register(int value_id, MipsReg* dst_reg, MipsReg* addr_reg) {
    if (addr_reg == nullptr) addr_reg = manager->sp_reg;
    if (cur_virtual_reg_offset.find(value_id) != cur_virtual_reg_offset.end()) {
        auto lw_instr = new ITypeInstr(Lw, dst_reg, addr_reg, cur_virtual_reg_offset[value_id]);
        manager->instr_list.push_back(lw_instr);
    } else {
        std::cout << "Cur Func : " << cur_func_name << std::endl;
        std::cout << "LoadInstr : WHAT THE HELL! can't find virtual register!"<< " id : " << value_id << std::endl;
    }
}

void MipsBackend::generate_mips_code(BrInstr &br_instr) {
    if (br_instr.condition) {
        load_to_register(br_instr.condition->id, manager->temp_regs_pool[8]);
        auto beq_instr = new ITypeInstr(Beq, manager->temp_regs_pool[8], manager->zero_reg, "func_" + cur_func_name + "_block_" + std::to_string(br_instr.false_block->id));
        manager->instr_list.push_back(beq_instr);
        auto j_instr = new JTypeInstr(J, "func_" + cur_func_name + "_block_" + std::to_string(br_instr.true_block->id));
        manager->instr_list.push_back(j_instr);
    } else {
        auto j_instr = new JTypeInstr(J, "func_" + cur_func_name + "_block_" + std::to_string(br_instr.true_block->id));
        manager->instr_list.push_back(j_instr);
    }
}

void MipsBackend::generate_mips_code(RetInstr &ret_instr) {
    if (ret_instr.return_value) {
        if (is_const_value(ret_instr.return_value)) {
            auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], get_const_value(ret_instr.return_value));
            manager->instr_list.push_back(li_instr);
        } else load_to_register(ret_instr.return_value->id, manager->retval_regs_pool[0]);
    }
    auto lw_instr = new ITypeInstr(Lw, manager->ra_reg, manager->sp_reg, -4);
    manager->instr_list.push_back(lw_instr);
    auto jr_instr = new RTypeInstr(Jr, manager->ra_reg);
    manager->instr_list.push_back(jr_instr);
}

void MipsBackend::generate_mips_code(CallInstr &call_instr) {
    if (call_instr.function->name == "getint") {
        auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], 5);
        manager->instr_list.push_back(li_instr);
        auto syscall_instr = new NonTypeInstr(Syscall);
        manager->instr_list.push_back(syscall_instr);
        cur_sp_offset -= 4;
        cur_virtual_reg_offset[call_instr.id] = cur_sp_offset;
        auto sw_instr = new ITypeInstr(Sw, manager->retval_regs_pool[0], manager->sp_reg, cur_sp_offset);
        manager->instr_list.push_back(sw_instr);
    } else if (call_instr.function->name == "getchar") {
        auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], 12);
        manager->instr_list.push_back(li_instr);
        auto syscall_instr = new NonTypeInstr(Syscall);
        manager->instr_list.push_back(syscall_instr);
        cur_sp_offset -= 4;
        cur_virtual_reg_offset[call_instr.id] = cur_sp_offset;
        auto sw_instr = new ITypeInstr(Sw, manager->retval_regs_pool[0], manager->sp_reg, cur_sp_offset);
        manager->instr_list.push_back(sw_instr);
    } else if (call_instr.function->name == "putint") {
        if (is_const_value(call_instr.args[0])) {
            auto li_instr = new NonTypeInstr(Li, manager->arg_regs_pool[0], get_const_value(call_instr.args[0]));
            manager->instr_list.push_back(li_instr);
        } else load_to_register(call_instr.args[0]->id, manager->arg_regs_pool[0]);
        auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], 1);
        manager->instr_list.push_back(li_instr);
        auto syscall_instr = new NonTypeInstr(Syscall);
        manager->instr_list.push_back(syscall_instr);
    } else if (call_instr.function->name == "putch") {
        if (is_const_value(call_instr.args[0])) {
            auto li_instr = new NonTypeInstr(Li, manager->arg_regs_pool[0], get_const_value(call_instr.args[0]));
            manager->instr_list.push_back(li_instr);
        } else load_to_register(call_instr.args[0]->id, manager->arg_regs_pool[0]);
        auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], 11);
        manager->instr_list.push_back(li_instr);
        auto syscall_instr = new NonTypeInstr(Syscall);
        manager->instr_list.push_back(syscall_instr);
    } else if (call_instr.function->name == "putstr") {
        auto gep_instr = (GetelementptrInstr*)call_instr.args[0];
        auto gv_name = ((GlobalVariable*)gep_instr->array)->name;
        auto la_instr = new NonTypeInstr(La, manager->arg_regs_pool[0], manager->zero_reg, "g_" + gv_name);
        manager->instr_list.push_back(la_instr);
        auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], 4);
        manager->instr_list.push_back(li_instr);
        auto syscall_instr = new NonTypeInstr(Syscall);
        manager->instr_list.push_back(syscall_instr);
    } else {
        //! $fp is the bottom of the stack, higher address
        //! $sp is the top of the stack, lower address
        //! a stack frame is like
        //! | arg0 | arg... | saved regs | ra | local vars |
        int arg_num = call_instr.args.size();
        auto addu_instr = new RTypeInstr(Addu, manager->fp_reg, manager->sp_reg, manager->zero_reg);
        manager->instr_list.push_back(addu_instr);
        int stack_size = 4 * arg_num + (-cur_sp_offset);
        auto addi_instr = new ITypeInstr(Addi, manager->sp_reg, manager->sp_reg, -stack_size);
        manager->instr_list.push_back(addi_instr);
        for (int i = 0; i < arg_num; i++) {
            auto arg = call_instr.args[i];
            if (i < 4) { // $a0-$a3
                if (is_const_value(arg)) {
                    auto li_instr = new NonTypeInstr(Li, manager->arg_regs_pool[i], get_const_value(arg));
                    manager->instr_list.push_back(li_instr);
                } else load_to_register(arg->id, manager->arg_regs_pool[i], manager->fp_reg);
            } else { // $sp
                if (is_const_value(arg)) {
                    auto li_instr = new NonTypeInstr(Li, manager->temp_regs_pool[8], get_const_value(arg));
                    manager->instr_list.push_back(li_instr);
                } else load_to_register(arg->id, manager->temp_regs_pool[8], manager->fp_reg);
                auto sw_instr = new ITypeInstr(Sw, manager->temp_regs_pool[8], manager->sp_reg, 4 * i);
                manager->instr_list.push_back(sw_instr);
            }
        }
        auto jal_instr = new JTypeInstr(Jal, "func_" + call_instr.function->name);
        manager->instr_list.push_back(jal_instr);
        // restore stack
        addi_instr = new ITypeInstr(Addi, manager->sp_reg, manager->sp_reg, stack_size);
        manager->instr_list.push_back(addi_instr);
        // return value
        auto return_type = ((FunctionType*)call_instr.function->type)->return_type;
        if (return_type != &IR_VOID) {
            cur_sp_offset -= 4;
            cur_virtual_reg_offset[call_instr.id] = cur_sp_offset;
            auto load_instr = new ITypeInstr(Sw, manager->retval_regs_pool[0], manager->sp_reg, cur_sp_offset);
            manager->instr_list.push_back(load_instr);
        }
    }
}

void MipsBackend::generate_mips_code(LoadInstr &load_instr) {
    if (auto gv_ptr = dynamic_cast<GlobalVariable*>(load_instr.src_ptr)) {
        auto deref_type = ((PointerType*)load_instr.src_ptr->type)->referenced_type;
        if (auto char_type = dynamic_cast<CharType*>(deref_type)) {
            auto lbu_instr = new ITypeInstr(Lbu, manager->temp_regs_pool[8], manager->zero_reg, "g_" + gv_ptr->name);
            manager->instr_list.push_back(lbu_instr);
        } else {
            auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->zero_reg, "g_" + gv_ptr->name);
            manager->instr_list.push_back(lw_instr);
        }
    } else if (cur_local_var_offset.find(load_instr.src_ptr->id) != cur_local_var_offset.end()) {
        auto deref_type = ((PointerType*)load_instr.src_ptr->type)->referenced_type;
        if (auto char_type = dynamic_cast<CharType*>(deref_type)) {
            auto lbu_instr = new ITypeInstr(Lbu, manager->temp_regs_pool[8], manager->sp_reg, cur_local_var_offset[load_instr.src_ptr->id]);
            manager->instr_list.push_back(lbu_instr);
        } else {
            auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, cur_local_var_offset[load_instr.src_ptr->id]);
            manager->instr_list.push_back(lw_instr);
        }
    } else if (cur_virtual_reg_offset.find(load_instr.src_ptr->id) != cur_virtual_reg_offset.end()) {
        auto vreg = cur_virtual_reg_offset.find(load_instr.src_ptr->id);
        auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, vreg->second);
        manager->instr_list.push_back(lw_instr);
        auto deref_type = ((PointerType*)load_instr.src_ptr->type)->referenced_type;
        if (auto char_type = dynamic_cast<CharType*>(deref_type)) {
            auto lbu_instr = new ITypeInstr(Lbu, manager->temp_regs_pool[8], manager->temp_regs_pool[8], 0);
            manager->instr_list.push_back(lbu_instr);
        } else {
            lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->temp_regs_pool[8], 0);
            manager->instr_list.push_back(lw_instr);
        }
    } else {
        std::cout << "Invalid Load Instruction!" << std::endl;
    }
    cur_sp_offset -= 4;
    cur_virtual_reg_offset[load_instr.id] = cur_sp_offset;
    auto sw_instr = new ITypeInstr(Sw, manager->temp_regs_pool[8], manager->sp_reg, cur_sp_offset);
    manager->instr_list.push_back(sw_instr);
}

void MipsBackend::generate_mips_code(StoreInstr &store_instr) {
    int value_id = store_instr.store_value->id;
    int ptr_id = store_instr.dst_ptr->id;
    //! 需要先把存的值load进reg  $t8
    if (is_const_value(store_instr.store_value)) {
        auto li_instr = new NonTypeInstr(Li, manager->temp_regs_pool[8], get_const_value(store_instr.store_value));
        manager->instr_list.push_back(li_instr);
    } else {
        if (value_id < cur_func_param_num) {
            if (value_id < 4) {
                cur_sp_offset -= 4;
                cur_virtual_reg_offset[ptr_id] = cur_sp_offset;
                int ptr_offset = cur_local_var_offset[ptr_id];
                auto store_instr = new ITypeInstr(Sw, manager->arg_regs_pool[value_id], manager->sp_reg, ptr_offset);
                manager->instr_list.push_back(store_instr);
                return;
            } else {
                int offset = 4 * value_id;
                auto load_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, offset);
                manager->instr_list.push_back(load_instr);
            }
        } else load_to_register(value_id, manager->temp_regs_pool[8]);
    }
    //! 然后把ptr load进reg
    if (auto gv_ptr = dynamic_cast<GlobalVariable*>(store_instr.dst_ptr)) {
        auto deref_type = ((PointerType*)store_instr.dst_ptr->type)->referenced_type;
        if (auto char_type = dynamic_cast<CharType*>(deref_type)) {
            auto sb_instr = new ITypeInstr(Sb, manager->temp_regs_pool[8], manager->zero_reg, "g_" + gv_ptr->name);
            manager->instr_list.push_back(sb_instr);
        } else {
            auto sw_instr = new ITypeInstr(Sw, manager->temp_regs_pool[8], manager->zero_reg, "g_" + gv_ptr->name);
            manager->instr_list.push_back(sw_instr);
        }
    } else if (cur_local_var_offset.find(ptr_id) != cur_local_var_offset.end()) {
        auto deref_type = ((PointerType*)store_instr.dst_ptr->type)->referenced_type;
        if (auto char_type = dynamic_cast<CharType*>(deref_type)) {
            auto sb_instr = new ITypeInstr(Sb, manager->temp_regs_pool[8], manager->sp_reg, cur_local_var_offset[ptr_id]);
            manager->instr_list.push_back(sb_instr);
        } else {
            auto sw_instr = new ITypeInstr(Sw, manager->temp_regs_pool[8], manager->sp_reg, cur_local_var_offset[ptr_id]);
            manager->instr_list.push_back(sw_instr);
        }
    } else if (cur_virtual_reg_offset.find(ptr_id) != cur_virtual_reg_offset.end()) {
        auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[9], manager->sp_reg, cur_virtual_reg_offset[ptr_id]);
        manager->instr_list.push_back(lw_instr);
        auto deref_type = ((PointerType*)store_instr.dst_ptr->type)->referenced_type;
        if (auto char_type = dynamic_cast<CharType*>(deref_type)) {
            auto sb_instr = new ITypeInstr(Sb, manager->temp_regs_pool[8], manager->temp_regs_pool[9], 0);
            manager->instr_list.push_back(sb_instr);
        } else {
            auto sw_instr = new ITypeInstr(Sw, manager->temp_regs_pool[8], manager->temp_regs_pool[9], 0);
            manager->instr_list.push_back(sw_instr);
        }
    } else {
        std::cout << "Invalid Store Instruction!" << std::endl;
    }
}

void MipsBackend::generate_mips_code(GetelementptrInstr &gep_instr) {
    if (auto gv_array = dynamic_cast<GlobalVariable*>(gep_instr.array)) {
        auto la_instr = new NonTypeInstr(La, manager->temp_regs_pool[8], manager->zero_reg, "g_" + gv_array->name);
        manager->instr_list.push_back(la_instr);
    } else if (cur_local_var_offset.find(gep_instr.array->id) != cur_local_var_offset.end()) {
        auto la_instr = new NonTypeInstr(La, manager->temp_regs_pool[8], manager->sp_reg, cur_local_var_offset[gep_instr.array->id]);
        manager->instr_list.push_back(la_instr);
    } else if (cur_virtual_reg_offset.find(gep_instr.array->id) != cur_virtual_reg_offset.end()) {
        auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, cur_virtual_reg_offset[gep_instr.array->id]);
        manager->instr_list.push_back(lw_instr);
    } else {
        std::cout << "Invalid Getelementptr Instruction!" << std::endl;
    }
    int offset = 0;
    ValueType* cur_type = ((PointerType*)gep_instr.array->type)->referenced_type;
    for (int i = 0; i < gep_instr.indices.size(); i++) {
        int cur_size = ir_type_size(cur_type);
        if (is_const_value(gep_instr.indices[i])) {
            offset += get_const_value(gep_instr.indices[i]) * cur_size;
        } else {
            if (cur_type == &IR_CHAR) { // alignment = 1, no need to multiply
                load_to_register(gep_instr.indices[i]->id, manager->temp_regs_pool[9]);
                auto addu_instr = new RTypeInstr(Addu, manager->temp_regs_pool[8], manager->temp_regs_pool[8], manager->temp_regs_pool[9]);
                manager->instr_list.push_back(addu_instr);
            } else {
                load_to_register(gep_instr.indices[i]->id, manager->temp_regs_pool[9]);
                auto mul_instr = new NonTypeInstr(Mul, manager->temp_regs_pool[9], manager->temp_regs_pool[9], cur_size);
                manager->instr_list.push_back(mul_instr);
                auto addu_instr = new RTypeInstr(Addu, manager->temp_regs_pool[8], manager->temp_regs_pool[8], manager->temp_regs_pool[9]);
                manager->instr_list.push_back(addu_instr);
            }
        }
        if (auto array_type = dynamic_cast<ArrayType*>(cur_type))
            cur_type = array_type->element_type;
    }
    if (offset != 0) {
        auto addiu_instr = new ITypeInstr(Addiu, manager->temp_regs_pool[8], manager->temp_regs_pool[8], offset);
        manager->instr_list.push_back(addiu_instr);
    }
    cur_sp_offset -= 4;
    cur_virtual_reg_offset[gep_instr.id] = cur_sp_offset;
    auto sw_instr = new ITypeInstr(Sw, manager->temp_regs_pool[8], manager->sp_reg, cur_sp_offset);
    manager->instr_list.push_back(sw_instr);
}

void MipsBackend::generate_mips_code(ZextInstr &zext_instr) {
    if (cur_virtual_reg_offset[zext_instr.operand->id])
        cur_virtual_reg_offset[zext_instr.id] = cur_virtual_reg_offset[zext_instr.operand->id];
    else std::cout << "ZextInstr : Invalid Operand!" << std::endl;
}

void MipsBackend::generate_mips_code(TruncInstr &trunc_instr) {
    if (cur_virtual_reg_offset[trunc_instr.operand->id])
        cur_virtual_reg_offset[trunc_instr.id] = cur_virtual_reg_offset[trunc_instr.operand->id];
    else std::cout << "TruncInstr : Invalid Operand!" << std::endl;
}

void MipsBackend::generate_mips_code(IcmpInstr &icmp_instr) {
    OpType op_type;
    switch (icmp_instr.compare_type) {
        case IcmpInstr::EQ: op_type = Seq; break;
        case IcmpInstr::NE: op_type = Sne; break;
        case IcmpInstr::SGT: op_type = Sgt; break;
        case IcmpInstr::SGE: op_type = Sge; break;
        case IcmpInstr::SLT: op_type = Slt; break;
        case IcmpInstr::SLE: op_type = Sle; break;
        default: break;
    }
    if ((!is_const_value(icmp_instr.op1)) && (!is_const_value(icmp_instr.op2))) {
        load_to_register(icmp_instr.op1->id, manager->temp_regs_pool[8]);
        load_to_register(icmp_instr.op2->id, manager->temp_regs_pool[9]);
        auto instr = new RTypeInstr(op_type, manager->retval_regs_pool[1], manager->temp_regs_pool[8], manager->temp_regs_pool[9]);
        manager->instr_list.push_back(instr);
    } else if (is_const_value(icmp_instr.op1)) {
        switch (icmp_instr.compare_type) {
            case IcmpInstr::SGT: op_type = Slti; break;
            case IcmpInstr::SGE: op_type = Sle; break;
            case IcmpInstr::SLE: op_type = Sge; break;
            case IcmpInstr::SLT: op_type = Sgt; break;
            //! 这里除了slt之外都是伪指令 slt不支持立即数 转换为伪指令sgt
            //! sgt支持16/32位立即数
            default: break;
        }
        load_to_register(icmp_instr.op2->id, manager->temp_regs_pool[9]);
        int op1 = get_const_value(icmp_instr.op1);
        if (icmp_instr.compare_type == IcmpInstr::SLT && (op1 < XBIT_MIN || op1 > XBIT_MAX)) {
            auto li_instr = new NonTypeInstr(Li, manager->temp_regs_pool[8], op1);
            manager->instr_list.push_back(li_instr);
            op_type = Slt;
            auto instr = new RTypeInstr(op_type, manager->retval_regs_pool[1], manager->temp_regs_pool[9], manager->temp_regs_pool[8]);
            manager->instr_list.push_back(instr);
        } else {
            auto instr = new ITypeInstr(op_type, manager->retval_regs_pool[1], manager->temp_regs_pool[9], op1);
            manager->instr_list.push_back(instr);
        }
    } else {
        //! slt不支持立即数 转换为slti后也只能支持16位立即数
        if (icmp_instr.compare_type == IcmpInstr::SLT) op_type = Slti;
        load_to_register(icmp_instr.op1->id, manager->temp_regs_pool[8]);
        int op2 = get_const_value(icmp_instr.op2);
        if (icmp_instr.compare_type == IcmpInstr::SLT && (op2 < XBIT_MIN || op2 > XBIT_MAX)) { //! 超出slti立即数范围
            auto li_instr = new NonTypeInstr(Li, manager->temp_regs_pool[9], op2);
            manager->instr_list.push_back(li_instr);
            op_type = Slt;
            auto instr = new RTypeInstr(op_type, manager->retval_regs_pool[1], manager->temp_regs_pool[8], manager->temp_regs_pool[9]);
            manager->instr_list.push_back(instr);
        } else {
            auto instr = new ITypeInstr(op_type, manager->retval_regs_pool[1], manager->temp_regs_pool[8], op2);
            manager->instr_list.push_back(instr);
        }
    }
    cur_sp_offset -= 4;
    cur_virtual_reg_offset[icmp_instr.id] = cur_sp_offset;
    auto sw_instr = new ITypeInstr(Sw, manager->retval_regs_pool[1], manager->sp_reg, cur_sp_offset);
    manager->instr_list.push_back(sw_instr);
}

void MipsBackend::print_mips_code() const {
    std::ofstream mips_out("mips.txt", std::ios::trunc);
    mips_out << ".data" << std::endl;
    for (auto &data : manager->data_list) {
        data->print(mips_out);
        mips_out << std::endl;
    }
    mips_out << std::endl;
    mips_out << std::endl;
    mips_out << ".text" << std::endl;
    auto jal_instr = new JTypeInstr(Jal, "func_main");
    jal_instr->print(mips_out);
    mips_out << std::endl;
    auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], 10);
    li_instr->print(mips_out);
    mips_out << std::endl;
    auto syscall_instr = new NonTypeInstr(Syscall);
    syscall_instr->print(mips_out);
    mips_out << std::endl;
    mips_out << std::endl;
    for (auto &instr : manager->instr_list) {
        instr->print(mips_out);
        mips_out << std::endl;
    }
}