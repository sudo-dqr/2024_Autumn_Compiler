#ifndef IR_VALUE_H
#define IR_VALUE_H
//! This file is the definition of Value and other subclasses of Value in LLVM IR.

#include "type.h"
#include <memory>

// 前向声明 Instruction 类 头文件需要另外包含在.cpp文件中
struct Instruction;

struct Value : public IRPrintable {
    std::string name;
    ValueType* type;
    int id; // 虚拟寄存器号
    Value() = default;
    Value(std::string name, ValueType* type, int id) : name(name), type(type), id(id) {}
    Value(std::string name, ValueType* type) : name(name), type(type), id(-1) {}
    Value(int id, ValueType* type) : name("v" + id), type(type), id(id) {}
    Value(ValueType* type) : name(""), type(type), id(-1) {}
    
    void print(std::ostream &os) const override;
};

struct User : public Value {
    User() = default;
    User(std::string name, ValueType* type, int id) : Value(name, type, id) {}
    User(std::string name, ValueType* type) : Value(name, type) {}
    User(int id, ValueType* type) : Value(id, type) {}
    User(ValueType* type) : Value(type) {}

    void print(std::ostream &os) const override;
};

struct GlobalVariable : public Value {
    int int_value;
    char char_value;
    std::vector<int> int_array_init_values; // int array
    std::vector<char> char_array_init_values; // char array
    std::string char_array_init_string; // string const 全局变量可以使用字符串常量直接初始化，局部变量不可以

    GlobalVariable() = default;
    GlobalVariable(std::string name, ValueType* type, int int_value) 
    : Value(name, type), int_value(int_value) {}
    GlobalVariable(std::string name, ValueType* type, char char_value)
    : Value(name, type), char_value(char_value) {}
    GlobalVariable(std::string name, ValueType* type, std::vector<int> int_array_init_values) 
    : Value(name, type), int_array_init_values(int_array_init_values) {}
    GlobalVariable(std::string name, ValueType* type, std::vector<char> char_array_init_values) 
    : Value(name, type), char_array_init_values(char_array_init_values) {}
    GlobalVariable(std::string name, ValueType* type, std::string str) 
    : Value(name, type), char_array_init_string(str) {}

    void print(std::ostream &os) const override;
};

struct FParam : public Value { // LLVM IR中形参保存在虚拟寄存器上 首先需要将形参保存到栈上
    FParam(int id, ValueType* type) : Value("FP" + id, type, id) {}
    void print(std::ostream &os) const override;
};

struct BasicBlock : public Value {
    std::vector<Instruction*> instrs;

    BasicBlock() = default;
    BasicBlock(int id) : Value("basicblock" + id, &IR_LABEL) {}

    void print(std::ostream &os) const override;

};

struct Function : public Value {
    std::vector<FParam*> fparams;
    std::vector<BasicBlock*> basic_blocks;

    Function() = default;
    Function(std::string name, FunctionType* function_type) : Value(name, type) {
        auto args_type = function_type->arg_types;
        for (const auto &arg: args_type) {
            auto param = FParam(114514,arg); //! id error
            fparams.push_back(&param); 
        }
        
    }
    void print(std::ostream &os) const override;
};

struct Module : public IRPrintable {
    private :
        Module() {}
        ~Module() {}

    public :
        std::vector<GlobalVariable*> global_variables;
        std::vector<Function*> functions;
        void print(std::ostream &os) const override;
        static Module& get_instance() {
            static Module instance;
            return instance;
        }
};

struct IntConst : public Value {
    int value;

    IntConst(int value) : Value(&IR_INT), value(value) {}
    void print(std::ostream &os) const override;
};

struct CharConst : public Value {
    char value;

    CharConst(char value) : Value(&IR_CHAR), value(value) {}
    void print(std::ostream &os) const override;
};

#endif // IR_VALUE_H