#ifndef IR_VALUE_H
#define IR_VALUE_H
//! This file is the definition of Value and other subclasses of Value in LLVM IR.

#include "type.h"
#include "utils.h"
#include <memory>
#include <fstream>

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
    int value;
    std::vector<int> array_values = std::vector<int>(); // int/char array
    std::string array_string = ""; // string const 全局变量可以使用字符串常量直接初始化，局部变量不可以
    bool is_printf_str = false;
    int char_cnt = 0;

    GlobalVariable() = default;
    GlobalVariable(std::string name, ValueType* dst_type, int value)  // 全局变量的类型是一个指针类型 
    : Value(name, new PointerType(dst_type)), value(value) {}
    GlobalVariable(std::string name, ValueType* dst_type, std::vector<int> array_values) 
    : Value(name, new PointerType(dst_type)), array_values(array_values) {}
    GlobalVariable(std::string name, ValueType* dst_type, std::string str, bool is_printf_str) // 字符串全局变量 
    : Value(name, new PointerType(dst_type)), array_string(str), is_printf_str(is_printf_str) {
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '\\') i++;
            char_cnt++;
        }
        // 将转义字符转换为ASCII码 \n -> \0A
        std::string str_value = "";
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '\\') {
                i++;
                switch (str[i]) {
                    case '0' : str_value += "\\00"; break;
                    case 'a' : str_value += "\\07"; break;
                    case 'b' : str_value += "\\08"; break;
                    case 't' : str_value += "\\09"; break;
                    case 'n' : str_value += "\\0A"; break;
                    case 'v' : str_value += "\\0B"; break;
                    case 'f' : str_value += "\\0C"; break;
                    case '\'' : str_value += "\\27"; break;
                    case '\"' : str_value += "\\22"; break;
                    case '\\' : str_value += "\\5C"; break;
                }
            } else str_value += str[i];
        }
        array_string = str_value;
    }

    void print(std::ostream &os) const override;
};

struct FParam : public Value { // LLVM IR中形参保存在虚拟寄存器上 首先需要将形参保存到栈上
    FParam(int id, ValueType* type) : Value("FP" + id, type, id) {}
    void print(std::ostream &os) const override;
};

struct BasicBlock : public Value {
    std::vector<Instruction*> instrs;

    BasicBlock() = default;
    BasicBlock(int id) : Value("basicblock" + id, &IR_LABEL, id) {}

    void print(std::ostream &os) const override;

};

struct Function : public Value {
    std::vector<FParam*> fparams;
    std::vector<BasicBlock*> basic_blocks;

    Function() = default;
    Function(std::string name, FunctionType* function_type) : Value(name, function_type) {
        auto args_type = function_type->arg_types;
        for (const auto &arg: args_type) {
            auto param = new FParam(Utils::get_next_counter(),arg);
            fparams.push_back(param); 
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
        void print_llvm_ir() const {
            std::ofstream llvm_ir_out("llvm_ir.txt", std::ios::trunc);
            print(llvm_ir_out);
            llvm_ir_out.close();
        }

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
    int value;

    CharConst(int value) : Value(&IR_CHAR), value(value) {}
    void print(std::ostream &os) const override;
};

#endif // IR_VALUE_H