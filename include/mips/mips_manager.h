#ifndef MIPS_MANAGER_H
#define MIPS_MANAGER_H
#include "mips_instr.h"
#include "mips_reg.h"s
#include <vector>

struct MipsManager {
    private:
        std::vector<MipsInstr*> instr_list;
        std::vector<MipsData*> data_list;
};

#endif // MIPS_MANAGER_H