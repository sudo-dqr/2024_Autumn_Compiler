#ifndef MIPS_GENERATE_H
#define MIPS_GENERATE_H
#include "value.h"
#include "mips_manager.h"

struct MipsBackend {
    MipsBackend() { manager = new MipsManager();}
    void generate_mips_code(Module &module);
    void print_mips_code() const;

    private:
        MipsManager* manager;
        void generate_mips_code(GlobalVariable &data);
        void generate_mips_code(Function &function);
};

#endif // MIPS_MANAGER_H