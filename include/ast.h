#ifndef AST_H
#define AST_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <variant> // C++17
#include "token.h""

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
using ConstInitVal = std::variant<std::unique_ptr<ConstExp>, std::vector<std::unique_ptr<ConstExp>>, std::unique_ptr<StringConst>>;
using InitVal = std::variant<std::unique_ptr<Exp>, std::vector<std::unique_ptr<Exp>>, std::unique_ptr<StringConst>>;
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
    std::unique_ptr<Token> ident;

    Ident(std::unique_ptr<Token> ident);
    void print(std::ostream &os) override;
};

struct StringConst : public Node {
    std::unique_ptr<Token> str;

    StringConst(std::unique_ptr<Token> str);
    void print(std::ostream &os) override;
};

struct CompUnit : public Node {
    std::vector<std::unique_ptr<FuncDef>> func_defs;
    std::vector<std::unique_ptr<Decl>> decls;
    std::unique_ptr<MainFunc> main_func;

    CompUnit(std::vector<std::unique_ptr<FuncDef>> func_defs, std::vector<std::unique_ptr<Decl>> decls, std::unique_ptr<MainFunc> main_func);
    void print(std::ostream &os) override;
};

struct FuncDef : public Node {
    std::unique_ptr<FuncType> func_type;
    std::unique_ptr<Ident> ident;
    std::unique_ptr<FuncFParams> func_fparams;
    std::unique_ptr<Block> block;

    FuncDef(std::unique_ptr<FuncType> func_type, std::unique_ptr<Ident> ident, std::unique_ptr<FuncFParams> func_fparams, std::unique_ptr<Block> block);
    void print(std::ostream &os) override;
};

struct MainFunc : public Node {
    std::unique_ptr<Block> block;

    MainFunc(std::unique_ptr<Block> block);
    void print(std::ostream &os) override;
};

struct ConstDecl : public Node {
    std::unique_ptr<BType> btype;
    std::vector<std::unique_ptr<ConstDef>> const_defs;

    ConstDecl(std::unique_ptr<BType> btype, std::vector<std::unique_ptr<ConstDef>> const_defs);
    void print(std::ostream &os) override;
};

struct BType : public Node {
    std::unique_ptr<Token> btype;

    BType(std::unique_ptr<Token> btype);
    void print(std::ostream &os) override;
};

struct FuncType : public Node {
    std::unique_ptr<Token> func_type;

    FuncType(std::unique_ptr<Token> func_type);
    void print(std::ostream &os) override;
};

struct VarDecl : public Node {
    std::unique_ptr<BType> btype;
    std::vector<std::unique_ptr<VarDef>> var_defs;

    VarDecl(std::unique_ptr<BType> btype, std::vector<std::unique_ptr<VarDef>> var_defs);
    void print(std::ostream &os) override;
};

struct ConstDef : public Node {
    std::unique_ptr<Ident> ident;
    std::unique_ptr<ConstExp> const_exp;
    std::unique_ptr<ConstInitVal> const_init_val;

    ConstDef(std::unique_ptr<Ident> ident, std::unique_ptr<ConstExp> const_exp, std::unique_ptr<ConstInitVal> const_init_val);
    void print(std::ostream &os) override;
};

struct VarDef : public Node {
    std::unique_ptr<Ident> ident;
    std::unique_ptr<ConstExp> const_exp;
    std::unique_ptr<InitVal> init_val;

    VarDef(std::unique_ptr<Ident> ident, std::unique_ptr<ConstExp> const_exp, std::unique_ptr<InitVal> init_val);
    void print(std::ostream &os) override;
};

struct FuncFParams : public Node {
    std::vector<std::unique_ptr<FuncFParam>> func_fparams;

    FuncFParams(std::vector<std::unique_ptr<FuncFParam>> func_fparams);
    void print(std::ostream &os) override;
};

struct FuncFParam : public Node {
    std::unique_ptr<BType> btype;
    std::unique_ptr<Ident> ident;
    bool is_array;

    FuncFParam(std::unique_ptr<BType> btype, std::unique_ptr<Ident> ident, bool is_array);
    void print(std::ostream &os) override;
};

struct Block : public Node {
    std::vector<std::unique_ptr<BlockItem>> block_items;

    Block(std::vector<std::unique_ptr<BlockItem>> block_items);
    void print(std::ostream &os) override;
};

struct LVal : public Node {
    std::unique_ptr<Ident> ident;
    std::unique_ptr<Exp> exp;

    LVal(std::unique_ptr<Ident> ident, std::unique_ptr<Exp> exp);
    void print(std::ostream &os) override;
};

struct AssignStmt : public Node {
    std::unique_ptr<LVal> lval;
    std::unique_ptr<Exp> exp;

    AssignStmt(std::unique_ptr<LVal> lval, std::unique_ptr<Exp> exp);
    void print(std::ostream &os) override;
};

struct ExpStmt : public Node {
    std::unique_ptr<Exp> exp;

    ExpStmt(std::unique_ptr<Exp> exp);
    void print(std::ostream &os) override;
};

struct IfStmt : public Node {
    std::unique_ptr<Cond> condition;
    std::unique_ptr<Stmt> if_stmt;
    std::unique_ptr<Stmt> else_stmt;

    IfStmt(std::unique_ptr<Cond> condition, std::unique_ptr<Stmt> if_stmt, std::unique_ptr<Stmt> else_stmt);
    void print(std::ostream &os) override;
};

struct ForStmt : public Node {
    std::unique_ptr<AssignStmt> assign1;
    std::unique_ptr<Cond> condition;
    std::unique_ptr<AssignStmt> assign2;
    std::unique_ptr<Stmt> stmt;

    ForStmt(std::unique_ptr<AssignStmt> assign1, std::unique_ptr<Cond> condition, std::unique_ptr<AssignStmt> assign2, std::unique_ptr<Stmt> stmt);
    void print(std::ostream &os) override;
};

struct BreakStmt : public Node {
    std::unique_ptr<Token> break_token;

    BreakStmt(std::unique_ptr<Token> break_token);
    void print(std::ostream &os) override;
};

struct ContinueStmt : public Node {
    std::unique_ptr<Token> continue_token;

    ContinueStmt(std::unique_ptr<Token> continue_token);
    void print(std::ostream &os) override;
};

struct ReturnStmt : public Node {
    std::unique_ptr<Token> return_token;
    std::unique_ptr<Exp> return_exp;

    ReturnStmt(std::unique_ptr<Token> return_token, std::unique_ptr<Exp> return_exp);
    void print(std::ostream &os) override;
};

struct GetIntStmt : public Node {
    std::unique_ptr<LVal> lval;

    GetIntStmt(std::unique_ptr<LVal> lval);
    void print(std::ostream &os) override;
};

struct GetCharStmt : public Node {
    std::unique_ptr<LVal> lval;

    GetCharStmt(std::unique_ptr<LVal> lval);
    void print(std::ostream &os) override;
};

struct PrintfStmt : public Node {
    std::unique_ptr<StringConst> str;
    std::vector<std::unique_ptr<Exp>> exps;

    PrintfStmt(std::unique_ptr<StringConst> str, std::vector<std::unique_ptr<Exp>> exps);
    void print(std::ostream &os) override;
};

struct Number : public Node {
    std::unique_ptr<Token> num;

    Number(std::unique_ptr<Token> number);
    void print(std::ostream &os) override;
};

struct Character : public Node {
    std::unique_ptr<Token> ch;

    Character(std::unique_ptr<Token> ch);
    void print(std::ostream &os) override;
};

struct UnaryOp : public Node {
    std::unique_ptr<Token> op;

    UnaryOp(std::unique_ptr<Token> op);
    void print(std::ostream &os) override;
};

struct FuncRParams : public Node {
    std::vector<std::unique_ptr<Exp>> exps;

    FuncRParams(std::vector<std::unique_ptr<Exp>> exps);
    void print(std::ostream &os) override;
};

using PrimaryExp = std::variant<std::unique_ptr<Exp>, std::unique_ptr<LVal>, std::unique_ptr<Number>, std::unique_ptr<Character>>;

struct UnaryExp : public Node{
    // primary_exp | call_func | unary_op unary_exp
    std::unique_ptr<PrimaryExp> primary_exp;
    std::unique_ptr<Ident> ident;
    std::unique_ptr<FuncRParams> func_rparams;
    std::unique_ptr<UnaryOp> unary_op;
    std::unique_ptr<UnaryExp> unary_exp; //!需要使用指针来避免无限递归

    void print(std::ostream &os) override;
    UnaryExp(std::unique_ptr<PrimaryExp> primary_exp);
    UnaryExp(std::unique_ptr<Ident> ident, std::unique_ptr<FuncRParams> func_rparams);
    UnaryExp(std::unique_ptr<UnaryOp> unary_op, std::unique_ptr<UnaryExp> unary_exp);
};

struct MulExp : public Node {
    //  MulExp → UnaryExp | MulExp ('*' | '/' | '%') UnaryExp 
    std::unique_ptr<MulExp> mulexp; //!需要使用指针来避免无限递归
    std::unique_ptr<Token> op;
    std::unique_ptr<UnaryExp> unaryexp;

    void print(std::ostream &os) override;
    MulExp(std::unique_ptr<MulExp> mulexp, std::unique_ptr<Token> op, std::unique_ptr<UnaryExp> unaryexp);
    MulExp(std::unique_ptr<UnaryExp> unaryexp);
};

struct AddExp : public Node {
    std::unique_ptr<AddExp> addexp;
    std::unique_ptr<Token> op;
    std::unique_ptr<MulExp> mulexp;

    void print(std::ostream &os) override;
    AddExp(std::unique_ptr<AddExp> addexp, std::unique_ptr<Token> op, std::unique_ptr<MulExp> mulexp);
    AddExp(std::unique_ptr<MulExp> mulexp);
};

struct RelExp : public Node {
    std::unique_ptr<RelExp> relexp;
    std::unique_ptr<Token> op;
    std::unique_ptr<AddExp> addexp;

    void print(std::ostream &os) override;
    RelExp(std::unique_ptr<RelExp> relexp, std::unique_ptr<Token> op, std::unique_ptr<AddExp> addexp);
    RelExp(std::unique_ptr<AddExp> addexp);
};

struct EqExp : public Node {
    std::unique_ptr<EqExp> eqexp;
    std::unique_ptr<Token> op;
    std::unique_ptr<RelExp> relexp;

    void print(std::ostream &os) override;
    EqExp(std::unique_ptr<EqExp> eqexp, std::unique_ptr<Token> op, std::unique_ptr<RelExp> relexp);
    EqExp(std::unique_ptr<RelExp> relexp);
};

struct LAndExp : public Node {
    std::unique_ptr<LAndExp> landexp;
    // op is &&
    std::unique_ptr<EqExp> eqexp;

    void print(std::ostream &os) override;
    LAndExp(std::unique_ptr<LAndExp> landexp, std::unique_ptr<EqExp> eqexp);
    LAndExp(std::unique_ptr<EqExp> eqexp);
};

struct LOrExp : public Node {
    std::unique_ptr<LOrExp> lorexp;
    // op is ||
    std::unique_ptr<LAndExp> landexp;

    void print(std::ostream &os) override;
    LOrExp(std::unique_ptr<LOrExp> lorexp, std::unique_ptr<LAndExp> landexp);
    LOrExp(std::unique_ptr<LAndExp> landexp);
};

struct Exp : public Node {
    std::unique_ptr<AddExp> add_exp;

    Exp(std::unique_ptr<AddExp> add_exp);
    void print(std::ostream &os) override;
};

struct ConstExp : public Node {
    std::unique_ptr<AddExp> add_exp;

    ConstExp(std::unique_ptr<AddExp> add_exp);
    void print(std::ostream &os) override; 
};  

struct Cond : public Node {
    std::unique_ptr<LOrExp> lor_exp;

    Cond(std::unique_ptr<LOrExp> lor_exp);
    void print(std::ostream &os) override;
};
#endif