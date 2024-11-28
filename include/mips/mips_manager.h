#ifndef MIPS_MANAGER_H
#define MIPS_MANAGER_H
#include <vector>
#include <unordered_map>
#include "mips_instr.h"
#include "mips_reg.h"
#include "mips_data.h"

struct MipsManager {
    // MIPS generate
    std::vector<MipsInstr*> instr_list;
    std::vector<MipsData*> data_list;

    // MIPS register
    std::unordered_map<int, TempReg*> temp_regs_pool;
    std::unordered_map<int, SavedReg*> saved_regs_pool;
    std::unordered_map<int, ArgReg*> arg_regs_pool;
    std::unordered_map<int, RetValReg*> retval_regs_pool;
    std::unordered_map<int, KernelReg*> kernel_regs_pool;
    ZeroReg* zero_reg;
    AtReg* at_reg;
    StackPtrReg* sp_reg;
    ReturnAddrReg* ra_reg;

    MipsManager();
    ~MipsManager();
};

#endif // MIPS_MANAGER_H