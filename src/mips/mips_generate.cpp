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
    auto label_instr = new MipsLabel(function.name);
    manager->instr_list.push_back(label_instr);
    cur_func_param_num = function.fparams.size();
    auto sw_instr = new ITypeInstr(Sw, manager->ra_reg, manager->sp_reg, -4);
    manager->instr_list.push_back(sw_instr);
    cur_sp_offset -= 4;
    for (const auto &basic_block : function.basic_blocks) {
        generate_mips_code(*basic_block);
    }
}

void MipsBackend::generate_mips_code(BasicBlock &basic_block) {
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

}

void MipsBackend::generate_mips_code(ArithmeticInstr &arith_instr) {

}

void MipsBackend::generate_mips_code(BrInstr &br_instr) {

}

void MipsBackend::generate_mips_code(RetInstr &ret_instr) {

}

void MipsBackend::generate_mips_code(CallInstr &call_instr) {

}

void MipsBackend::generate_mips_code(IcmpInstr &icmp_instr) {

}

void MipsBackend::generate_mips_code(LoadInstr &load_instr) {

}

void MipsBackend::generate_mips_code(StoreInstr &store_instr) {

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
    for (auto &instr : manager->instr_list) {
        instr->print(mips_out);
        mips_out << std::endl;
    }
}