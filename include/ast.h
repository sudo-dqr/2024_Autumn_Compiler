#ifndef AST_H
#define AST_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <variant> // C++17

struct Node {
    int line_number;

    Node() = default;
    Node(int line_number) : line_number(line_number) {}
    virtual void print(std::ostream &os) = 0;
};

struct FuncDef;
struct MainFunc;
struct ConstDecl;
struct VarDecl;
using Decl = std::variant<std::unique_ptr<ConstDecl>, std::unique_ptr<VarDecl>>;
struct FuncType;
struct Ident;
struct FuncFParam;
struct FuncFParams;
struct Block;
struct BType;
struct ConstDef;
struct VarDef;
struct ConstExp;
struct Exp;
struct StringConst;
struct ArrayConstInitVal;
struct ArrayInitVal;
using ConstInitVal = std::variant<std::unique_ptr<ConstExp>, std::unique_ptr<ArrayConstInitVal>, std::unique_ptr<StringConst>>;
using InitVal = std::variant<std::unique_ptr<Exp>, std::unique_ptr<ArrayInitVal>, std::unique_ptr<StringConst>>;
struct AssignStmt;
struct ExpStmt;
struct IfStmt;
struct ForStmt;
struct BreakStmt;
struct ContinueStmt;
struct ReturnStmt;
struct GetIntStmt;
struct GetCharStmt;
struct PrintfStmt;
using Stmt = std::variant<std::unique_ptr<AssignStmt>, std::unique_ptr<ExpStmt>, Block,
                        std::unique_ptr<IfStmt>, std::unique_ptr<ForStmt>, 
                        std::unique_ptr<BreakStmt>, std::unique_ptr<ContinueStmt>, 
                        std::unique_ptr<ReturnStmt>, std::unique_ptr<GetIntStmt>, 
                        std::unique_ptr<GetCharStmt>, std::unique_ptr<PrintfStmt>>;
using BlockItem = std::variant<std::unique_ptr<Decl>, std::unique_ptr<Stmt>>;
struct LVal;
struct Cond;

struct Ident : public Node {
    std::string ident;

    void print(std::ostream &os) override;
    Ident(std::string ident) : ident(ident) {}
};

struct StringConst : public Node {
    std::string str;

    void print(std::ostream &os) override;
};

struct CompUnit : public Node {
    std::vector<std::unique_ptr<FuncDef>> func_defs;
    std::vector<std::unique_ptr<Decl>> decls;
    std::unique_ptr<MainFunc> main_func;

    void print(std::ostream &os) override;
};

struct FuncDef : public Node {
    std::unique_ptr<FuncType> func_type;
    std::unique_ptr<Ident> ident;
    std::unique_ptr<FuncFParams> func_fparams;
    std::unique_ptr<Block> block;

    void print(std::ostream &os) override;
};

struct MainFunc : public Node {
    std::unique_ptr<Block> block;

    void print(std::ostream &os) override;
};

struct ConstDecl : public Node {
    std::unique_ptr<BType> btype;
    std::vector<std::unique_ptr<ConstDef>> const_defs;

    void print(std::ostream &os) override;
};

struct BType : public Node {
    std::string btype;

    void print(std::ostream &os) override;
};

struct FuncType : public Node {
    std::string func_type;

    void print(std::ostream &os) override;
};

struct VarDecl : public Node {
    std::unique_ptr<BType> btype;
    std::vector<std::unique_ptr<VarDef>> var_defs;

    void print(std::ostream &os) override;
};

struct ConstDef : public Node {
    std::unique_ptr<Ident> ident;
    std::unique_ptr<ConstExp> const_exp;
    std::unique_ptr<ConstInitVal> const_init_val;

    void print(std::ostream &os) override;
};

struct VarDef : public Node {
    std::unique_ptr<Ident> ident;
    std::unique_ptr<ConstExp> const_exp;
    std::unique_ptr<InitVal> init_val;

    void print(std::ostream &os) override;
};

struct FuncFParams : public Node {
    std::vector<std::unique_ptr<FuncFParam>> func_fparams;

    void print(std::ostream &os) override;
};

struct FuncFParam : public Node {
    std::unique_ptr<BType> btype;
    std::unique_ptr<Ident> ident;
    bool is_array;

    void print(std::ostream &os) override;
};

struct Block : public Node {
    std::vector<std::unique_ptr<BlockItem>> block_items;

    void print(std::ostream &os) override;
};

struct LVal : public Node {
    std::unique_ptr<Ident> ident;
    std::unique_ptr<Exp> exp;

    void print(std::ostream &os) override;
};

struct AssignStmt : public Node {
    std::unique_ptr<LVal> lval;
    std::unique_ptr<Exp> exp;

    void print(std::ostream &os) override;
};

struct ExpStmt : public Node {
    std::unique_ptr<Exp> exp;
};

struct IfStmt : public Node {
    std::unique_ptr<Cond> condition;
    std::unique_ptr<Stmt> if_stmt;
    std::unique_ptr<Stmt> else_stmt;

    void print(std::ostream &os) override;
};

struct ForStmt : public Node {
    std::unique_ptr<AssignStmt> assign1;
    std::unique_ptr<Cond> condition;
    std::unique_ptr<AssignStmt> assign2;
    std::unique_ptr<Stmt> stmt;

    void print(std::ostream &os) override;
};

struct BreakStmt : public Node {
    void print(std::ostream &os) override;
};

struct ContinueStmt : public Node {
    void print(std::ostream &os) override;
};

struct ReturnStmt : public Node {
    std::unique_ptr<Exp> return_exp;

    void print(std::ostream &os) override;
};

struct GetIntStmt : public Node {
    std::unique_ptr<LVal> lval;

    void print(std::ostream &os) override;
};

struct GetCharStmt : public Node {
    std::unique_ptr<LVal> lval;

    void print(std::ostream &os) override;
};

struct PrintfStmt : public Node {
    std::unique_ptr<StringConst> str;
    std::vector<std::unique_ptr<Exp>> exps;

    void print(std::ostream &os) override;
};

struct Number : public Node {
    int number;

    void print(std::ostream &os) override;
};

struct Character : public Node {
    char ch;

    void print(std::ostream &os) override;
};

struct UnaryOp : public Node {
    char op; // +/-/!

    void print(std::ostream &os) override;
};

struct FuncRParams : public Node {
    std::vector<std::unique_ptr<Exp>> exps;

    void print(std::ostream &os) override;
};

using PrimaryExp = std::variant<Exp, LVal, Number, Character>;

struct CallFunc : public Node {
    std::unique_ptr<Ident> ident;
    std::unique_ptr<FuncRParams> func_rparams;

    void print(std::ostream &os) override;
};

struct UnaryOpExp;
using UnaryExp = std::variant<PrimaryExp, CallFunc, UnaryOpExp>;
struct UnaryOpExp : public Node {
    std::unique_ptr<UnaryOp>  op;
    std::unique_ptr<UnaryExp> exp;

    void print(std::ostream &os) override;
};

struct MulUnaryExp;
using MulExp = std::variant<UnaryExp, MulUnaryExp>;
struct MulUnaryExp : public Node {
    std::unique_ptr<MulExp> mul_exp;
    char op;
    std::unique_ptr<UnaryExp> unary_exp;

    void print(std::ostream &os) override;
};

struct AddMulExp;
using AddExp = std::variant<MulExp, AddMulExp>;
struct AddMulExp : public Node {
    std::unique_ptr<AddExp> add_exp;
    char op;
    std::unique_ptr<MulExp> mul_exp;

    void print(std::ostream &os) override;
};

struct RelAddExp;
using RelExp = std::variant<AddExp, RelAddExp>;
struct RelAddExp : public Node {
    std::unique_ptr<RelExp> rel_exp;
    std::string op;
    std::unique_ptr<AddExp> add_exp;

    void print(std::ostream &os) override;
};

struct EqRelExp;
using EqExp = std::variant<RelExp, EqRelExp>;
struct EqRelExp : public Node {
    std::unique_ptr<EqExp> eq_exp;
    std::string op;
    std::unique_ptr<RelExp> rel_exp;

    void print(std::ostream &os) override;
};

struct LAndEqExp;
using LAndExp = std::variant<EqExp, LAndEqExp>;
struct LAndEqExp : public Node {
    std::unique_ptr<LAndExp> land_exp;
    std::unique_ptr<EqExp> eq_exp;

    void print(std::ostream &os) override;
};

struct LOrLAndExp;
using LOrExp = std::variant<LAndExp, LOrLAndExp>;
struct LOrLAndExp : public Node {
    std::unique_ptr<LOrExp> lor_exp;
    std::unique_ptr<LAndExp> land_exp;

    void print(std::ostream &os) override;
};

struct Exp : public Node {
    std::unique_ptr<AddExp> add_exp;

    void print(std::ostream &os) override;
};

struct ConstExp : public Node {
    std::unique_ptr<AddExp> add_exp;

    void print(std::ostream &os) override; 
};  

struct Cond : public Node {
    std::unique_ptr<LOrExp> lor_exp;

    void print(std::ostream &os) override;
};

struct ArrayInitVal : public Node {
    std::vector<std::unique_ptr<Exp>> exps;

    void print(std::ostream &os) override;
};

struct ArrayConstInitVal : public Node {
    std::vector<std::unique_ptr<ConstExp>> exps;

    void print(std::ostream &os) override;
};

#endif