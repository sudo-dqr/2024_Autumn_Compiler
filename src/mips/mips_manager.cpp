#include "mips_manager.h"

MipsManager::MipsManager() {
    // init registers
    zero_reg = new ZeroReg();
    at_reg = new AtReg();
    sp_reg = new StackPtrReg();
    fp_reg = new FramePtrReg();
    ra_reg = new ReturnAddrReg();
    for (int i = 0; i < 10; i++)
        temp_regs_pool[i] = new TempReg(i);
    for (int i = 0; i < 8; i++)
        saved_regs_pool[i] = new SavedReg(i);
    for (int i = 0; i < 4; i++)
        arg_regs_pool[i] = new ArgReg(i);
    for (int i = 0; i < 2; i++)
        retval_regs_pool[i] = new RetValReg(i);
    for (int i = 0; i < 2; i++)
        kernel_regs_pool[i] = new KernelReg(i);        
}

MipsManager::~MipsManager() {
    delete zero_reg;
    delete at_reg;
    delete sp_reg;
    delete fp_reg;
    delete ra_reg;
    for (int i = 0; i < 10; i++)
        delete temp_regs_pool[i];
    for (int i = 0; i < 8; i++)
        delete saved_regs_pool[i];
    for (int i = 0; i < 4; i++)
        delete arg_regs_pool[i];
    for (int i = 0; i < 2; i++)
        delete retval_regs_pool[i];
    for (int i = 0; i < 2; i++)
        delete kernel_regs_pool[i];
    for (auto instr : instr_list)
        delete instr;
    for (auto data : data_list)
        delete data;
}