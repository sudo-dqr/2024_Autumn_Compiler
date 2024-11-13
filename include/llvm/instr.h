#ifndef IR_INSTR_H
#define IR_INSTR_H

#include "value.h"

struct Instruction : public User {
    protected :
        Instruction(std::string name, ValueType* type, int id) : User(name, type, id) {}
        Instruction(std::string name, ValueType* type) : User(name, type) {}
        Instruction(int id, ValueType* type) : User(id, type) {}
        Instruction(ValueType* type) : User(type) {}

    public : 
        void print(std::ostream &os) const override;
};

struct AllocaInstr : public Instruction {
    int elements_num;

    AllocaInstr(int id, ValueType* type) : Instruction("pointer" + id, type, id), elements_num(1) {}
    AllocaInstr(int id, ValueType* type, int elements_num) : Instruction("pointer" + id, type, id), elements_num(elements_num) {}
    void print(std::ostream &os) const;
};

struct ArithmeticInstr : public Instruction {
    enum AriType {
        ADD, SUB, MUL, SDIV, SREM
    };

    AriType arith_type;
    Value* op1;
    Value* op2;

    ArithmeticInstr(int id, AriType arith_type, Value* op1, Value* op2) : // char类型运算时先转int
        Instruction("arith" + id, &IR_INT, id), arith_type(arith_type), op1(op1), op2(op2) {}

    void print(std::ostream &os) const;
};

struct BrInstr : public Instruction {
    Value* condition; // conditional : bool -> i1; unconditional : nullptr
    BasicBlock* true_block;
    BasicBlock* false_block;

    BrInstr(Value *condition, BasicBlock* true_block, BasicBlock* false_block) :
        Instruction(&IR_VOID), condition(condition), true_block(true_block), false_block(false_block) {}

    BrInstr(BasicBlock* dst_block) :
        Instruction(&IR_VOID), condition(nullptr), true_block(dst_block), false_block(nullptr) {}

    void print(std::ostream &os) const override;
};

struct RetInstr : public Instruction {
    Value* return_value;

    RetInstr() : Instruction(&IR_VOID), return_value(nullptr) {}
    RetInstr(Value* return_value) : Instruction(&IR_VOID), return_value(return_value) {}

    void print(std::ostream &os) const override;
};

struct CallInstr : public Instruction { // void / int/char
    Function* function;
    std::vector<Value*> args;

    CallInstr(int id, ValueType* return_value_type, Function* function, std::vector<Value*> args) // int / char
    : Instruction("T" + id, return_value_type, id), function(function), args(args) {} 

    CallInstr(Function* function, std::vector<Value*> args) // void
    : Instruction(&IR_VOID), function(function), args(args) {}

    void print(std::ostream &os) const override;
};

struct GetelementptrInstr : public Instruction {
    Value* array;
    Value* index;

    GetelementptrInstr(int id, ValueType* type, Value* array, Value* index)
    : Instruction(id, type), array(array), index(index) {}

    void print(std::ostream &os) const override;
};

struct IcmpInstr : public Instruction {

};

struct StoreInstr : public Instruction {

};

struct LoadInstr : public Instruction {

};

struct ZextInstr : public Instruction {

};

struct TruncInstr : public Instruction {

};


#endif // IR_INSTR_H