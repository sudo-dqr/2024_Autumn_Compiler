#ifndef MIPS_MANAGER_H
#define MIPS_MANAGER_H
#include <vector>
struct MipsInstr;
struct MipsData;

struct MipsManager {
    std::vector<MipsInstr*> instr_list;
    std::vector<MipsData*> data_list;
};

#endif // MIPS_MANAGER_H