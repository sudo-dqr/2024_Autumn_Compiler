#ifndef MIPS_H
#define MIPS_H
#include "mips_reg.h"
#include "mips_instr.h"
#include "value.h"

struct MipsBackend {
    void generate_mips_code(Module &module);

    private:
        MipsManager* manager;

};

#endif // MIPS_H