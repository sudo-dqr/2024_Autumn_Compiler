#ifndef IR_TYPE_H
#define IR_TYPE_H

#include "ir_printable.h"
#include <vector>
#include <memory>

struct ValueType : public IRPrintable { // abstract class as a implement
    virtual void print(std::ostream &os) const = 0;
};

struct ArrayType : public ValueType {
    ValueType* element_type;
    int size;

    ArrayType(ValueType* element_type, int size) : element_type(element_type), size(size) {}
    ValueType* get_element_type() { return element_type; }
    int get_size() { return size; }
    void print(std::ostream &os) const override;   
};

struct FunctionType : public ValueType {
    ValueType* return_type;
    std::vector<ValueType*> arg_types;

    FunctionType(ValueType* return_type, std::vector<ValueType*> arg_types) : 
                    return_type(return_type), arg_types(arg_types) {}
    ValueType* get_return_type() { return return_type; }
    std::vector<ValueType*> get_arg_types() { return arg_types; }
    void print(std::ostream &os) const override;
};

struct IntType : public ValueType {
    bool is_logical; // int1 -> bool

    IntType(bool is_logical) : is_logical(is_logical) {}
    void print(std::ostream &os) const override;  
};
static IntType IR_INT = IntType(false);
static IntType IR_BOOL = IntType(true);

struct CharType : public ValueType {
    void print(std::ostream &os) const override;
};
static CharType IR_CHAR = CharType();

struct LabelType : public ValueType {
    void print(std::ostream &os) const override;
};
static LabelType IR_LABEL = LabelType();

struct PointerType : public ValueType {
    ValueType* referenced_type;

    PointerType(ValueType* referenced_type) : referenced_type(referenced_type) {}
    ValueType* get_referenced_type() { return referenced_type; }
    void print(std::ostream &os) const override;    
};

struct VoidType : public ValueType {
    void print(std::ostream &os) const override;
};
static VoidType IR_VOID = VoidType();

#endif // IR_TYPE_H