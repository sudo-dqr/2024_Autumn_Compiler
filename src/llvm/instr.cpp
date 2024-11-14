#include "instr.h"

void Instruction::print(std::ostream &os) const {
    os << '\t'; // tab
}

// %xxx = alloca T
void AllocaInstr::print(std::ostream &os) const {
    Instruction::print(os);
    os << "%" << get_id() << " = alloca ";
    type->print(os);
}

// %xxx = <op> T %yyy, %zzz
void ArithmeticInstr::print(std::ostream &os) const {
    Instruction::print(os);
    os << "%" << get_id() << " = ";
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
    IntConst* intconst_ptr = nullptr;
    if (intconst_ptr = dynamic_cast<IntConst*>(op1)) intconst_ptr->print(os);
    else os << "%" << op1->get_id();
    os << ", ";
    if (intconst_ptr = dynamic_cast<IntConst*>(op2)) intconst_ptr->print(os);
    else os << "%" << op2->get_id();
}


// br i1 %cond, label %iftrue, label %iffalse
// br label %target
void BrInstr::print(std::ostream &os) const {
    Instruction::print(os);
    os << "br ";
    if (condition)
        os << "i1 %" << condition->get_id() 
        << ", label %" << true_block->get_id() 
        << ", label %" << false_block->get_id(); 
    else
        os << "label %" << true_block->get_id();
}

// ret void
// ret int32 0
// ret int32 %1
void RetInstr::print(std::ostream &os) const {
    Instruction::print(os);
    os << "ret ";
    if (return_value) {
        return_value->get_type()->print(os);
        os << " ";
        if (auto intconst_ptr = dynamic_cast<IntConst*>(return_value)) intconst_ptr->print(os);
        else os << "%" << return_value->get_id();
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
        os << "%" << get_id() << "call ";
        get_type()->print(os);
        os << " @";
    }
    os << get_name() << "(";
    for (int i = 0; i < args.size(); i++) {
        if (auto constexp_ptr = dynamic_cast<IntConst*>(args[i])) {
            os << "i32 ";
            constexp_ptr->print(os);
        } else {
            args[i]->get_type()->print(os);
            os << " %" << args[i]->get_id();
        }
        if (i != args.size() - 1) 
            os << ", ";
    }
    os << ")";
}


// %ptr = getelementptr T, T* %baseptr, V %idx1, V idx2, ...
void GetelementptrInstr::print(std::ostream &os) const {
    Instruction::print(os);
    os << "%" << get_id() << " = getelementptr ";
    get_type()->print(os);
    os << ", ";
    auto array_ptr = (PointerType*)get_type(); // i32 -> i32*
    array_ptr->print(os);
    if (auto global_ptr = dynamic_cast<GlobalVariable*>(array)) os << "@" << get_name();
    else os << "%" << get_id();
    os << ", i32 "; // index : i32
    if (auto intconst_ptr = dynamic_cast<IntConst*>(index)) intconst_ptr->print(os);
    else {
        os << "%" << index->get_id();
    }
}

// <result> = icmp eq i32 4, 5
void IcmpInstr::print(std::ostream &os) const {
    Instruction::print(os);
    os << "%" << get_id() << " = icmp ";
    switch (compare_type)
    {
        case EQ:
            os << "eq ";
            break;
        case NE:
            os << "ne ";
        case SGT:
            os << "sgt ";
        case SGE:
            os << "sge ";
        case SLT:
            os << "slt ";
        case SLE:
            os << "sle ";
        default:
            break;
    }
    op1->get_type()->print(os);
    os << " ";
    IntConst* intconst_ptr = nullptr;
    if (intconst_ptr = dynamic_cast<IntConst*>(op1)) intconst_ptr->print(os);
    else os << "%" << op1->get_id();
    if (intconst_ptr = dynamic_cast<IntConst*>(op2)) intconst_ptr->print(os);
    else os << "%" << op2->get_id();
}

// store T %val, P %ptr
void StoreInstr::print(std::ostream &os) const {
    Instruction::print(os);
    os << "store ";
    store_value->get_type()->print(os);
    os << " ";
    IntConst* intconst_ptr = nullptr;
    if (intconst_ptr = dynamic_cast<IntConst*>(store_value->get_type())) intconst_ptr->print(os);
    else os << "%" << store_value->get_id();
    os << ", ";
    GlobalVariable* global_ptr = nullptr;
    if (global_ptr = dynamic_cast<GlobalVariable*>(dst_ptr)) os << "@" << dst_ptr->get_name();
    else os << "%" << dst_ptr->get_id();
}