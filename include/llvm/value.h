#ifndef IR_VALUE_H
#define IR_VALUE_H
//! This file is the definition of Value and other subclasses of Value in LLVM IR.

#include "type.h"
#include "ir_printable.h"
#include <memory>

// 前向声明 Instruction 类 头文件需要另外包含在.cpp文件中
struct Instruction;

struct Value : public IRPrintable {
    protected :
        std::string name;
        ValueType* type;
        int id; // 虚拟寄存器号
        Value(std::string name, ValueType* type, int id) : name(name), type(type), id(id) {}
        Value(std::string name, ValueType* type) : name(name), type(type), id(-1) {}
        Value(int id, ValueType* type) : name("v" + id), type(type), id(id) {}
    
    public :
        std::string get_name() { return name; }
        ValueType* get_type() { return type; }
        int get_id() { return id; }
        void print(std::ostream &os) const override;
};

struct User : public Value {
    protected :
        User(std::string name, ValueType* type, int id) : Value(name, type, id) {}
        User(std::string name, ValueType* type) : Value(name, type) {}
        User(int id, ValueType* type) : Value(id, type) {}

    public :
        void print(std::ostream &os) const override;
};

struct GlobalVariable : public Value {
    private :
        int init_value; // 普通变量 
        std::vector<int> int_array_init_values; // int array
        std::vector<char> char_array_init_values; // char array
        std::string char_array_init_string; // string const

    public :
        GlobalVariable(std::string name, ValueType* type, int init_value) 
        : Value(name, type), init_value(init_value) {}
        GlobalVariable(std::string name, ValueType* type, std::vector<int> int_array_init_values) 
        : Value(name, type), int_array_init_values(int_array_init_values) {}
        GlobalVariable(std::string name, ValueType* type, std::vector<char> char_array_init_values) 
        : Value(name, type), char_array_init_values(char_array_init_values) {}
        GlobalVariable(std::string name, ValueType* type, std::string str) 
        : Value(name, type), char_array_init_string(str) {}
        int get_init_value() { return init_value; }
        std::vector<int> get_int_array_init_values() { return int_array_init_values; }
        std::vector<char> get_char_array_init_values() { return char_array_init_values; }
        void print(std::ostream &os) const override;
};

struct FParam : public Value { // LLVM IR中形参保存在虚拟寄存器上 首先需要将形参保存到栈上
    public :
        FParam(int id, ValueType* type) : Value("FP" + id, type, id) {}
        void print(std::ostream &os) const override;
};

struct BasicBlock : public Value {
    private :
        std::vector<Instruction*> instrs;

    public :
        BasicBlock(int id);
        void append_instr(Instruction* instr) { instrs.push_back(instr); }
        std::vector<Instruction*> get_instrs() { return instrs; }
        bool is_empty() { return instrs.empty(); }
        void print(std::ostream &os) const override;

};

struct Function : public Value {
    private :
        std::vector<FParam*> fparams;
        std::vector<BasicBlock*> basic_blocks;

    public :
        std::vector<FParam*> get_fparams() { return fparams; }
        std::vector<BasicBlock*> get_basic_blocks() { return basic_blocks; }
};

struct Module : public IRPrintable {
    private :
        Module() {}
        ~Module() {}
        std::vector<GlobalVariable*> global_variables;
        std::vector<Function*> functions;

    public :
        void append_global_variable(GlobalVariable* global_variable) { global_variables.push_back(global_variable); }
        void append_function(Function* function) { functions.push_back(function); }
        std::vector<GlobalVariable*> get_global_variables() { return global_variables; }
        std::vector<Function*> get_functions() { return functions; }
        void print(std::ostream &os) const override;
        static Module& get_instance() {
            static Module instance;
            return instance;
        }
};

#endif // IR_VALUE_H