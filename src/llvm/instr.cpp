#include "instr.h"

void Instruction::print(std::ostream &os) const {
    os << '\t'; // tab
}

// %xxx = alloca T
void AllocaInstr::print(std::ostream &os) const {
    Instruction::print(os);
    os << "%" << id << " = alloca ";
    type->print(os);
}

// %xxx = <op> T %yyy, %zzz
void ArithmeticInstr::print(std::ostream &os) const {
    Instruction::print(os);
    os << "%" << id << " = ";
    switch (arith_type) {
        case ADD:
            os << "add ";
            break;
        case SUB:
            os << "sub ";
            break;
        case MUL:
            os << "mul ";
            break;
        case SDIV:
            os << "sdiv ";
            break;
        case SREM:
            os << "srem ";
            break;
    }
    type->print(os); // 这里应该只有int char类型在运算前会先转成int
    os << " ";
    IntConst* intconst_ptr = nullptr;
    if (intconst_ptr = dynamic_cast<IntConst*>(op1)) intconst_ptr->print(os);
    else os << "%" << op1->id;
    os << ", ";
    if (intconst_ptr = dynamic_cast<IntConst*>(op2)) intconst_ptr->print(os);
    else os << "%" << op2->id;
}


// br i1 %cond, label %iftrue, label %iffalse
// br label %target
void BrInstr::print(std::ostream &os) const {
    Instruction::print(os);
    os << "br ";
    if (condition)
        os << "i1 %" << condition->id 
        << ", label %" << true_block->id 
        << ", label %" << false_block->id; 
    else
        os << "label %" << true_block->id;
}

// ret void
// ret int32 0
// ret int32 %1
void RetInstr::print(std::ostream &os) const {
    Instruction::print(os);
    os << "ret ";
    if (return_value) {
        return_value->type->print(os);
        os << " ";
        if (auto intconst_ptr = dynamic_cast<IntConst*>(return_value)) intconst_ptr->print(os);
        else os << "%" << return_value->id;
    }
    else os << "void";
}

// call void @putint(i32 1)
// call void @putint(i32 %result)`
// %xxx = call T @fff(T1, %p1, T2, %p2)
void CallInstr::print(std::ostream &os) const {
    Instruction::print(os);
    if (auto void_ptr = dynamic_cast<VoidType*>(type)) {
        os << "call void @";
    } else {
        os << "%" << id << "= call ";
        type->print(os);
        os << " @";
    }
    os << this->function->name << "(";
    for (int i = 0; i < args.size(); i++) {
        if (auto constexp_ptr = dynamic_cast<IntConst*>(args[i])) {
            os << "i32 ";
            constexp_ptr->print(os);
        } else {
            args[i]->type->print(os);
            os << " %" << args[i]->id;
        }
        if (i != args.size() - 1) 
            os << ", ";
    }
    os << ")";
}


// %ptr = getelementptr T, T* %baseptr, V %idx1, V idx2, ...
void GetelementptrInstr::print(std::ostream &os) const {
    Instruction::print(os);
    os << "%" << id << " = getelementptr ";
    array->type->print(os);
    os << ", ";
    array->type->print(os);
    os << "* ";
    if (auto global_ptr = dynamic_cast<GlobalVariable*>(array)) os << "@" << array->name;
    else os << "%" << id;
    os << ", "; // index : i32
    for (const auto &indice : indices) {
        os << "i32 ";
        IntConst* intconst_ptr = dynamic_cast<IntConst*>(indice);
        if (intconst_ptr) intconst_ptr->print(os);
        else os << "%" << indice->id;
        if (&indice != &indices.back()) os << ", ";
    }
}

// <result> = icmp eq i32 4, 5
void IcmpInstr::print(std::ostream &os) const {
    Instruction::print(os);
    os << "%" << id << " = icmp ";
    switch (compare_type)
    {
        case EQ:
            os << "eq ";
            break;
        case NE:
            os << "ne ";
            break;
        case SGT:
            os << "sgt ";
            break;
        case SGE:
            os << "sge ";
            break;
        case SLT:
            os << "slt ";
            break;
        case SLE:
            os << "sle ";
        default:
            break;
    }
    op1->type->print(os);
    os << " ";
    IntConst* intconst_ptr = nullptr;
    if (intconst_ptr = dynamic_cast<IntConst*>(op1)) intconst_ptr->print(os);
    else os << "%" << op1->id;
    if (intconst_ptr = dynamic_cast<IntConst*>(op2)) intconst_ptr->print(os);
    else os << "%" << op2->id;
}

// store T %val, P %ptr
void StoreInstr::print(std::ostream &os) const {
    Instruction::print(os);
    os << "store ";
    store_value->type->print(os);
    os << " ";
    IntConst* intconst_ptr = nullptr;
    if (intconst_ptr = dynamic_cast<IntConst*>(store_value->type)) intconst_ptr->print(os);
    else os << "%" << store_value->id;
    os << ", ";
    dst_ptr->type->print(os);
    os << " ";
    GlobalVariable* global_ptr = nullptr;
    if (global_ptr = dynamic_cast<GlobalVariable*>(dst_ptr)) os << "@" << dst_ptr->name;
    else os << "%" << dst_ptr->id;
}

// %val = load T, P %ptr
void LoadInstr::print(std::ostream &os) const {
    Instruction::print(os);
    os << "%" << id << " = load ";
    ((PointerType*)type)->referenced_type->print(os);
    os << ", ";
    src_ptr->type->print(os);
    os << " ";
    GlobalVariable* global_ptr = nullptr;
    if (global_ptr = dynamic_cast<GlobalVariable*>(src_ptr)) os << "@" << src_ptr->name;
    else os << "%" << src_ptr->id;
}

// %X = zext i32 257 to i64
void ZextInstr::print(std::ostream &os) const {
    Instruction::print(os);
    os << "%" << id << " = zext ";
    operand->type->print(os);
    os << " ";
    os << "%" << operand->type << " to ";
    type->print(os);
}

void TruncInstr::print(std::ostream &os) const {
    Instruction::print(os);
    os << "%" << id << " = trunc ";
    operand->type->print(os);
    os << " ";
    os << "%" << operand->id << " to ";
    type->print(os);
}