#include "mips_generate.h"

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
    manager->instr_list.push_back(label_instr);
    cur_func_param_num = function.fparams.size();
    cur_func_name = function.name;
    auto sw_instr = new ITypeInstr(Sw, manager->ra_reg, manager->sp_reg, -4);
    manager->instr_list.push_back(sw_instr);
    cur_sp_offset -= 4;
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
}

int MipsBackend::ir_type_size(ValueType* ir_type) {
    if (auto int_type = dynamic_cast<IntType*>(ir_type)) {
        return 4;
    } else if (auto char_type = dynamic_cast<CharType*>(ir_type)) {
        return 4;
    } else if (auto array_type = dynamic_cast<ArrayType*>(ir_type)) {
        return array_type->size * ir_type_size(array_type->element_type);
    } else if (auto pointer_type = dynamic_cast<PointerType*>(ir_type)) {
        return 4;
    } else {
        std::cout << "MIPS Alloca : Invalid Type!" << std::endl;
        return 0;
    }
}

void MipsBackend::generate_mips_code(ArithmeticInstr &arith_instr) {
    switch (arith_instr.arith_type) {
    case ArithmeticInstr::ADD:
        /* code */
        break;
    case ArithmeticInstr::SUB:
        /* code */
        break;
    case ArithmeticInstr::MUL:
        /* code */
        break;
    case ArithmeticInstr::SDIV:
        /* code */
        break;
    case ArithmeticInstr::SREM:
        /* code */
        break;
    default: 
        break;
    }
}

void MipsBackend::generate_mips_code(BrInstr &br_instr) {

}

void MipsBackend::generate_mips_code(RetInstr &ret_instr) {

}

void MipsBackend::generate_mips_code(CallInstr &call_instr) {
    if (call_instr.function->name == "getint") {
        auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], 5);
        manager->instr_list.push_back(li_instr);
        auto syscall_instr = new NonTypeInstr(Syscall);
        manager->instr_list.push_back(syscall_instr);
    } else if (call_instr.function->name == "getch") {
        auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], 12);
        manager->instr_list.push_back(li_instr);
        auto syscall_instr = new NonTypeInstr(Syscall);
        manager->instr_list.push_back(syscall_instr);
    } else if (call_instr.function->name == "putint") {
        auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], 1);
        manager->instr_list.push_back(li_instr);
        auto arg = call_instr.args[0];
        if (auto intconst_ptr = dynamic_cast<IntConst*>(arg)) {
            auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], intconst_ptr->value);
            manager->instr_list.push_back(li_instr);
        } else {

        }
        auto syscall_instr = new NonTypeInstr(Syscall);
        manager->instr_list.push_back(syscall_instr);
    } else if (call_instr.function->name == "putch") {
        auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], 11);
        manager->instr_list.push_back(li_instr);
        if (auto charconst_ptr = dynamic_cast<CharConst*>(call_instr.args[0])) {
            auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], charconst_ptr->value);
            manager->instr_list.push_back(li_instr);
        } else {

        }
        auto syscall_instr = new NonTypeInstr(Syscall);
        manager->instr_list.push_back(syscall_instr);
    } else if (call_instr.function->name == "putstr") {
        auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], 4);
        manager->instr_list.push_back(li_instr);
        //$a0
        auto syscall_instr = new NonTypeInstr(Syscall);
        manager->instr_list.push_back(syscall_instr);
    } else {
        int arg_num = call_instr.args.size();
        //! $fp is the bottom of the stack, higher address
        //! $sp is the top of the stack, lower address
        //! a stack frame is like
        //! | arg0 | arg... | saved regs | ra | local vars |
        auto addu_instr = new RTypeInstr(Addu, manager->fp_reg, manager->sp_reg, manager->zero_reg);
        manager->instr_list.push_back(addu_instr);
        int stack_size = 4 * arg_num - cur_sp_offset;
        auto addi_instr = new ITypeInstr(Addi, manager->sp_reg, manager->sp_reg, -stack_size);
        manager->instr_list.push_back(addi_instr);
        for (int i = 0; i < arg_num; i++) {
            auto arg = call_instr.args[i];
            if (i < 4) { // $a0-$a3
                if (auto intconst_ptr = dynamic_cast<IntConst*>(arg)) {
                    auto li_instr = new NonTypeInstr(Li, manager->arg_regs_pool[i], intconst_ptr->value);
                    manager->instr_list.push_back(li_instr);
                } else if (auto charconst_ptr = dynamic_cast<CharConst*>(arg)) {
                    auto li_instr = new NonTypeInstr(Li, manager->arg_regs_pool[i], charconst_ptr->value);
                    manager->instr_list.push_back(li_instr);
                } else if ((auto vreg = cur_virtual_reg_offset.find(arg->id)) != cur_virtual_reg_offset.end()) {
                    auto load_instr = new ITypeInstr(Lw, manager->arg_regs_pool[i], manager->fp_reg, vreg->second);
                    manager->instr_list.push_back(load_instr);
                } else {
                    auto load_instr = new ITypeInstr(Lw, manager->arg_regs_pool[i], manager->sp_reg, cur_local_var_offset[arg->id]);
                    manager->instr_list.push_back(load_instr);
                }
            } else { // $sp
                if (auto intconst_ptr = dynamic_cast<IntConst*>(arg)) {
                    auto li_instr = new NonTypeInstr(Li, manager->temp_regs_pool[0], intconst_ptr->value);
                    manager->instr_list.push_back(li_instr);
                } else if (auto charconst_ptr = dynamic_cast<CharConst*>(arg)) {
                    auto li_instr = new NonTypeInstr(Li, manager->temp_regs_pool[0], charconst_ptr->value);
                    manager->instr_list.push_back(li_instr);
                } else if (auto vreg = cur_virtual_reg_offset.find(arg->id) != cur_virtual_reg_offset.end()) {
                    auto load_instr = new ITypeInstr(Lw, manager->temp_regs_pool[0], manager->fp_reg, vreg->second);
                    manager->instr_list.push_back(load_instr);
                } else {
                    auto load_instr = new ITypeInstr(Lw, manager->temp_regs_pool[0], manager->sp_reg, cur_local_var_offset[arg->id]);
                    manager->instr_list.push_back(load_instr);
                }
                auto store_instr = new ITypeInstr(Sw, manager->temp_regs_pool[0], manager->sp_reg, 4 * i);
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
    auto deref_type = ((PointerType*)load_instr.type)->referenced_type;
    if (auto gv_ptr = dynamic_cast<GlobalVariable*>(deref_type)) {

    } else {
        int ptr_id = load_instr.src_ptr->id;
    }
}

void MipsBackend::generate_mips_code(StoreInstr &store_instr) {
    int value_id = store_instr.store_value->id;
    int ptr_id = store_instr.dst_ptr->id;
    if (value_id < cur_func_param_num) { // function params
        if (value_id < 4) { // $a0-$a3
            auto store_instr = new ITypeInstr(Sw, manager->arg_regs_pool[value_id], manager->sp_reg, cur_local_var_offset[ptr_id]);
            manager->instr_list.push_back(store_instr);
        }
    } else {

    }
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