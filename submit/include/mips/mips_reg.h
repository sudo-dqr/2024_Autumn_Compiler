#ifndef MIPS_REG_H
#define MIPS_REG_H
#include <iostream>

enum MipsRegType {
    ZeroRegType, // $0
    AtRegType, // $at
    RetValRegType, // $v0, $v1
    ArgRegType, // $a0-$a3s
    TempRegType, // $t0-$t9
    SavedRegType, // $s0-$s7
    KernelRegType, // $k0-$k1
    GlobalPtrRegType, // $gp
    StackPtrRegType, // $sp
    FramePtrRegType, // $fp
    ReturnAddrRegType, // $ra 
};

struct MipsReg {
    MipsRegType type;
    int index;

    MipsReg(MipsRegType type, int index) : type(type), index(index) {}
    virtual void printReg(std::ostream &os) const = 0;
};

struct ZeroReg : public MipsReg {
    ZeroReg() : MipsReg(ZeroRegType, 0) {}
    void printReg(std::ostream &os) const override {
        os << "$zero";
    }
};

struct AtReg : public MipsReg {
    AtReg() : MipsReg(AtRegType, 1) {}
    void printReg(std::ostream &os) const override {
        os << "$at";
    }
};

struct RetValReg : public MipsReg {
    RetValReg(int index) : MipsReg(RetValRegType, index) {
        if (index < 0 || index > 1) 
            std::cout << "Invalid index for RetValReg" << std::endl;
    }
    void printReg(std::ostream &os) const override {
        os << "$v" << index;
    }
};

struct ArgReg : public MipsReg {
    ArgReg(int index) : MipsReg(ArgRegType, index) {
        if (index < 0 || index > 3) 
            std::cout << "Invalid index for ArgReg" << std::endl;
    }
    void printReg(std::ostream &os) const override {
        os << "$a" << index;
    }
};

struct TempReg : public MipsReg {
    TempReg(int index) : MipsReg(TempRegType, index) {
        if (index < 0 || index > 9) 
            std::cout << "Invalid index for TempReg" << std::endl;
    }
    void printReg(std::ostream &os) const override {
        os << "$t" << index;
    }
};

struct SavedReg : public MipsReg {
    SavedReg(int index) : MipsReg(SavedRegType, index) {
        if (index < 0 || index > 7) 
            std::cout << "Invalid index for SavedReg" << std::endl;
    }
    void printReg(std::ostream &os) const override {
        os << "$s" << index;
    }
};

struct KernelReg : public MipsReg {
    KernelReg(int index) : MipsReg(KernelRegType, index) {
        if (index < 0 || index > 1) 
            std::cout << "Invalid index for KernelReg" << std::endl;
    }
    void printReg(std::ostream &os) const override {
        os << "$k" << index;
    }
};

struct GlobalPtrReg : public MipsReg {
    GlobalPtrReg() : MipsReg(GlobalPtrRegType, 0) {}
    void printReg(std::ostream &os) const override {
        os << "$gp";
    }
};

struct StackPtrReg : public MipsReg {
    StackPtrReg() : MipsReg(StackPtrRegType, 0) {}
    void printReg(std::ostream &os) const override {
        os << "$sp";
    }
};

struct FramePtrReg : public MipsReg {
    FramePtrReg() : MipsReg(FramePtrRegType, 0) {}
    void printReg(std::ostream &os) const override {
        os << "$fp";
    }
};

struct ReturnAddrReg : public MipsReg {
    ReturnAddrReg() : MipsReg(ReturnAddrRegType, 0) {}
    void printReg(std::ostream &os) const override {
        os << "$ra";
    }
};

#endif