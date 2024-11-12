#ifndef IR_VALUE_H
#define IR_VALUE_H
//! This file is the definition of Value and other subclasses of Value in LLVM IR.

#include "type.h"
#include "ir_printable.h"
#include <memory>

struct Value : public IRPrintable {
    protected :
        std::string name;
        std::unique_ptr<ValueType> type;
        int id; // 虚拟寄存器号
        Value(std::string name, std::unique_ptr<ValueType> type, int id) : name(name), type(std::move(type)), id(id) {}
        Value(std::string name, std::unique_ptr<ValueType> type) : name(name), type(std::move(type)), id(-1) {}
        Value(int id, std::unique_ptr<ValueType> type) : name("v" + id), type(std::move(type)), id(id) {}
    
    public :
        std::string get_name() { return name; }
        std::unique_ptr<ValueType> get_type() { return std::move(type); }
        int get_id() { return id; }
        void print(std::ostream &os) const override;
};

struct User : public Value {
    protected :
        User(std::string name, std::unique_ptr<ValueType> type, int id) : Value(name, std::move(type), id) {}

    public :
        void print(std::ostream &os) const override;
};

struct GlobalVariable : public Value {
    private :
        int init_value; // 普通变量 
        std::vector<int> int_array_init_values; // int array
        std::vector<char> char_array_init_values; // char array

    public :
        GlobalVariable(std::string name, std::unique_ptr<ValueType> type, int id, int init_value) 
        : Value(name, std::move(type), id), init_value(init_value) {}
        GlobalVariable(std::string name, std::unique_ptr<ValueType> type, int id, std::vector<int> int_array_init_values) 
        : Value(name, std::move(type), id), int_array_init_values(int_array_init_values) {}
        GlobalVariable(std::string name, std::unique_ptr<ValueType> type, int id, std::vector<char> char_array_init_values) 
        : Value(name, std::move(type), id), char_array_init_values(char_array_init_values) {}
        int get_init_value() { return init_value; }
        std::vector<int> get_int_array_init_values() { return int_array_init_values; }
        std::vector<char> get_char_array_init_values() { return char_array_init_values; }
        void print(std::ostream &os) const override;
};

struct FParam : public Value { // LLVM IR中形参保存在虚拟寄存器上 首先需要将形参保存到栈上
    public :
        FParam(int id, std::unique_ptr<ValueType> type) : Value("FP" + id, std::move(type), id) {}
        void print(std::ostream &os) const override;
};

struct BasicBlock : public Value {

};

struct Function : public Value {
    private :
        std::vector<std::unique_ptr<FParam>> fparams;
        std::vector<std::unique_ptr<BasicBlock>> basic_blocks;
};

struct Module : public IRPrintable {
    private :
        std::vector<std::unique_ptr<GlobalVariable>> global_variables;
        std::vector<std::unique_ptr<Function>> functions;

    public :
        Module(std::vector<std::unique_ptr<GlobalVariable>> global_variables, std::vector<std::unique_ptr<Function>> functions) 
        : global_variables(std::move(global_variables)), functions(std::move(functions)) {}
        std::vector<std::unique_ptr<GlobalVariable>> get_global_variables() { return std::move(global_variables); }
        std::vector<std::unique_ptr<Function>> get_functions() { return std::move(functions); }
        void print(std::ostream &os) const override;
};


#endif // IR_VALUE_H