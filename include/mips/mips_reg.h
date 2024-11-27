#ifndef MIPS_REG_H
#define MIPS_REG_H

enum MipsRegType {
    ZeroReg, // $0
    AtReg, // $at
    RetValReg, // $v0, $v1
    ArgReg, // $a0-$a3s
    TempReg, // $t0-$t9
    SavedReg, // $s0-$s7
    KernelReg, // $k0-$k1
    GlobalPtrReg, // $gp
    StackPtrReg, // $sp
    FramePtrReg, // $fp
    ReturnAddrReg, // $ra 
};

struct MipsReg {
    enum MipsRegType type;
    int index;

    MipsReg(enum MipsRegType type, int index) : type(type), index(index) {}
    virtual void printReg(std::ostream &os) const = 0;
};

struct ZeroReg : public MipsReg {
    ZeroReg() : MipsReg(ZeroReg, 0) {}
    void printReg(std::ostream &os) const override {
        os << "$zero";
    }
}

struct AtReg : public MipsReg {
    AtReg() : MipsReg(AtReg, 1) {}
    void printReg(std::ostream &os) const override {
        os << "$at";
    }
}

struct RetValReg : public MipsReg {
    RetValReg(int index) : MipsReg(RetValReg, index) {
        if (index < 0 || index > 1) 
            std::cout << "Invalid index for RetValReg" << std::endl;
    }
    void printReg(std::ostream &os) const override {
        os << "$v" << index;
    }
}

struct ArgReg : public MipsReg {
    ArgReg(int index) : MipsReg(ArgReg, index) {
        if (index < 0 || index > 3) 
            std::cout << "Invalid index for ArgReg" << std::endl;
    }
    void printReg(std::ostream &os) const override {
        os << "$a" << index;
    }
}

struct TempReg : public MipsReg {
    TempReg(int index) : MipsReg(TempReg, index) {
        if (index < 0 || index > 9) 
            std::cout << "Invalid index for TempReg" << std::endl;
    }
    void printReg(std::ostream &os) const override {
        os << "$t" << index;
    }
}

struct SavedReg : public MipsReg {
    SavedReg(int index) : MipsReg(SavedReg, index) {
        if (index < 0 || index > 7) 
            std::cout << "Invalid index for SavedReg" << std::endl;
    }
    void printReg(std::ostream &os) const override {
        os << "$s" << index;
    }
}

struct KernelReg : public MipsReg {
    KernelReg(int index) : MipsReg(KernelReg, index) {
        if (index < 0 || index > 1) 
            std::cout << "Invalid index for KernelReg" << std::endl;
    }
    void printReg(std::ostream &os) const override {
        os << "$k" << index;
    }
}

struct GlobalPtrReg : public MipsReg {
    GlobalPtrReg() : MipsReg(GlobalPtrReg, 0) {}
    void printReg(std::ostream &os) const override {
        os << "$gp";
    }
}

struct StackPtrReg : public MipsReg {
    StackPtrReg() : MipsReg(StackPtrReg, 0) {}
    void printReg(std::ostream &os) const override {
        os << "$sp";
    }
}

struct FramePtrReg : public MipsReg {
    FramePtrReg() : MipsReg(FramePtrReg, 0) {}
    void printReg(std::ostream &os) const override {
        os << "$fp";
    }
}

struct ReturnAddrReg : public MipsReg {
    ReturnAddrReg() : MipsReg(ReturnAddrReg, 0) {}
    void printReg(std::ostream &os) const override {
        os << "$ra";
    }
}

#endif