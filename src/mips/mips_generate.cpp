#include "mips_generate.h"
#include "mips_utils.h"

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
    std::cout << "Function Name : " << function.name << std::endl;
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
    if (basic_block.instrs.empty()) return;
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
    cur_sp_offset -= size;
    cur_local_var_offset[alloca_instr.id] = cur_sp_offset;
    std::cout << "Alloca : " << alloca_instr.id << " " << cur_sp_offset << std::endl;
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
            auto subu_instr = new ITypeInstr(Subu, manager->retval_regs_pool[1], manager->temp_regs_pool[9], op1);
            manager->instr_list.push_back(subu_instr);
        } else {
            load_to_register(arith_instr.op1->id, manager->temp_regs_pool[8]);
            int op2 = get_const_value(arith_instr.op2);
            auto subu_instr = new ITypeInstr(Subu, manager->retval_regs_pool[1], manager->temp_regs_pool[8], op2);
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
            auto div_instr = new ITypeInstr(Div, manager->retval_regs_pool[1], manager->temp_regs_pool[9], op1);
            manager->instr_list.push_back(div_instr);
        } else {
            load_to_register(arith_instr.op1->id, manager->temp_regs_pool[8]);
            int op2 = get_const_value(arith_instr.op2);
            auto div_instr = new ITypeInstr(Div, manager->retval_regs_pool[1], manager->temp_regs_pool[8], op2);
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
        break;
    }
}

void MipsBackend::load_to_register(int value_id, MipsReg* reg) {
    if (cur_virtual_reg_offset.find(value_id) != cur_virtual_reg_offset.end()) {
        auto lw_instr = new ITypeInstr(Lw, reg, manager->sp_reg, cur_virtual_reg_offset[value_id]);
        manager->instr_list.push_back(lw_instr);
    } else if (cur_local_var_offset.find(value_id) != cur_local_var_offset.end()) {
        auto lw_instr = new ITypeInstr(Lw, reg, manager->sp_reg, cur_local_var_offset[value_id]);
        manager->instr_list.push_back(lw_instr);
    } else {
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
        if (auto intconst_ptr = dynamic_cast<IntConst*>(ret_instr.return_value)) {
            auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], intconst_ptr->value);
            manager->instr_list.push_back(li_instr);
        } else if (auto charconst_ptr = dynamic_cast<CharConst*>(ret_instr.return_value)) {
            auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], charconst_ptr->value);
            manager->instr_list.push_back(li_instr);
        } else if (cur_virtual_reg_offset.find(ret_instr.return_value->id) != cur_virtual_reg_offset.end()) {
            auto lw_instr = new ITypeInstr(Lw, manager->retval_regs_pool[0], manager->sp_reg, cur_virtual_reg_offset[ret_instr.return_value->id]);
            manager->instr_list.push_back(lw_instr);
        } else if (cur_local_var_offset.find(ret_instr.return_value->id) != cur_local_var_offset.end()) {
            auto lw_instr = new ITypeInstr(Lw, manager->retval_regs_pool[0], manager->sp_reg, cur_local_var_offset[ret_instr.return_value->id]);
            manager->instr_list.push_back(lw_instr);
        } else {
            std::cout << "ReturnInstr : Invalid Return Value!" << std::endl;
            return;
        }
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
    } else if (call_instr.function->name == "getch") {
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
        auto la_instr = new NonTypeInstr(La, manager->arg_regs_pool[0], "g_" + call_instr.args[0]->name);
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
                } else load_to_register(arg->id, manager->arg_regs_pool[i]);
            } else { // $sp
                if (is_const_value(arg)) {
                    auto li_instr = new NonTypeInstr(Li, manager->temp_regs_pool[8], get_const_value(arg));
                    manager->instr_list.push_back(li_instr);
                } else load_to_register(arg->id, manager->temp_regs_pool[8]);
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
            cur_local_var_offset[call_instr.id] = cur_sp_offset;
            auto load_instr = new ITypeInstr(Lw, manager->retval_regs_pool[0], manager->sp_reg, cur_sp_offset);
            manager->instr_list.push_back(load_instr);
        }
    }
}

void MipsBackend::generate_mips_code(IcmpInstr &icmp_instr) {

}

void MipsBackend::generate_mips_code(LoadInstr &load_instr) {
    auto deref_type = ((PointerType*)load_instr.src_ptr->type)->referenced_type;
    ITypeInstr* lw_instr = nullptr;
    if (auto gv_ptr = dynamic_cast<GlobalVariable*>(deref_type)) {
        lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->zero_reg, "g_" + gv_ptr->name);
    } else if (cur_local_var_offset.find(load_instr.src_ptr->id) != cur_local_var_offset.end()) {
        lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, cur_local_var_offset[load_instr.src_ptr->id]);
    } else if (cur_virtual_reg_offset.find(load_instr.src_ptr->id) != cur_virtual_reg_offset.end()) {
        auto vreg = cur_virtual_reg_offset.find(load_instr.src_ptr->id);
        lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[9], manager->sp_reg, vreg->second);
        manager->instr_list.push_back(lw_instr);
        lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[9], manager->temp_regs_pool[8], 0);
    } else {
        std::cout << "Invalid Load Instruction!" << std::endl;
    }
    manager->instr_list.push_back(lw_instr);
    cur_sp_offset -= 4;
    cur_local_var_offset[load_instr.id] = cur_sp_offset;    
    auto sw_instr = new ITypeInstr(Sw, manager->temp_regs_pool[8], manager->sp_reg, cur_sp_offset);
    manager->instr_list.push_back(sw_instr);
}

void MipsBackend::generate_mips_code(StoreInstr &store_instr) {
    int value_id = store_instr.store_value->id;
    int ptr_id = store_instr.dst_ptr->id;
    //! 需要先把存的值load进reg  $t8
    if (auto intconst_ptr = dynamic_cast<IntConst*>(store_instr.store_value)) {
        auto li_instr = new NonTypeInstr(Li, manager->temp_regs_pool[8], intconst_ptr->value);
        manager->instr_list.push_back(li_instr);
    } else if (auto charconst_ptr = dynamic_cast<CharConst*>(store_instr.store_value)) {
        auto li_instr = new NonTypeInstr(Li, manager->temp_regs_pool[8], charconst_ptr->value);
        manager->instr_list.push_back(li_instr);
    } else {
        if (value_id < cur_func_param_num) {
            if (value_id < 4) {
                cur_sp_offset -= 4;
                cur_virtual_reg_offset[value_id] = cur_sp_offset;
                auto store_instr = new ITypeInstr(Sw, manager->arg_regs_pool[value_id], manager->sp_reg, cur_sp_offset);
                return;
            }
            auto load_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, cur_virtual_reg_offset[value_id]);
        } else if (cur_virtual_reg_offset.find(value_id) != cur_virtual_reg_offset.end()) {
            auto vreg = cur_virtual_reg_offset.find(value_id);
            auto load_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, vreg->second);
            manager->instr_list.push_back(load_instr);
        } else {
            auto load_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, cur_local_var_offset[value_id]);
            manager->instr_list.push_back(load_instr);
        }
    }
    //! 然后把ptr load进reg
    ITypeInstr* sw_instr = nullptr;
    if (auto gv_ptr = dynamic_cast<GlobalVariable*>(store_instr.store_value)) {
        sw_instr = new ITypeInstr(Sw, manager->temp_regs_pool[8], manager->zero_reg, "g_" + gv_ptr->name);
    } else if (cur_local_var_offset.find(ptr_id) != cur_local_var_offset.end()) {
        sw_instr = new ITypeInstr(Sw, manager->temp_regs_pool[8], manager->sp_reg, cur_local_var_offset[ptr_id]);
    } else if (cur_virtual_reg_offset.find(ptr_id) != cur_virtual_reg_offset.end()) {
        auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[9], manager->sp_reg, cur_virtual_reg_offset[ptr_id]);
        sw_instr = new ITypeInstr(Sw, manager->temp_regs_pool[8], manager->temp_regs_pool[9], 0);
    } else {
        std::cout << "Invalid Store Instruction!" << std::endl;
    }
    manager->instr_list.push_back(sw_instr);
}

void MipsBackend::generate_mips_code(GetelementptrInstr &gep_instr) {

}

void MipsBackend::generate_mips_code(ZextInstr &zext_instr) {

}

void MipsBackend::generate_mips_code(TruncInstr &trunc_instr) {

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