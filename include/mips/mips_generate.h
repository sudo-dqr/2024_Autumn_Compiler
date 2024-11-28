#ifndef MIPS_H
#define MIPS_H
#include "mips_reg.h"
#include "mips_instr.h"
#include "mips_data.h"
#include "mips_manager.h"
#include "value.h"

struct MipsBackend {
    MipsBackend() { manager = new MipsManager();}
    void generate_mips_code(Module &module);
    void print_mips_code() const;

    private:
        MipsManager* manager;
        void generate_mips_code(GlobalVariable &data);
        void generate_mips_code(Function &function);
};

#endif // MIPS_H