#ifndef IR_TYPE_H
#define IR_TYPE_H

#include "ir_printable.h"

struct ValueType {
    virtual ~ValueType() = default;
};

struct ArrayType : public ValueType, public IRPrintable {
    private :
        ValueType element_type;
        int size;

    public :
        ArrayType(ValueType element_type, int size) : element_type(element_type), size(size) {}
        ValueType get_element_type() { return element_type; }
        int get_size() { return size; }
        void print(std::ostream &os) const override;   
};

struct FunctionType : public ValueType, public IRPrintable {
    private :
        ValueType return_type;
        std::vector<ValueType> arg_types;

    public :
        FunctionType(ValueType return_type, std::vector<ValueType> arg_types) : return_type(return_type), arg_types(arg_types) {}
        ValueType get_return_type() { return return_type; }
        std::vector<ValueType> get_arg_types() { return arg_types; }
        void print(std::ostream &os) const override;
};

struct IntType : public ValueType, public IRPrintable {
    static IntType INT = IntType(false);
    static IntType BOOL = IntType(true);

    private :
        bool is_logical; // int1 -> bool
        IntType(bool is_logical) : is_logical(is_logical) {}

    public :
        void print(std::ostream &os) const override;  
};

struct CharType : public ValueType, public IRPrintable {
    static CharType CHAR = CharType();

    public :
        void print(std::ostream &os) const override;
};

struct LabelType : public ValueType, public IRPrintable {
    static LabelType LABEL = LabelType();

    public :
        void print(std::ostream &os) const override;
};

struct PointerType : public ValueType, public IRPrintable {
    private :
        ValueType referenced_type;

    public :
        PointerType(ValueType referenced_type) : referenced_type(referenced_type) {}
        ValueType get_referenced_type() { return referenced_type; }
        void print(std::ostream &os) const override;    
};

struct VoidType : public ValueType, public IRPrintable {
    static VoidType VOID = VoidType();

    public :
        void print(std::ostream &os) const override;
};

#endif // IR_TYPE_H