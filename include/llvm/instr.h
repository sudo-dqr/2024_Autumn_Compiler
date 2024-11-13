#ifndef IR_INSTR_H
#define IR_INSTR_H

#include "value.h"

struct Instruction : public User {
    protected :
        Instruction(std::string name, std::unique_ptr<ValueType> type, int id) : User(name, std::move(type), id) {}
        Instruction(std::string name, std::unique_ptr<ValueType> type) : User(name, std::move(type)) {}
        Instruction(int id, std::unique_ptr<ValueType> type) : User(id, std::move(type)) {}

    public : 
        void print(std::ostream &os) const override;  
};

struct AllocaInstr : public Instruction {

};



#endif // IR_INSTR_H