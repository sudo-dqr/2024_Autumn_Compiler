#ifndef IR_TYPE_H
#define IR_TYPE_H

#include "ir_printable.h"
#include <vector>
#include <memory>

struct ValueType : public IRPrintable { // abstract class as a implement
    virtual void print(std::ostream &os) const = 0;
};

struct ArrayType : public ValueType {
    private :
        std::unique_ptr<ValueType> element_type;
        int size;

    public :
        ArrayType(std::unique_ptr<ValueType> element_type, int size) : element_type(std::move(element_type)), size(size) {}
        std::unique_ptr<ValueType> get_element_type() { return std::move(element_type); }
        int get_size() { return size; }
        void print(std::ostream &os) const override;   
};

struct FunctionType : public ValueType {
    private :
        std::unique_ptr<ValueType> return_type;
        std::vector<std::unique_ptr<ValueType>> arg_types;

    public :
        FunctionType(std::unique_ptr<ValueType> return_type, std::vector<std::unique_ptr<ValueType>> arg_types) : 
                        return_type(std::move(return_type)), arg_types(std::move(arg_types)) {}
        std::unique_ptr<ValueType> get_return_type() { return std::move(return_type); }
        std::vector<std::unique_ptr<ValueType>> get_arg_types() { return std::move(arg_types); }
        void print(std::ostream &os) const override;
};

struct IntType : public ValueType {
    private :
        bool is_logical; // int1 -> bool

    public :
        IntType(bool is_logical) : is_logical(is_logical) {}
        void print(std::ostream &os) const override;  
};
static IntType INT = IntType(false);
static IntType BOOL = IntType(true);

struct CharType : public ValueType {
    public :
        void print(std::ostream &os) const override;
};
static CharType CHAR = CharType();

struct LabelType : public ValueType {
    public :
        void print(std::ostream &os) const override;
};
static LabelType LABEL = LabelType();

struct PointerType : public ValueType {
    private :
        std::unique_ptr<ValueType> referenced_type;

    public :
        PointerType(std::unique_ptr<ValueType> referenced_type) : referenced_type(std::move(referenced_type)) {}
        std::unique_ptr<ValueType> get_referenced_type() { return std::move(referenced_type); }
        void print(std::ostream &os) const override;    
};

struct VoidType : public ValueType {
    public :
        void print(std::ostream &os) const override;
};
static VoidType VOID = VoidType();

#endif // IR_TYPE_H