#include "mips_generate.h"

void MipsBackend::generate_mips_code(Module &module) {
    manager = MipsManager::get_instance();
    for (auto &function: module.functions) {
        manager->generate_mips_code(*function);
    }
}