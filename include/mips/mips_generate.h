#ifndef MIPS_GENERATE_H
#define MIPS_GENERATE_H
#include "value.h"
#include "instr.h"
#include "mips_manager.h"
#include <unordered_map>

#define XBIT_MAX 32767
#define XBIT_MIN -32768

struct MipsBackend {
    
    enum Mode {
        NORMAL,
        OPTIMIZED
    };

    MipsBackend() { this->manager = new MipsManager();}
    void start_generate_mips_code(Module &module, Mode mode);
    void print_mips_code() const;

    private:
        MipsManager* manager;
        std::string cur_func_name;
        int cur_func_param_num = 0;
        int cur_sp_offset = 0;
        // llvm ir local variable offset
        std::unordered_map<int, int> cur_local_var_offset = {};
        // llvm ir virtual register offset
        std::unordered_map<int, int> cur_virtual_reg_offset = {};

        // before optimization
        void generate_mips_code(Module &module);
        void generate_mips_code(GlobalVariable &data);
        void generate_mips_code(Function &function);
        void generate_mips_code(BasicBlock &basic_block);
        void generate_mips_code(AllocaInstr &alloca_instr);
        void generate_mips_code(ArithmeticInstr &arith_instr);
        void load_to_register(int value_id, MipsReg* dst_reg, MipsReg* addr_reg = nullptr);
        void generate_mips_code(BrInstr &br_instr);
        void generate_mips_code(RetInstr &ret_instr);
        void generate_mips_code(CallInstr &call_instr);
        void generate_mips_code(IcmpInstr &icmp_instr);
        void generate_mips_code(LoadInstr &load_instr);
        void generate_mips_code(StoreInstr &store_instr);
        void generate_mips_code(GetelementptrInstr &gep_instr);
        void generate_mips_code(ZextInstr &zext_instr);
        void generate_mips_code(TruncInstr &trunc_instr);
        // after optimization
        void generate_optimized_mips_code(Module &module);
        void generate_optimized_mips_code(GlobalVariable &data);
        void generate_optimized_mips_code(Function &function);
        void generate_optimized_mips_code(BasicBlock &basic_block);
        void generate_optimized_mips_code(AllocaInstr &alloca_instr);
        void generate_optimized_mips_code(ArithmeticInstr &arith_instr);
        void generate_optimized_mips_code(BrInstr &br_instr);
        void generate_optimized_mips_code(RetInstr &ret_instr);
        void generate_optimized_mips_code(CallInstr &call_instr);
        void generate_optimized_mips_code(IcmpInstr &icmp_instr);
        void generate_optimized_mips_code(LoadInstr &load_instr);
        void generate_optimized_mips_code(StoreInstr &store_instr);
        void generate_optimized_mips_code(GetelementptrInstr &gep_instr);
        void generate_optimized_mips_code(ZextInstr &zext_instr);
        void generate_optimized_mips_code(TruncInstr &trunc_instr);
};

#endif // MIPS_MANAGER_H