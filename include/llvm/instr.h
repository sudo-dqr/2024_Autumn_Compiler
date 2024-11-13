#ifndef IR_INSTR_H
#define IR_INSTR_H

#include "value.h"

struct Instruction : public User {
    protected :
        Instruction(std::string name, ValueType* type, int id) : User(name, type, id) {}
        Instruction(std::string name, ValueType* type) : User(name, type) {}
        Instruction(int id, ValueType* type) : User(id, type) {}

    public : 
        void print(std::ostream &os) const override;  
};

struct AllocaInstr : public Instruction {

};



#endif // IR_INSTR_H