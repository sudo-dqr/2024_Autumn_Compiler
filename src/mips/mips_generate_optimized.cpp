#include "mips_generate.h"
#include "mips_utils.h"
#include <cmath>
#include <climits>

//TODO: 寄存器分配中不free可以通过 free后testcase6会出错 

void MipsBackend::generate_optimized_mips_code(Module &module) {
    for (auto &data : module.global_variables) {
        generate_optimized_mips_code(*data);
    }
    for (auto &function: module.functions) {
        generate_optimized_mips_code(*function);
    }
}

void MipsBackend::generate_optimized_mips_code(GlobalVariable &data) {
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

void MipsBackend::generate_optimized_mips_code(Function &function) {
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
        generate_optimized_mips_code(*basic_block);
    }
}

void MipsBackend::generate_optimized_mips_code(BasicBlock &basic_block) {
    if (basic_block.instrs.empty()) return;
    register_allocator = new RegisterAllocator();
    auto label_instr = new MipsLabel("func_" + cur_func_name + "_block_" + std::to_string(basic_block.id));
    manager->instr_list.push_back(label_instr);
    for (const auto &instr : basic_block.instrs) {
        if (auto alloca_ir = dynamic_cast<AllocaInstr*>(instr)) {
            generate_optimized_mips_code(*alloca_ir);
        } else if (auto arith_ir = dynamic_cast<ArithmeticInstr*>(instr)) {
            generate_optimized_mips_code(*arith_ir);
        } else if (auto br_ir = dynamic_cast<BrInstr*>(instr)) {
            generate_optimized_mips_code(*br_ir);
        } else if (auto call_ir = dynamic_cast<CallInstr*>(instr)) {
            generate_optimized_mips_code(*call_ir);
        } else if (auto icmp_ir = dynamic_cast<IcmpInstr*>(instr)) {
            generate_optimized_mips_code(*icmp_ir);
        } else if (auto load_ir = dynamic_cast<LoadInstr*>(instr)) {
            generate_optimized_mips_code(*load_ir);
        } else if (auto store_ir = dynamic_cast<StoreInstr*>(instr)) {
            generate_optimized_mips_code(*store_ir);
        } else if (auto zext_ir = dynamic_cast<ZextInstr*>(instr)) {
            generate_optimized_mips_code(*zext_ir);
        } else if (auto trunc_ir = dynamic_cast<TruncInstr*>(instr)) {
            generate_optimized_mips_code(*trunc_ir);
        } else if (auto ret_ir = dynamic_cast<RetInstr*>(instr)) {
            generate_optimized_mips_code(*ret_ir);
        } else if (auto gep_ir = dynamic_cast<GetelementptrInstr*>(instr)) {
            generate_optimized_mips_code(*gep_ir);
        }
    }
}

void MipsBackend::generate_optimized_mips_code(AllocaInstr &alloca_instr) {
    auto deref_type = ((PointerType*)alloca_instr.type)->referenced_type;
    int size = ir_type_size(deref_type);
    if (size % 4 != 0) size = (size / 4 + 1) * 4;
    cur_sp_offset -= size;
    cur_local_var_offset[alloca_instr.id] = cur_sp_offset;
    // std::cout << "Alloca : " << alloca_instr.id << " " << cur_sp_offset << std::endl;
}


// 算数运算操作 每一种操作至多使用三种寄存器
// 使用$v1存储结果, 使用$t8存储op1, 使用$t9存储op2
void MipsBackend::generate_optimized_mips_code(ArithmeticInstr &arith_instr) {
    MipsReg* op1 = nullptr;
    MipsReg* op2 = nullptr;
    MipsReg* dst = nullptr;
    switch (arith_instr.arith_type) {
    case ArithmeticInstr::ADD:
        if ((!is_const_value(arith_instr.op1)) && (!is_const_value(arith_instr.op2))) {
            if (cur_virtual_reg_offset.find(arith_instr.op1->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op1->id]);
                manager->instr_list.push_back(lw_instr);
                op1 = manager->temp_regs_pool[8];
            } else {
                op1 = register_allocator->virtual_2_physical(arith_instr.op1->id);
                // register_allocator->free_register(arith_instr.op1->id);
            }
            if (cur_virtual_reg_offset.find(arith_instr.op2->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[9], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op2->id]);
                manager->instr_list.push_back(lw_instr);
                op2 = manager->temp_regs_pool[9];
            } else {
                op2 = register_allocator->virtual_2_physical(arith_instr.op2->id);
                // register_allocator->free_register(arith_instr.op2->id);
            }
            dst = register_allocator->allocate_register(arith_instr.id);
            if (!dst) dst = manager->retval_regs_pool[1];
            auto addu_instr = new RTypeInstr(Addu, dst, op1, op2);
            manager->instr_list.push_back(addu_instr);
        } else if (is_const_value(arith_instr.op1)) {
            if (cur_virtual_reg_offset.find(arith_instr.op2->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[9], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op2->id]);
                manager->instr_list.push_back(lw_instr);
                op2 = manager->temp_regs_pool[9];
            } else {
                op2 = register_allocator->virtual_2_physical(arith_instr.op2->id);
                // register_allocator->free_register(arith_instr.op2->id);
            }
            int op1 = get_const_value(arith_instr.op1);
            dst = register_allocator->allocate_register(arith_instr.id);
            if (!dst) dst = manager->retval_regs_pool[1];
            auto addiu_instr = new ITypeInstr(Addiu, dst, op2, op1);
            manager->instr_list.push_back(addiu_instr);
        } else {
            if (cur_virtual_reg_offset.find(arith_instr.op1->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op1->id]);
                manager->instr_list.push_back(lw_instr);
                op1 = manager->temp_regs_pool[8];
            } else {
                op1 = register_allocator->virtual_2_physical(arith_instr.op1->id);
                // register_allocator->free_register(arith_instr.op1->id);
            }
            int op2 = get_const_value(arith_instr.op2);
            dst = register_allocator->allocate_register(arith_instr.id);
            if (!dst) dst = manager->retval_regs_pool[1];
            auto addiu_instr = new ITypeInstr(Addiu, dst, op1, op2);
            manager->instr_list.push_back(addiu_instr);
        }
        break;
    case ArithmeticInstr::SUB:
        if ((!is_const_value(arith_instr.op1)) && (!is_const_value(arith_instr.op2))) {
            if (cur_virtual_reg_offset.find(arith_instr.op1->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op1->id]);
                manager->instr_list.push_back(lw_instr);
                op1 = manager->temp_regs_pool[8];
            } else {
                op1 = register_allocator->virtual_2_physical(arith_instr.op1->id);
                // register_allocator->free_register(arith_instr.op1->id);
            }
            if (cur_virtual_reg_offset.find(arith_instr.op2->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[9], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op2->id]);
                manager->instr_list.push_back(lw_instr);
                op2 = manager->temp_regs_pool[9];
            } else {
                op2 = register_allocator->virtual_2_physical(arith_instr.op2->id);
                // register_allocator->free_register(arith_instr.op2->id);
            }
            dst = register_allocator->allocate_register(arith_instr.id);
            if (!dst) dst = manager->retval_regs_pool[1];
            auto subu_instr = new RTypeInstr(Subu, dst, op1, op2);
            manager->instr_list.push_back(subu_instr);
        } else if (is_const_value(arith_instr.op1)) {
            int intconst = get_const_value(arith_instr.op1);
            auto li_instr = new NonTypeInstr(Li, manager->temp_regs_pool[8], intconst);
            manager->instr_list.push_back(li_instr);
            op1 = manager->temp_regs_pool[8];
            if (cur_virtual_reg_offset.find(arith_instr.op2->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[9], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op2->id]);
                manager->instr_list.push_back(lw_instr);
                op2 = manager->temp_regs_pool[9];
            } else {
                op2 = register_allocator->virtual_2_physical(arith_instr.op2->id);
                // register_allocator->free_register(arith_instr.op2->id);
            }
            dst = register_allocator->allocate_register(arith_instr.id);
            if (!dst) dst = manager->retval_regs_pool[1];
            auto subu_instr = new RTypeInstr(Subu, dst, op1, op2);
            manager->instr_list.push_back(subu_instr);
        } else {
            if (cur_virtual_reg_offset.find(arith_instr.op1->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op1->id]);
                manager->instr_list.push_back(lw_instr);
                op1 = manager->temp_regs_pool[8];
            } else {
                op1 = register_allocator->virtual_2_physical(arith_instr.op1->id);
                // register_allocator->free_register(arith_instr.op1->id);
            }
            int intconst = get_const_value(arith_instr.op2);
            dst = register_allocator->allocate_register(arith_instr.id);
            if (!dst) dst = manager->retval_regs_pool[1];
            if (intconst >= XBIT_MIN && intconst <= XBIT_MAX) {
                auto addiu_instr = new ITypeInstr(Addiu, dst, op1, -intconst);
                manager->instr_list.push_back(addiu_instr);
            } else {
                auto subiu_instr = new ITypeInstr(Subiu, dst, op1, intconst);
                manager->instr_list.push_back(subiu_instr);
            }
        }
        break;
    case ArithmeticInstr::MUL:
        if ((!is_const_value(arith_instr.op1)) && (!is_const_value(arith_instr.op2))) {
            if (cur_virtual_reg_offset.find(arith_instr.op1->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op1->id]);
                manager->instr_list.push_back(lw_instr);
                op1 = manager->temp_regs_pool[8];
            } else {
                op1 = register_allocator->virtual_2_physical(arith_instr.op1->id);
                // register_allocator->free_register(arith_instr.op1->id);
            }
            if (cur_virtual_reg_offset.find(arith_instr.op2->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[9], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op2->id]);
                manager->instr_list.push_back(lw_instr);
                op2 = manager->temp_regs_pool[9];
            } else {
                op2 = register_allocator->virtual_2_physical(arith_instr.op2->id);
                // register_allocator->free_register(arith_instr.op2->id);
            }
            dst = register_allocator->allocate_register(arith_instr.id);
            if (!dst) dst = manager->retval_regs_pool[1];
            auto mul_instr = new RTypeInstr(Mul, dst, op1, op2);
            manager->instr_list.push_back(mul_instr);
        } else if (is_const_value(arith_instr.op1)) {
            if (cur_virtual_reg_offset.find(arith_instr.op2->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[9], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op2->id]);
                manager->instr_list.push_back(lw_instr);
                op2 = manager->temp_regs_pool[9];
            } else {
                op2 = register_allocator->virtual_2_physical(arith_instr.op2->id);
                // register_allocator->free_register(arith_instr.op2->id);
            }
            int intconst = get_const_value(arith_instr.op1);
            dst = register_allocator->allocate_register(arith_instr.id);
            if (!dst) dst = manager->retval_regs_pool[1];
            if (optimize_multiply(intconst)) {
                int shift = factor_2_shift(intconst);
                auto sll_instr = new RTypeInstr(Sll, dst, op2, shift);
                manager->instr_list.push_back(sll_instr);
            } else {
                auto mul_instr = new ITypeInstr(Mul, dst, op2, intconst);
                manager->instr_list.push_back(mul_instr);
            }
        } else {
            if (cur_virtual_reg_offset.find(arith_instr.op1->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op1->id]);
                manager->instr_list.push_back(lw_instr);
                op1 = manager->temp_regs_pool[8];
            } else {
                op1 = register_allocator->virtual_2_physical(arith_instr.op1->id);
                // register_allocator->free_register(arith_instr.op1->id);
            }
            int intconst = get_const_value(arith_instr.op2);
            dst = register_allocator->allocate_register(arith_instr.id);
            if (!dst) dst = manager->retval_regs_pool[1];
            if (optimize_multiply(intconst)) {
                int shift = factor_2_shift(intconst);
                auto sll_instr = new RTypeInstr(Sll, dst, op1, shift);
                manager->instr_list.push_back(sll_instr);
            } else {
                auto mul_instr = new ITypeInstr(Mul, dst, op1, intconst);
                manager->instr_list.push_back(mul_instr);
            }
        }
        break;
    case ArithmeticInstr::SDIV:
        if ((!is_const_value(arith_instr.op1)) && (!is_const_value(arith_instr.op2))) {
            if (cur_virtual_reg_offset.find(arith_instr.op1->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op1->id]);
                manager->instr_list.push_back(lw_instr);
                op1 = manager->temp_regs_pool[8];
            } else {
                op1 = register_allocator->virtual_2_physical(arith_instr.op1->id);
                // register_allocator->free_register(arith_instr.op1->id);
            }
            if (cur_virtual_reg_offset.find(arith_instr.op2->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[9], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op2->id]);
                manager->instr_list.push_back(lw_instr);
                op2 = manager->temp_regs_pool[9];
            } else {
                op2 = register_allocator->virtual_2_physical(arith_instr.op2->id);
                // register_allocator->free_register(arith_instr.op2->id);
            }
            dst = register_allocator->allocate_register(arith_instr.id);
            if (!dst) dst = manager->retval_regs_pool[1];
            auto div_instr = new RTypeInstr(Div, dst, op1, op2);
            manager->instr_list.push_back(div_instr);
        } else if (is_const_value(arith_instr.op1)) {
            int intconst = get_const_value(arith_instr.op1);
            auto li_instr = new NonTypeInstr(Li, manager->temp_regs_pool[8], intconst);
            manager->instr_list.push_back(li_instr);
            op1 = manager->temp_regs_pool[8];
            if (cur_virtual_reg_offset.find(arith_instr.op2->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[9], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op2->id]);
                manager->instr_list.push_back(lw_instr);
                op2 = manager->temp_regs_pool[9];
            } else {
                op2 = register_allocator->virtual_2_physical(arith_instr.op2->id);
                // register_allocator->free_register(arith_instr.op2->id);
            }
            dst = register_allocator->allocate_register(arith_instr.id);
            if (!dst) dst = manager->retval_regs_pool[1];
            auto div_instr = new RTypeInstr(Div, dst, op1, op2);
            manager->instr_list.push_back(div_instr);
        } else {
            if (cur_virtual_reg_offset.find(arith_instr.op1->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op1->id]);
                manager->instr_list.push_back(lw_instr);
                op1 = manager->temp_regs_pool[8];
            } else {
                op1 = register_allocator->virtual_2_physical(arith_instr.op1->id);
                // register_allocator->free_register(arith_instr.op1->id);
            }
            dst = register_allocator->allocate_register(arith_instr.id);
            if (!dst) dst = manager->retval_regs_pool[1];
            optimize_divide(arith_instr, op1, dst);
        }
        break;
    case ArithmeticInstr::SREM:
        //! mips中没有求余指令 可以通过div指令得到余数
        //! 商在lo寄存器中 余数在hi寄存器中
        //! but pesudo instruction REM is provided by MARS
        if ((!is_const_value(arith_instr.op1)) && (!is_const_value(arith_instr.op2))) {
            if (cur_virtual_reg_offset.find(arith_instr.op1->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op1->id]);
                manager->instr_list.push_back(lw_instr);
                op1 = manager->temp_regs_pool[8];
            } else {
                op1 = register_allocator->virtual_2_physical(arith_instr.op1->id);
                // register_allocator->free_register(arith_instr.op1->id);
            }
            if (cur_virtual_reg_offset.find(arith_instr.op2->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[9], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op2->id]);
                manager->instr_list.push_back(lw_instr);
                op2 = manager->temp_regs_pool[9];
            } else {
                op2 = register_allocator->virtual_2_physical(arith_instr.op2->id);
                // register_allocator->free_register(arith_instr.op2->id);
            }
            dst = register_allocator->allocate_register(arith_instr.id);
            if (!dst) dst = manager->retval_regs_pool[1];
            auto rem_instr = new NonTypeInstr(Rem, dst, op1, op2);
            manager->instr_list.push_back(rem_instr);
        } else if (is_const_value(arith_instr.op1)) {
            int intconst = get_const_value(arith_instr.op1);
            auto li_instr = new NonTypeInstr(Li, manager->temp_regs_pool[8], intconst);
            manager->instr_list.push_back(li_instr);
            op1 = manager->temp_regs_pool[8];
            if (cur_virtual_reg_offset.find(arith_instr.op2->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[9], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op2->id]);
                manager->instr_list.push_back(lw_instr);
                op2 = manager->temp_regs_pool[9];
            } else {
                op2 = register_allocator->virtual_2_physical(arith_instr.op2->id);
                // register_allocator->free_register(arith_instr.op2->id);
            }
            dst = register_allocator->allocate_register(arith_instr.id);
            if (!dst) dst = manager->retval_regs_pool[1];
            auto rem_instr = new NonTypeInstr(Rem, dst, op1, op2);
            manager->instr_list.push_back(rem_instr);
        } else {
            if (cur_virtual_reg_offset.find(arith_instr.op1->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, cur_virtual_reg_offset[arith_instr.op1->id]);
                manager->instr_list.push_back(lw_instr);
                op1 = manager->temp_regs_pool[8];
            } else {
                op1 = register_allocator->virtual_2_physical(arith_instr.op1->id);
                // register_allocator->free_register(arith_instr.op1->id);
            }
            int intconst = get_const_value(arith_instr.op2);
            dst = register_allocator->allocate_register(arith_instr.id);
            if (!dst) dst = manager->retval_regs_pool[1];
            if (optimize_multiply(intconst)) {
                int shift = factor_2_shift(intconst);
                auto andi_instr = new ITypeInstr(Andi, dst, op1, (intconst - 1));
                manager->instr_list.push_back(andi_instr);
                std::string label = "rem_opt_" + std::to_string(special_counter++);
                auto bgez_instr = new ITypeInstr(Bgez, op1, label);
                manager->instr_list.push_back(bgez_instr);
                auto beq_instr = new ITypeInstr(Beq, dst, manager->zero_reg, label);
                manager->instr_list.push_back(beq_instr);
                if (intconst <= XBIT_MAX && intconst >= XBIT_MIN) {
                    auto addiu_instr = new ITypeInstr(Addiu, dst, dst, -intconst);
                    manager->instr_list.push_back(addiu_instr);
                } else {
                    auto subiu_instr = new ITypeInstr(Subiu, dst, dst, intconst);
                    manager->instr_list.push_back(subiu_instr);
                }
                auto label_instr = new MipsLabel(label);
                manager->instr_list.push_back(label_instr);
            } else {
                auto rem_instr = new NonTypeInstr(Rem, dst, op1, intconst);
                manager->instr_list.push_back(rem_instr);
            }
        }
        break;
    default: 
        std::cout << "Undefined ArithmeticInstr!" << std::endl;
        break;
    }
    if (dst == manager->retval_regs_pool[1]) {
        cur_sp_offset -= 4;
        cur_virtual_reg_offset[arith_instr.id] = cur_sp_offset;
        auto sw_instr = new ITypeInstr(Sw, manager->retval_regs_pool[1], manager->sp_reg, cur_sp_offset);
        manager->instr_list.push_back(sw_instr);
    }
}

void MipsBackend::optimize_divide(ArithmeticInstr instr, MipsReg* op1, MipsReg* dst) {
    bool is_divisor_negative = (get_const_value(instr.op2) < 0);
    int divisor = abs(get_const_value(instr.op2));
    long long multiplier;
    int shift, shift_log;
    choose_multiplier(divisor, shift_log, multiplier, shift);
    if (divisor == (1 << shift_log)) {
        auto sra_instr = new RTypeInstr(Sra, manager->kernel_regs_pool[0], op1, (shift_log - 1));
        manager->instr_list.push_back(sra_instr);
        auto srl_instr = new RTypeInstr(Srl, manager->kernel_regs_pool[0], manager->kernel_regs_pool[0], (32 - shift_log));
        manager->instr_list.push_back(srl_instr);
        auto addu_instr = new RTypeInstr(Addu, manager->kernel_regs_pool[0], manager->kernel_regs_pool[0], op1);
        manager->instr_list.push_back(addu_instr);
        sra_instr = new RTypeInstr(Sra, dst, manager->kernel_regs_pool[0], shift_log);
        manager->instr_list.push_back(sra_instr);
    } else if (number_of_leading_zeros(multiplier) > 0 && multiplier < 0x80000000L) {
        int m = (int)multiplier;
        auto li_instr = new NonTypeInstr(Li, manager->kernel_regs_pool[0], m);
        manager->instr_list.push_back(li_instr);
        auto mult_instr = new NonTypeInstr(Mult, manager->kernel_regs_pool[0], op1);
        manager->instr_list.push_back(mult_instr);
        auto mfhi_instr = new NonTypeInstr(Mfhi, manager->kernel_regs_pool[0]);
        manager->instr_list.push_back(mfhi_instr);
        auto sra_instr = new RTypeInstr(Sra, manager->kernel_regs_pool[0], manager->kernel_regs_pool[0], shift);
        manager->instr_list.push_back(sra_instr);
        sra_instr = new RTypeInstr(Sra, manager->kernel_regs_pool[1], op1, 31);
        manager->instr_list.push_back(sra_instr);
        auto subu_instr = new RTypeInstr(Subu, dst, manager->kernel_regs_pool[0], manager->kernel_regs_pool[1]);
        manager->instr_list.push_back(subu_instr);
    } else {
        int m = (int)(multiplier - 0x100000000L);
        auto li_instr = new NonTypeInstr(Li, manager->kernel_regs_pool[0], m);
        manager->instr_list.push_back(li_instr);
        auto mult_instr = new NonTypeInstr(Mult, manager->kernel_regs_pool[0], op1);
        manager->instr_list.push_back(mult_instr);
        auto mfhi_instr = new NonTypeInstr(Mfhi, manager->kernel_regs_pool[0]);
        manager->instr_list.push_back(mfhi_instr);
        auto addu_instr = new RTypeInstr(Addu, manager->kernel_regs_pool[0], manager->kernel_regs_pool[0], op1);
        manager->instr_list.push_back(addu_instr);
        auto sra_instr = new RTypeInstr(Sra, manager->kernel_regs_pool[0], manager->kernel_regs_pool[0], shift);
        manager->instr_list.push_back(sra_instr);
        sra_instr = new RTypeInstr(Sra, manager->kernel_regs_pool[1], op1, 31);
        manager->instr_list.push_back(sra_instr);
        auto subu_instr = new RTypeInstr(Subu, dst, manager->kernel_regs_pool[0], manager->kernel_regs_pool[1]);
        manager->instr_list.push_back(subu_instr);
    }
    if (is_divisor_negative) {
        auto subu_instr = new RTypeInstr(Subu, dst, manager->zero_reg, dst);
        manager->instr_list.push_back(subu_instr);
    }
}

int MipsBackend::number_of_leading_zeros(int divisor) {
    int count = 0;
    while ((divisor & 0x80000000) == 0) {
        divisor <<= 1;
        count++;
    }
    return count;
}

void MipsBackend::choose_multiplier(int divisor, int &shift_log, long long &multiplier, int &shift) {
    shift = 32 - number_of_leading_zeros(divisor - 1);
    shift_log = shift;
    long long low = (1LL << (32 + shift)) / divisor;
    long long high = ((1LL << (32 + shift)) + (1LL << (shift + 1))) / divisor;
    while ((low >> 1) < (high >> 1) && shift > 0) {
        low >>= 1;
        high >>= 1;
        shift--;
    }
    multiplier = high;
}

bool MipsBackend::optimize_multiply(int factor) {
    // Check if the factor is a power of 2
    if ((factor & (factor - 1)) == 0)
        if (factor != 0x80000000) return true;
    return false;
}

int MipsBackend::factor_2_shift(int factor) {
    int shift = -1;
    while (factor != 0) {
        factor = static_cast<unsigned int>(factor) >> 1; 
        shift++;
    }
    return shift;
}

void MipsBackend::generate_optimized_mips_code(BrInstr &br_instr) {
    if (br_instr.condition) {
        MipsReg* op1 = nullptr;
        if (cur_virtual_reg_offset.find(br_instr.condition->id) != cur_virtual_reg_offset.end()) {
            auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, cur_virtual_reg_offset[br_instr.condition->id]);
            manager->instr_list.push_back(lw_instr);
            op1 = manager->temp_regs_pool[8];
        } else {
            op1 = register_allocator->virtual_2_physical(br_instr.condition->id);
            // register_allocator->free_register(br_instr.condition->id);
        }
        auto beq_instr = new ITypeInstr(Beq, op1, manager->zero_reg, "func_" + cur_func_name + "_block_" + std::to_string(br_instr.false_block->id));
        manager->instr_list.push_back(beq_instr);
        auto j_instr = new JTypeInstr(J, "func_" + cur_func_name + "_block_" + std::to_string(br_instr.true_block->id));
        manager->instr_list.push_back(j_instr);
    } else {
        auto j_instr = new JTypeInstr(J, "func_" + cur_func_name + "_block_" + std::to_string(br_instr.true_block->id));
        manager->instr_list.push_back(j_instr);
    }
}

void MipsBackend::generate_optimized_mips_code(RetInstr &ret_instr) {
    if (ret_instr.return_value) {
        if (is_const_value(ret_instr.return_value)) {
            auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], get_const_value(ret_instr.return_value));
            manager->instr_list.push_back(li_instr);
        } else {
            if (cur_virtual_reg_offset.find(ret_instr.return_value->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->retval_regs_pool[0], manager->sp_reg, cur_virtual_reg_offset[ret_instr.return_value->id]);
                manager->instr_list.push_back(lw_instr);
            } else {
                auto op = register_allocator->virtual_2_physical(ret_instr.return_value->id);
                // register_allocator->free_register(ret_instr.return_value->id);
                auto addu_instr = new RTypeInstr(Addu, manager->retval_regs_pool[0], op, manager->zero_reg);
                manager->instr_list.push_back(addu_instr);
            }
        }
    }
    auto lw_instr = new ITypeInstr(Lw, manager->ra_reg, manager->sp_reg, -4);
    manager->instr_list.push_back(lw_instr);
    auto jr_instr = new RTypeInstr(Jr, manager->ra_reg);
    manager->instr_list.push_back(jr_instr);
}

void MipsBackend::generate_optimized_mips_code(CallInstr &call_instr) {
    if (call_instr.function->name == "getint") {
        auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], 5);
        manager->instr_list.push_back(li_instr);
        auto syscall_instr = new NonTypeInstr(Syscall);
        manager->instr_list.push_back(syscall_instr);
        auto dst = register_allocator->allocate_register(call_instr.id);
        if (!dst) {
            cur_sp_offset -= 4;
            cur_virtual_reg_offset[call_instr.id] = cur_sp_offset;
            auto sw_instr = new ITypeInstr(Sw, manager->retval_regs_pool[0], manager->sp_reg, cur_sp_offset);
            manager->instr_list.push_back(sw_instr);
        } else {
            auto addu_instr = new RTypeInstr(Addu, dst, manager->retval_regs_pool[0], manager->zero_reg);
            manager->instr_list.push_back(addu_instr);
        }
    } else if (call_instr.function->name == "getchar") {
        auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], 12);
        manager->instr_list.push_back(li_instr);
        auto syscall_instr = new NonTypeInstr(Syscall);
        manager->instr_list.push_back(syscall_instr);
        auto dst = register_allocator->allocate_register(call_instr.id);
        if (!dst) {
            cur_sp_offset -= 4;
            cur_virtual_reg_offset[call_instr.id] = cur_sp_offset;
            auto sw_instr = new ITypeInstr(Sw, manager->retval_regs_pool[0], manager->sp_reg, cur_sp_offset);
            manager->instr_list.push_back(sw_instr);
        } else {
            auto addu_instr = new RTypeInstr(Addu, dst, manager->retval_regs_pool[0], manager->zero_reg);
            manager->instr_list.push_back(addu_instr);
        }
    } else if (call_instr.function->name == "putint") {
        if (is_const_value(call_instr.args[0])) {
            auto li_instr = new NonTypeInstr(Li, manager->arg_regs_pool[0], get_const_value(call_instr.args[0]));
            manager->instr_list.push_back(li_instr);
        } else if (cur_virtual_reg_offset.find(call_instr.args[0]->id) != cur_virtual_reg_offset.end()) {
            auto lw_instr = new ITypeInstr(Lw, manager->arg_regs_pool[0], manager->sp_reg, cur_virtual_reg_offset[call_instr.args[0]->id]);
            manager->instr_list.push_back(lw_instr);
        } else {
            auto op = register_allocator->virtual_2_physical(call_instr.args[0]->id);
            // register_allocator->free_register(call_instr.args[0]->id);
            auto addu_instr = new RTypeInstr(Addu, manager->arg_regs_pool[0], op, manager->zero_reg);
            manager->instr_list.push_back(addu_instr);
        }
        auto li_instr = new NonTypeInstr(Li, manager->retval_regs_pool[0], 1);
        manager->instr_list.push_back(li_instr);
        auto syscall_instr = new NonTypeInstr(Syscall);
        manager->instr_list.push_back(syscall_instr);
    } else if (call_instr.function->name == "putch") {
        if (is_const_value(call_instr.args[0])) {
            auto li_instr = new NonTypeInstr(Li, manager->arg_regs_pool[0], get_const_value(call_instr.args[0]));
            manager->instr_list.push_back(li_instr);
        } else if (cur_virtual_reg_offset.find(call_instr.args[0]->id) != cur_virtual_reg_offset.end()) {
            auto lw_instr = new ITypeInstr(Lw, manager->arg_regs_pool[0], manager->sp_reg, cur_virtual_reg_offset[call_instr.args[0]->id]);
            manager->instr_list.push_back(lw_instr);
        } else {
            auto op = register_allocator->virtual_2_physical(call_instr.args[0]->id);
            // register_allocator->free_register(call_instr.args[0]->id);
            auto addu_instr = new RTypeInstr(Addu, manager->arg_regs_pool[0], op, manager->zero_reg);
            manager->instr_list.push_back(addu_instr);
        }
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
        std::vector<MipsReg*> active_regs = register_allocator->get_active_registers();
        for (int i = 0; i < active_regs.size(); i++) {
            cur_sp_offset -= 4;
            int virtual_reg_id = register_allocator->physical_2_virtual(active_regs[i]);
            if (!call_instr.contains_arg_id(virtual_reg_id)) {
                auto sw_instr = new ITypeInstr(Sw, active_regs[i], manager->sp_reg, cur_sp_offset);
                manager->instr_list.push_back(sw_instr);
            }
        }
        auto addu_instr = new RTypeInstr(Addu, manager->fp_reg, manager->sp_reg, manager->zero_reg);
        manager->instr_list.push_back(addu_instr);
        int stack_size = 4 * arg_num + (-cur_sp_offset);
        auto addiu_instr = new ITypeInstr(Addiu, manager->sp_reg, manager->sp_reg, -stack_size);
        manager->instr_list.push_back(addiu_instr);
        for (int i = 0; i < arg_num; i++) {
            auto arg = call_instr.args[i];
            if (i < 4) { // $a0-$a3
                if (is_const_value(arg)) {
                    auto li_instr = new NonTypeInstr(Li, manager->arg_regs_pool[i], get_const_value(arg));
                    manager->instr_list.push_back(li_instr);
                } else if (cur_virtual_reg_offset.find(arg->id) != cur_virtual_reg_offset.end()) {
                    auto lw_instr = new ITypeInstr(Lw, manager->arg_regs_pool[i], manager->fp_reg, cur_virtual_reg_offset[arg->id]);
                    manager->instr_list.push_back(lw_instr);
                } else {
                    auto op = register_allocator->virtual_2_physical(arg->id);
                    // register_allocator->free_register(arg->id);
                    auto addu_instr = new RTypeInstr(Addu, manager->arg_regs_pool[i], op, manager->zero_reg);
                    manager->instr_list.push_back(addu_instr);
                }
            } else { // $sp
                MipsReg* op = nullptr;
                if (is_const_value(arg)) {
                    auto li_instr = new NonTypeInstr(Li, manager->temp_regs_pool[8], get_const_value(arg));
                    manager->instr_list.push_back(li_instr);
                    op = manager->temp_regs_pool[8];
                } else if (cur_virtual_reg_offset.find(arg->id) != cur_virtual_reg_offset.end()) {
                    auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->fp_reg, cur_virtual_reg_offset[arg->id]);
                    manager->instr_list.push_back(lw_instr);
                    op = manager->temp_regs_pool[8];
                } else {
                    op = register_allocator->virtual_2_physical(arg->id);
                    // register_allocator->free_register(arg->id);
                }
                auto sw_instr = new ITypeInstr(Sw, op, manager->sp_reg, 4 * i);
                manager->instr_list.push_back(sw_instr);
            }
        }
        auto jal_instr = new JTypeInstr(Jal, "func_" + call_instr.function->name);
        manager->instr_list.push_back(jal_instr);
        // restore stack
        addiu_instr = new ITypeInstr(Addiu, manager->sp_reg, manager->sp_reg, (arg_num * 4 - cur_sp_offset));
        manager->instr_list.push_back(addiu_instr);
        for (int i = active_regs.size() - 1; i >= 0; i--) {
            //现在active_registers 中是否包含原来的active_registers
            if (register_allocator->is_active_register(active_regs[i])) {
                auto lw_instr = new ITypeInstr(Lw, active_regs[i], manager->sp_reg, cur_sp_offset);
                manager->instr_list.push_back(lw_instr);
            }
            cur_sp_offset += 4;
        }
        // return value
        auto return_type = ((FunctionType*)call_instr.function->type)->return_type;
        if (dynamic_cast<VoidType*>(return_type) == nullptr) {
            auto dst = register_allocator->allocate_register(call_instr.id);
            if (!dst) {
                cur_sp_offset -= 4;
                cur_virtual_reg_offset[call_instr.id] = cur_sp_offset;
                auto load_instr = new ITypeInstr(Sw, manager->retval_regs_pool[0], manager->sp_reg, cur_sp_offset);
                manager->instr_list.push_back(load_instr);
            } else {
                auto addu_instr = new RTypeInstr(Addu, dst, manager->retval_regs_pool[0], manager->zero_reg);
                manager->instr_list.push_back(addu_instr);
            }
        }
    }
}

void MipsBackend::generate_optimized_mips_code(LoadInstr &load_instr) {
    auto dst = register_allocator->allocate_register(load_instr.id);
    if (!dst) dst = manager->retval_regs_pool[1];
    if (auto gv_ptr = dynamic_cast<GlobalVariable*>(load_instr.src_ptr)) {
        auto deref_type = ((PointerType*)load_instr.src_ptr->type)->referenced_type;
        if (auto char_type = dynamic_cast<CharType*>(deref_type)) {
            auto lbu_instr = new ITypeInstr(Lbu, dst, manager->zero_reg, "g_" + gv_ptr->name);
            manager->instr_list.push_back(lbu_instr);
        } else {
            auto lw_instr = new ITypeInstr(Lw, dst, manager->zero_reg, "g_" + gv_ptr->name);
            manager->instr_list.push_back(lw_instr);
        }
    } else if (cur_local_var_offset.find(load_instr.src_ptr->id) != cur_local_var_offset.end()) {
        auto deref_type = ((PointerType*)load_instr.src_ptr->type)->referenced_type;
        if (auto char_type = dynamic_cast<CharType*>(deref_type)) {
            auto lbu_instr = new ITypeInstr(Lbu, dst, manager->sp_reg, cur_local_var_offset[load_instr.src_ptr->id]);
            manager->instr_list.push_back(lbu_instr);
        } else {
            auto lw_instr = new ITypeInstr(Lw, dst, manager->sp_reg, cur_local_var_offset[load_instr.src_ptr->id]);
            manager->instr_list.push_back(lw_instr);
        }
    } else if (cur_virtual_reg_offset.find(load_instr.src_ptr->id) != cur_virtual_reg_offset.end()) {
        auto vreg = cur_virtual_reg_offset.find(load_instr.src_ptr->id);
        auto lw_instr = new ITypeInstr(Lw, dst, manager->sp_reg, vreg->second);
        manager->instr_list.push_back(lw_instr);
        auto deref_type = ((PointerType*)load_instr.src_ptr->type)->referenced_type;
        if (auto char_type = dynamic_cast<CharType*>(deref_type)) {
            auto lbu_instr = new ITypeInstr(Lbu, dst, dst, 0);
            manager->instr_list.push_back(lbu_instr);
        } else {
            lw_instr = new ITypeInstr(Lw, dst, dst, 0);
            manager->instr_list.push_back(lw_instr);
        }
    } else {
        auto src_reg = register_allocator->virtual_2_physical(load_instr.src_ptr->id);
        // register_allocator->free_register(load_instr.src_ptr->id);
        if (auto char_type = dynamic_cast<CharType*>(((PointerType*)load_instr.src_ptr->type)->referenced_type)) {
            auto lbu_instr = new ITypeInstr(Lbu, dst, src_reg, 0);
            manager->instr_list.push_back(lbu_instr);
        } else {
            auto lw_instr = new ITypeInstr(Lw, dst, src_reg, 0);
            manager->instr_list.push_back(lw_instr);
        }
    }
    if (dst == manager->retval_regs_pool[1]) {
        cur_sp_offset -= 4;
        cur_virtual_reg_offset[load_instr.id] = cur_sp_offset;
        auto sw_instr = new ITypeInstr(Sw, dst, manager->sp_reg, cur_sp_offset);
        manager->instr_list.push_back(sw_instr);
    }
}

void MipsBackend::generate_optimized_mips_code(StoreInstr &store_instr) {
    int value_id = store_instr.store_value->id;
    int dst_id = store_instr.dst_ptr->id;
    MipsReg* op = nullptr;
    //! 需要先把存的值load进reg  $t8
    if (is_const_value(store_instr.store_value)) {
        auto li_instr = new NonTypeInstr(Li, manager->temp_regs_pool[8], get_const_value(store_instr.store_value));
        manager->instr_list.push_back(li_instr);
        op = manager->temp_regs_pool[8];
    } else {
        if (value_id < cur_func_param_num) {
            if (value_id < 4) {
                cur_sp_offset -= 4;
                cur_virtual_reg_offset[dst_id] = cur_sp_offset;
                int ptr_offset = cur_local_var_offset[dst_id];
                auto store_instr = new ITypeInstr(Sw, manager->arg_regs_pool[value_id], manager->sp_reg, ptr_offset);
                manager->instr_list.push_back(store_instr);
                return;
            } else {
                int offset = 4 * value_id;
                auto load_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, offset);
                manager->instr_list.push_back(load_instr);
                op = manager->temp_regs_pool[8];
            }
        } else if (cur_virtual_reg_offset.find(value_id) != cur_virtual_reg_offset.end()) {
            auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, cur_virtual_reg_offset[value_id]);
            manager->instr_list.push_back(lw_instr);
            op = manager->temp_regs_pool[8];
        } else {
            op = register_allocator->virtual_2_physical(value_id);
            // register_allocator->free_register(value_id);
        }
    }
    //! 然后把ptr load进reg
    if (auto gv_ptr = dynamic_cast<GlobalVariable*>(store_instr.dst_ptr)) {
        auto deref_type = ((PointerType*)store_instr.dst_ptr->type)->referenced_type;
        if (auto char_type = dynamic_cast<CharType*>(deref_type)) {
            auto sb_instr = new ITypeInstr(Sb, op, manager->zero_reg, "g_" + gv_ptr->name);
            manager->instr_list.push_back(sb_instr);
        } else {
            auto sw_instr = new ITypeInstr(Sw, op, manager->zero_reg, "g_" + gv_ptr->name);
            manager->instr_list.push_back(sw_instr);
        }
    } else if (cur_local_var_offset.find(dst_id) != cur_local_var_offset.end()) {
        auto deref_type = ((PointerType*)store_instr.dst_ptr->type)->referenced_type;
        if (auto char_type = dynamic_cast<CharType*>(deref_type)) {
            auto sb_instr = new ITypeInstr(Sb, op, manager->sp_reg, cur_local_var_offset[dst_id]);
            manager->instr_list.push_back(sb_instr);
        } else {
            auto sw_instr = new ITypeInstr(Sw, op, manager->sp_reg, cur_local_var_offset[dst_id]);
            manager->instr_list.push_back(sw_instr);
        }
    } else if (cur_virtual_reg_offset.find(dst_id) != cur_virtual_reg_offset.end()) {
        auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[9], manager->sp_reg, cur_virtual_reg_offset[dst_id]);
        manager->instr_list.push_back(lw_instr);
        auto deref_type = ((PointerType*)store_instr.dst_ptr->type)->referenced_type;
        if (auto char_type = dynamic_cast<CharType*>(deref_type)) {
            auto sb_instr = new ITypeInstr(Sb, op, manager->temp_regs_pool[9], 0);
            manager->instr_list.push_back(sb_instr);
        } else {
            auto sw_instr = new ITypeInstr(Sw, op, manager->temp_regs_pool[9], 0);
            manager->instr_list.push_back(sw_instr);
        }
    } else {
        auto dst_reg = register_allocator->virtual_2_physical(dst_id);
        // register_allocator->free_register(dst_id);
        if (auto char_type = dynamic_cast<CharType*>(((PointerType*)store_instr.dst_ptr->type)->referenced_type)) {
            auto sb_instr = new ITypeInstr(Sb, op, dst_reg, 0);
            manager->instr_list.push_back(sb_instr);
        } else {
            auto sw_instr = new ITypeInstr(Sw, op, dst_reg, 0);
            manager->instr_list.push_back(sw_instr);
        }
    }
}

void MipsBackend::generate_optimized_mips_code(GetelementptrInstr &gep_instr) {
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
        auto src_reg = register_allocator->virtual_2_physical(gep_instr.array->id);
        // register_allocator->free_register(gep_instr.array->id);
        auto addu_instr = new RTypeInstr(Addu, manager->temp_regs_pool[8], src_reg, manager->zero_reg);
        manager->instr_list.push_back(addu_instr);
    }
    int offset = 0;
    ValueType* cur_type = ((PointerType*)gep_instr.array->type)->referenced_type;
    for (int i = 0; i < gep_instr.indices.size(); i++) {
        int cur_size = ir_type_size(cur_type);
        if (is_const_value(gep_instr.indices[i])) {
            offset += get_const_value(gep_instr.indices[i]) * cur_size;
        } else {
            MipsReg* index = nullptr;
            if (cur_virtual_reg_offset.find(gep_instr.indices[i]->id) != cur_virtual_reg_offset.end()) {
                auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[9], manager->sp_reg, cur_virtual_reg_offset[gep_instr.indices[i]->id]);
                manager->instr_list.push_back(lw_instr);
                index = manager->temp_regs_pool[9];
            } else {
                index = register_allocator->virtual_2_physical(gep_instr.indices[i]->id);
                // register_allocator->free_register(gep_instr.indices[i]->id);
            }
            if (cur_type == &IR_CHAR) { // alignment = 1, no need to multiply
                auto addu_instr = new RTypeInstr(Addu, manager->temp_regs_pool[8], manager->temp_regs_pool[8], index);
                manager->instr_list.push_back(addu_instr);
            } else {
                if (optimize_multiply(cur_size)) {
                    auto sll_instr = new RTypeInstr(Sll, index, index, factor_2_shift(cur_size));
                    manager->instr_list.push_back(sll_instr);
                } else {
                    auto mul_instr = new NonTypeInstr(Mul, index, index, cur_size);
                    manager->instr_list.push_back(mul_instr);
                }
                auto addu_instr = new RTypeInstr(Addu, manager->temp_regs_pool[8], manager->temp_regs_pool[8], index);
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
    auto dst = register_allocator->allocate_register(gep_instr.id);
    if (dst == nullptr) {
        cur_sp_offset -= 4;
        cur_virtual_reg_offset[gep_instr.id] = cur_sp_offset;
        auto sw_instr = new ITypeInstr(Sw, manager->temp_regs_pool[8], manager->sp_reg, cur_sp_offset);
        manager->instr_list.push_back(sw_instr);
    } else {
        auto addu_instr = new RTypeInstr(Addu, dst, manager->temp_regs_pool[8], manager->zero_reg);
        manager->instr_list.push_back(addu_instr);
    }
}

void MipsBackend::generate_optimized_mips_code(ZextInstr &zext_instr) {
    if (cur_virtual_reg_offset[zext_instr.operand->id])
        cur_virtual_reg_offset[zext_instr.id] = cur_virtual_reg_offset[zext_instr.operand->id];
    else {
        register_allocator->move_register(zext_instr.operand->id, zext_instr.id);
    }
}

void MipsBackend::generate_optimized_mips_code(TruncInstr &trunc_instr) {
    if (cur_virtual_reg_offset[trunc_instr.operand->id])
        cur_virtual_reg_offset[trunc_instr.id] = cur_virtual_reg_offset[trunc_instr.operand->id];
    else {
        register_allocator->move_register(trunc_instr.operand->id, trunc_instr.id);
    }
}

void MipsBackend::generate_optimized_mips_code(IcmpInstr &icmp_instr) {
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
    MipsReg* op1 = nullptr;
    MipsReg* op2 = nullptr;
    MipsReg* dst = nullptr;
    if ((!is_const_value(icmp_instr.op1)) && (!is_const_value(icmp_instr.op2))) {
        if (cur_virtual_reg_offset.find(icmp_instr.op1->id) != cur_virtual_reg_offset.end()) {
            auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, cur_virtual_reg_offset[icmp_instr.op1->id]);
            manager->instr_list.push_back(lw_instr);
            op1 = manager->temp_regs_pool[8];
        } else {
            op1 = register_allocator->virtual_2_physical(icmp_instr.op1->id);
            // register_allocator->free_register(icmp_instr.op1->id);
        }
        if (cur_virtual_reg_offset.find(icmp_instr.op2->id) != cur_virtual_reg_offset.end()) {
            auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[9], manager->sp_reg, cur_virtual_reg_offset[icmp_instr.op2->id]);
            manager->instr_list.push_back(lw_instr);
            op2 = manager->temp_regs_pool[9];
        } else {
            op2 = register_allocator->virtual_2_physical(icmp_instr.op2->id);
            // register_allocator->free_register(icmp_instr.op2->id);
        }
        dst = register_allocator->allocate_register(icmp_instr.id);
        if (!dst) dst = manager->retval_regs_pool[1];
        auto instr = new RTypeInstr(op_type, dst, op1, op2);
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
        if (cur_virtual_reg_offset.find(icmp_instr.op2->id) != cur_virtual_reg_offset.end()) {
            auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[9], manager->sp_reg, cur_virtual_reg_offset[icmp_instr.op2->id]);
            manager->instr_list.push_back(lw_instr);
            op2 = manager->temp_regs_pool[9];
        } else {
            op2 = register_allocator->virtual_2_physical(icmp_instr.op2->id);
            // register_allocator->free_register(icmp_instr.op2->id);
        }
        int intconst = get_const_value(icmp_instr.op1);
        dst = register_allocator->allocate_register(icmp_instr.id);
        if (!dst) dst = manager->retval_regs_pool[1];
        if (icmp_instr.compare_type == IcmpInstr::SLT && (intconst < XBIT_MIN || intconst > XBIT_MAX)) {
            auto li_instr = new NonTypeInstr(Li, manager->temp_regs_pool[8], intconst);
            manager->instr_list.push_back(li_instr);
            op1 = manager->temp_regs_pool[8];
            op_type = Slt;
            auto instr = new RTypeInstr(op_type, dst, op2, op1);
            manager->instr_list.push_back(instr);
        } else {
            auto instr = new ITypeInstr(op_type, dst, op2, intconst);
            manager->instr_list.push_back(instr);
        }
    } else {
        //! slt不支持立即数 转换为slti后也只能支持16位立即数
        if (icmp_instr.compare_type == IcmpInstr::SLT) op_type = Slti;
        if (cur_virtual_reg_offset.find(icmp_instr.op1->id) != cur_virtual_reg_offset.end()) {
            auto lw_instr = new ITypeInstr(Lw, manager->temp_regs_pool[8], manager->sp_reg, cur_virtual_reg_offset[icmp_instr.op1->id]);
            manager->instr_list.push_back(lw_instr);
            op1 = manager->temp_regs_pool[8];
        } else {
            op1 = register_allocator->virtual_2_physical(icmp_instr.op1->id);
            // register_allocator->free_register(icmp_instr.op1->id);
        }
        int intconst = get_const_value(icmp_instr.op2);
        dst = register_allocator->allocate_register(icmp_instr.id);
        if (!dst) dst = manager->retval_regs_pool[1];
        if (icmp_instr.compare_type == IcmpInstr::SLT && (intconst < XBIT_MIN || intconst > XBIT_MAX)) { //! 超出slti立即数范围
            auto li_instr = new NonTypeInstr(Li, manager->temp_regs_pool[9], intconst);
            manager->instr_list.push_back(li_instr);
            op2 = manager->temp_regs_pool[9];
            op_type = Slt;
            auto instr = new RTypeInstr(op_type, dst, op1, op2);
            manager->instr_list.push_back(instr);
        } else {
            auto instr = new ITypeInstr(op_type, dst, op1, intconst);
            manager->instr_list.push_back(instr);
        }
    }
    if (dst == manager->retval_regs_pool[1]) {
        cur_sp_offset -= 4;
        cur_virtual_reg_offset[icmp_instr.id] = cur_sp_offset;
        auto sw_instr = new ITypeInstr(Sw, manager->retval_regs_pool[1], manager->sp_reg, cur_sp_offset);
        manager->instr_list.push_back(sw_instr);
    }
}