#include "parser.h"

void Parser::next_token() {
    auto& buf = is_recovering ? recoverybuf : buffer; //! 注意这里要引用 否则会创建副本
    if (!backbuf.empty()) { // 将预读的token从backbuf移回buffer
        buf.push_back(backbuf.back());
        backbuf.pop_back();
    } else if (lexer.has_next()) {
        buf.push_back(lexer.next());
    } else {
        std::cout << "Error! No Lexer Read!" << std::endl;
    }

    // backbuf是不断消耗的 不需要关心内存
    // buffer需要不断从头部移除旧元素来控制内存
    if (buffer.size() > 5) {
        buffer.pop_front();
    }
}

Token Parser::get_curtoken() {
    return (is_recovering ? recoverybuf : buffer).back();
}

void Parser::unget_token() { 
    auto& buf = is_recovering ? recoverybuf : buffer;
    std::cout << "BackBuf in unget_token : " << buf.back().to_string() << std::endl;
    backbuf.push_back(buf.back());
    buf.pop_back();
}

void Parser::start_recovery() {
    is_recovering = true;
    if (!buffer.empty()) { // 将buffer中的最新token复制一个到recoverybuf中(LVal的起始token)
        recoverybuf.push_back(buffer.back());
    }
}

void Parser::done_recovery() { // 将recoverybuf中的token恢复到backbuf中重新解析
    is_recovering = false;
    while (!recoverybuf.empty()) { // 逆序填入backbuf, buffer读取的是正序
        backbuf.push_back(recoverybuf.back());
        recoverybuf.pop_back();
    }
    if (!buffer.empty()) {
        backbuf.pop_back(); // 这个元素是start时从buffer复制到recoverybuf的
    }
}

void Parser::abort_recovery() { // 将recoverybuf中的token放到buffer中，相当于正常解析过了，不再重新解析(不再恢复)
    is_recovering = false;
    if (!buffer.empty()) {
        recoverybuf.pop_front(); // 这个元素是start时从buffer复制到recoverybuf的
    }
    while (!recoverybuf.empty()) { // 顺序填入buffer
        buffer.push_back(recoverybuf.front());
        recoverybuf.pop_front();
    }
    while (buffer.size() > 5) { // 控制buffer的大小
        buffer.pop_front();
    }
}

std::unique_ptr<CompUnit> Parser::parse() {
    return parse_comp_unit();
}

std::unique_ptr<CompUnit> Parser::parse_comp_unit() {
    next_token();
    auto decls = std::vector<std::unique_ptr<Decl>>();
    auto func_defs = std::vector<std::unique_ptr<FuncDef>>();
    while (comp_unit_judge_next_type() == CompUnitType::DECL) {
        decls.push_back(parse_decl());
    }
    while (comp_unit_judge_next_type() == CompUnitType::FUNCDEF) {
        func_defs.push_back(parse_funcdef());
    }
    auto main_func = parse_mainfunc();
    return std::make_unique<CompUnit>(std::move(func_defs), std::move(decls), std::move(main_func));
}

Parser::CompUnitType Parser::comp_unit_judge_next_type() {
    Token t = get_curtoken();
    if (t.get_type() == Token::CONSTTK) {
        return CompUnitType::DECL;
    } else if (t.get_type() == Token::VOIDTK) {
        return CompUnitType::FUNCDEF;
    }
    next_token();
    t = get_curtoken();
    if (t.get_type() == Token::MAINTK) {
        return CompUnitType::MAINFUNC;
    }
    next_token();
    t = get_curtoken();
    unget_token(); // 回退预读的token
    unget_token();
    if (t.get_type() == Token::LPARENT) {
        return CompUnitType::FUNCDEF;
    } else {
        return CompUnitType::DECL;
    }
}

std::unique_ptr<Decl> Parser::parse_decl() {
    Token t = get_curtoken();
    if (t.get_type() == Token::CONSTTK) {
        auto const_decl = parse_constdecl();
        return std::make_unique<Decl>(std::in_place_type<ConstDecl>, std::move(*const_decl));
    } else {
        auto var_decl = parse_vardecl();
        return std::make_unique<Decl>(std::in_place_type<VarDecl>,std::move(*var_decl));
    }
}

std::unique_ptr<ConstDecl> Parser::parse_constdecl() {
    next_token(); // 跳过const
    auto btype = parse_btype();
    auto const_defs = std::vector<std::unique_ptr<ConstDef>>();
    const_defs.push_back(parse_constdef());
    while (get_curtoken().get_type() == Token::COMMA) { // ConstDef {, ConstDef}
        next_token();
        const_defs.push_back(parse_constdef());
    }
    if (get_curtoken().get_type() == Token::SEMICN) { // ;结尾
        next_token();
    } else { // i error
        unget_token();
        report_error(get_curtoken().get_line_number(), 'i');
        next_token();
    }
    return std::make_unique<ConstDecl>(std::move(btype), std::move(const_defs));
}

std::unique_ptr<VarDecl> Parser::parse_vardecl() {
    auto btype = parse_btype();
    auto var_defs = std::vector<std::unique_ptr<VarDef>>();
    var_defs.push_back(parse_vardef());
    while (get_curtoken().get_type() == Token::COMMA) { // VarDef {, VarDef}
        next_token();
        var_defs.push_back(parse_vardef());
    }
    if (get_curtoken().get_type() == Token::SEMICN) {
        next_token();
    } else { // i error
        unget_token();
        report_error(get_curtoken().get_line_number(), 'i');
        next_token();
    }
    return std::make_unique<VarDecl>(std::move(btype), std::move(var_defs));
}

std::unique_ptr<BType> Parser::parse_btype() {
    auto res = std::make_unique<BType>(std::make_unique<Token>(get_curtoken()));
    next_token();
    return std::move(res);
}

std::unique_ptr<ConstDef> Parser::parse_constdef() {
    auto ident = parse_ident();
    std::unique_ptr<ConstExp> const_exp;
    std::unique_ptr<ConstInitVal> const_init_val;
    if (get_curtoken().get_type() == Token::LBRACK) {
        next_token();
        const_exp = parse_constexp();
        if (get_curtoken().get_type() == Token::RBRACK) {
            next_token();
        } else { // k  error
            unget_token();
            report_error(get_curtoken().get_line_number(), 'k');
            next_token();
        }
    }
    next_token();
    const_init_val = parse_const_initval();
    return std::make_unique<ConstDef>(std::move(ident), std::move(const_exp), std::move(const_init_val));
}

std::unique_ptr<VarDef> Parser::parse_vardef() {
    auto ident = parse_ident();
    std::unique_ptr<ConstExp> const_exp;
    std::unique_ptr<InitVal> init_val;
    if (get_curtoken().get_type() == Token::LBRACK) {
        next_token();
        const_exp = parse_constexp();
        if (get_curtoken().get_type() == Token::RBRACK) {
            next_token();
        } else { // k error
            unget_token();
            report_error(get_curtoken().get_line_number(), 'k');
            next_token();
        }
    }
    if (get_curtoken().get_type() == Token::ASSIGN) {
        next_token();
        init_val = parse_initval();
    } else {
        init_val = nullptr;
    }
    return std::make_unique<VarDef>(std::move(ident), std::move(const_exp), std::move(init_val));
}

std::unique_ptr<ConstExp> Parser::parse_constexp() {
    return std::make_unique<ConstExp>(parse_addexp());
}

std::unique_ptr<ConstInitVal> Parser::parse_const_initval() {
    if (get_curtoken().get_type() == Token::STRCON) {
        auto stringconst = parse_stringconst();
        return std::make_unique<ConstInitVal>(std::in_place_type<StringConst>,std::move(*stringconst));
    } else if (get_curtoken().get_type() == Token::LBRACE) {
        auto vec = std::vector<std::unique_ptr<ConstExp>>();
        next_token(); // 跳过 {
        if (get_curtoken().get_type() != Token::RBRACE) {
            vec.push_back(parse_constexp());
            while (get_curtoken().get_type() == Token::COMMA) {
                next_token();
                vec.push_back(parse_constexp());
            }
        }
        next_token(); // 跳过 }
        return std::make_unique<ConstInitVal>(std::in_place_type<ConstExps>,ConstExps(std::move(vec)));
    } else {
        auto const_exp = parse_constexp();
        return std::make_unique<ConstInitVal>(std::in_place_type<ConstExp>,std::move(*const_exp));
    }
}

std::unique_ptr<InitVal> Parser::parse_initval() {
    std::cout << "InitVal : curtoken is " << get_curtoken().to_string() << std::endl;
    if (get_curtoken().get_type() == Token::STRCON) {
        auto stringconst = parse_stringconst();
        return std::make_unique<InitVal>(std::in_place_type<StringConst>,std::move(*stringconst));
    } else if (get_curtoken().get_type() == Token::LBRACE) {
        auto vec = std::vector<std::unique_ptr<Exp>>();
        next_token(); // 跳过 {
        if (get_curtoken().get_type() != Token::RBRACE) {
            vec.push_back(parse_exp());
            while (get_curtoken().get_type() == Token::COMMA) {
                next_token();
                vec.push_back(parse_exp());
            }
        }
        next_token(); // 跳过 }
        return std::make_unique<InitVal>(std::in_place_type<Exps>,Exps(std::move(vec)));
    } else {
        auto exp = parse_exp();
        return std::make_unique<InitVal>(std::in_place_type<Exp>,std::move(*exp));
    }
}

std::unique_ptr<FuncDef> Parser::parse_funcdef() {
    auto func_type = parse_functype();
    auto ident = parse_ident();
    std::unique_ptr<FuncFParams> func_fparams;
    std::unique_ptr<Block> block;
    next_token(); // 跳过 (
    if (get_curtoken().get_type() == Token::RPARENT) {
        func_fparams = nullptr;
        next_token();
    } else {
        func_fparams = parse_funcfparams();
        if (get_curtoken().get_type() == Token::RPARENT) {
            next_token();
        } else { // j error
            unget_token();
            report_error(get_curtoken().get_line_number(), 'j');
            next_token();
        }
    }
    block = parse_block();
    return std::make_unique<FuncDef>(std::move(func_type), std::move(ident), std::move(func_fparams), std::move(block));
}

std::unique_ptr<FuncType> Parser::parse_functype() {
    auto res = std::make_unique<FuncType>(std::make_unique<Token>(get_curtoken()));
    next_token();
    return std::move(res);
}

std::unique_ptr<Ident> Parser::parse_ident() {
    auto res = std::make_unique<Ident>(std::make_unique<Token>(get_curtoken()));
    next_token();
    return std::move(res);
}

std::unique_ptr<StringConst> Parser::parse_stringconst() {
    auto res = std::make_unique<StringConst>(std::make_unique<Token>(get_curtoken()));
    next_token();
    return std::move(res);
}

std::unique_ptr<MainFunc> Parser::parse_mainfunc() {
    //std::cout << "MainFunc : curtoken is " << get_curtoken().get_token() << std::endl;
    next_token(); // 跳过main
    next_token(); // 跳过(
    if (get_curtoken().get_type() == Token::RPARENT) {
        next_token();
    } else { // j error
        unget_token();
        report_error(get_curtoken().get_line_number(), 'j');
        next_token();
    }
    return std::make_unique<MainFunc>(parse_block());
}

std::unique_ptr<FuncFParams> Parser::parse_funcfparams() {
    auto func_fparams = std::vector<std::unique_ptr<FuncFParam>>();
    func_fparams.push_back(parse_funcfparam());
    while (get_curtoken().get_type() == Token::COMMA) {
        next_token();
        func_fparams.push_back(parse_funcfparam());
    }
    return std::make_unique<FuncFParams>(std::move(func_fparams));
}

std::unique_ptr<FuncFParam> Parser::parse_funcfparam() {
    auto btype = parse_btype();
    auto ident = parse_ident();
    bool is_array = false;
    if (get_curtoken().get_type() == Token::LBRACK) {
        next_token();
        if (get_curtoken().get_type() == Token::RBRACK) {
            next_token();
        } else { // k error
            unget_token();
            report_error(get_curtoken().get_line_number(), 'k');
            next_token();
        }
        is_array = true;
    }
    return std::make_unique<FuncFParam>(std::move(btype), std::move(ident), is_array);
}

std::unique_ptr<Block> Parser::parse_block() {
    std::cout << "Block : curtoken is " << get_curtoken().get_token() << "in line " << get_curtoken().get_line_number() <<std::endl;
    next_token(); // 跳过{
    auto block_items = std::vector<std::unique_ptr<BlockItem>>();
    while (get_curtoken().get_type() != Token::RBRACE) {
        block_items.push_back(parse_blockitem());
    }
    next_token(); // 跳过}
    return std::make_unique<Block>(std::move(block_items));
}

std::unique_ptr<BlockItem> Parser::parse_blockitem() {
    std::cout << "BlockItem : curtoken is " << get_curtoken().get_token() << " in line " << get_curtoken().get_line_number() <<std::endl;
    if (get_curtoken().get_type() == Token::INTTK 
        || get_curtoken().get_type() == Token::CHARTK
        || get_curtoken().get_type() == Token::CONSTTK) {
        auto decl = parse_decl();
        return std::make_unique<BlockItem>(std::in_place_type<Decl>,std::move(*decl));
    } else {
        auto stmt = parse_stmt();
        return std::make_unique<BlockItem>(std::in_place_type<Stmt>,std::move(*stmt));
    }
}

std::unique_ptr<Stmt> Parser::parse_stmt() {
    if (get_curtoken().get_type() == Token::LBRACE) { // Block
        auto block = parse_block();
        return std::make_unique<Stmt>(std::in_place_type<BlockStmt>,BlockStmt(std::move(block)));
    } else if (get_curtoken().get_type() == Token::IFTK) { //IF
        auto if_stmt = parse_ifstmt();
        return std::make_unique<Stmt>(std::in_place_type<IfStmt>,std::move(*if_stmt));
    } else if (get_curtoken().get_type() == Token::FORTK) { //FOR
        auto for_stmt = parse_forstmt();
        return std::make_unique<Stmt>(std::in_place_type<ForStmt>,std::move(*for_stmt));
    } else if (get_curtoken().get_type() == Token::BREAKTK) { //BREAK
        auto break_stmt = parse_breakstmt();
        return std::make_unique<Stmt>(std::in_place_type<BreakStmt>,std::move(*break_stmt));
    } else if (get_curtoken().get_type() == Token::CONTINUETK) { // CONTINUE
        auto continue_stmt = parse_continuestmt();
        return std::make_unique<Stmt>(std::in_place_type<ContinueStmt>,std::move(*continue_stmt));
    } else if (get_curtoken().get_type() == Token::RETURNTK) { // RETURN 
        auto return_stmt = parse_returnstmt();
        return std::make_unique<Stmt>(std::in_place_type<ReturnStmt>,std::move(*return_stmt));
    } else if (get_curtoken().get_type() == Token::PRINTFTK) { // PRINTF
        auto printf_stmt = parse_printfstmt();
        return std::make_unique<Stmt>(std::in_place_type<PrintfStmt>,std::move(*printf_stmt));
    } else if (get_curtoken().get_type() == Token::LPARENT ||
                get_curtoken().get_type() == Token::PLUS ||
                get_curtoken().get_type() == Token::MINU || 
                get_curtoken().get_type() == Token::NOT ||
                get_curtoken().get_type() == Token::INTCON ||
                get_curtoken().get_type() == Token::CHRCON) { // EXP 注意这里不能有IDENFR
        auto exp = parse_exp();
        if (get_curtoken().get_type() == Token::SEMICN) {
            next_token();
        } else { // i error
            unget_token();
            report_error(get_curtoken().get_line_number(), 'i');
            next_token();
        }
        return std::make_unique<Stmt>(std::in_place_type<ExpStmt>,ExpStmt(std::move(exp)));
    } else if (get_curtoken().get_type() == Token::SEMICN) { // [EXP];(无exp)
        next_token();
        return std::make_unique<Stmt>(std::in_place_type<ExpStmt>,ExpStmt(nullptr));
    } else { // IDENTFR : may be rule 1,2,8,9
        Token t1 = get_curtoken();
        next_token();
        Token t2 = get_curtoken();
        unget_token();
        if (t1.get_type() == Token::IDENFR && t2.get_type() == Token::LPARENT) { // rule2 ident()
            auto exp = parse_exp();
            if (get_curtoken().get_type() == Token::SEMICN) {
                next_token(); // 读到LVal的起始token
            } else { // i error
                unget_token();
                report_error(get_curtoken().get_line_number(), 'i');
                next_token();
            }
            return std::make_unique<Stmt>(std::in_place_type<ExpStmt>,ExpStmt(std::move(exp)));
        } else { // 1,2,9,10
            // 2余下的情况中一定以LVal开头, 1,9,10一定以LVal开头
            start_recovery(); // 将LVal读到recoverybuf中
            auto lval = parse_lval();
            if (get_curtoken().get_type() == Token::ASSIGN) { // rule 1,9,10
                abort_recovery(); // 不再恢复
                next_token(); // 跳过=
                if (get_curtoken().get_type() == Token::GETINTTK ||
                    get_curtoken().get_type() == Token::GETCHARTK ) { // rule 9,10
                    bool getint_flag = (get_curtoken().get_type() == Token::GETINTTK);
                    next_token(); // 跳过getint/getchar
                    next_token(); // 跳过(
                    if (get_curtoken().get_type() == Token::RPARENT) {
                        next_token();
                    } else { // j error
                        unget_token();
                        report_error(get_curtoken().get_line_number(), 'j');
                        next_token();
                    }
                    if (get_curtoken().get_type() == Token::SEMICN) {
                        next_token();
                    } else { // i error
                        unget_token();
                        report_error(get_curtoken().get_line_number(), 'i');
                        next_token();
                    }
                    if (getint_flag) {
                        return std::make_unique<Stmt>(std::in_place_type<GetIntStmt>,GetIntStmt(std::move(lval)));
                    } else {
                        return std::make_unique<Stmt>(std::in_place_type<GetCharStmt>,GetCharStmt(std::move(lval)));
                    }
                } else { // rule 1
                    auto exp = parse_exp();
                    if (get_curtoken().get_type() == Token::SEMICN) {
                        next_token();
                    } else { // i error
                        unget_token();
                        report_error(get_curtoken().get_line_number(), 'i');
                        next_token();
                    }
                    return std::make_unique<Stmt>(std::in_place_type<AssignStmt>,AssignStmt(std::move(lval), std::move(exp)));
                }
            } else { // rule 2
                done_recovery(); // token恢复到backbuf中重新读取
                auto exp = parse_exp();
                if (get_curtoken().get_type() == Token::SEMICN) {
                    next_token();
                } else { // i error
                    unget_token();
                    report_error(get_curtoken().get_line_number(), 'i');
                    next_token();
                }
                return std::make_unique<Stmt>(std::in_place_type<ExpStmt>,ExpStmt(std::move(exp)));
            }
        }
    }
}

//! 关于else {1, 2, 9, 10} 部分的分析
//! 对于规则 1, 9, 10一定以LVal开头
//! 对于规则 2, 排除了之前的情况后，开头元素也为LVal
//! 可以首先试着读一个LVal, 然后判断后续的token
//! 但是问题是：对于规则1,9,10 读到的LVal是有用的，但是对于规则2，读到的LVal是无用的(规则2需要保存Exp)
//! 需要设置一个机制，缓存读到的LVal, 如果判断得到的规则是1,9,10，那么读到的LVal是有用的, 将tokens放入buffer中，相当已经读过了
//! 如果判断得到的规则是2, 那么读到的LVal是无用的，将tokens放入backbuf中，相当于没有读过, 重新读取, 解析成Exp
//! 设置一个Recovery模式, 增加一个Recoverybuffer, 保存读取的LVal中的tokens
//! 如果判断得到的规则是1,9,10, 将Recoverybuffer中的tokens放入buffer中
//! 如果判断得到的规则是2, 将Recoverybuffer中的tokens放入backbuf中, 重新读取
//! 为什么不能接着用backbuf? 因为我们要回复的其实就是LVal的tokens, 需要有一个明确的起始点

std::unique_ptr<IfStmt> Parser::parse_ifstmt() {
    std::cout << "IfStmt : curtoken is " << get_curtoken().get_token() << std::endl;
    next_token(); // 跳过if
    next_token(); // 跳过(
    auto condition = parse_cond();
    if (get_curtoken().get_type() == Token::RPARENT) {
        next_token();
    } else { // j error
        unget_token();
        report_error(get_curtoken().get_line_number(), 'j');
        next_token();
    }
    auto if_stmt = parse_stmt();
    std::unique_ptr<Stmt> else_stmt;
    if (get_curtoken().get_type() == Token::ELSETK) {
        next_token();
        else_stmt = parse_stmt();
    } else {
        else_stmt = nullptr;
    }
    return std::make_unique<IfStmt>(std::move(condition), std::move(if_stmt), std::move(else_stmt));
}

std::unique_ptr<Cond> Parser::parse_cond() {
    std::cout << "Cond : curtoken is " << get_curtoken().get_token() << std::endl;
    return std::make_unique<Cond>(parse_lorexp());
}

std::unique_ptr<ForStmt> Parser::parse_forstmt() {
    next_token(); // 跳过for
    next_token(); // 跳过(
    std::unique_ptr<AssignStmt> assign1;
    std::unique_ptr<Cond> condition;
    std::unique_ptr<AssignStmt> assign2;
    std::unique_ptr<Stmt> stmt;
    // 第一个子句
    if (get_curtoken().get_type() == Token::SEMICN) {
        assign1 = nullptr;
    } else {
        assign1 = parse_assignstmt();
    }
    next_token(); // 跳过;
    // 第二个子句
    if (get_curtoken().get_type() == Token::SEMICN) {
        condition = nullptr;
    } else {
        condition = parse_cond();
    }
    next_token(); // 跳过;
    // 第三个子句
    if (get_curtoken().get_type() == Token::RPARENT) {
        assign2 = nullptr;
    } else {
        assign2 = parse_assignstmt();
    }
    next_token(); // 跳过)
    stmt = parse_stmt();
    return std::make_unique<ForStmt>(std::move(assign1), std::move(condition), std::move(assign2), std::move(stmt));
}

std::unique_ptr<BreakStmt> Parser::parse_breakstmt() {
    Token break_token = get_curtoken();
    next_token(); // 跳过break
    if (get_curtoken().get_type() == Token::SEMICN) {
        next_token();
    } else { // l error
        unget_token();
        report_error(get_curtoken().get_line_number(), 'l');
        next_token();
    }
    return std::make_unique<BreakStmt>(std::make_unique<Token>(break_token));
}

std::unique_ptr<ContinueStmt> Parser::parse_continuestmt() {
    Token continue_token = get_curtoken();
    next_token(); // 跳过continue
    if (get_curtoken().get_type() == Token::SEMICN) {
        next_token();
    } else { // l error
        unget_token();
        report_error(get_curtoken().get_line_number(), 'l');
        next_token();
    }
    return std::make_unique<ContinueStmt>(std::make_unique<Token>(continue_token));
}

std::unique_ptr<ReturnStmt> Parser::parse_returnstmt() {
    auto return_token = get_curtoken();
    std::unique_ptr<Exp> return_exp;
    next_token(); // 跳过return
    // 实际上是推导Exp的FIRST集 最终划归到求UnaryExp的FIRST集
    if (get_curtoken().get_type() == Token::IDENFR ||
        get_curtoken().get_type() == Token::LPARENT ||
        get_curtoken().get_type() == Token::PLUS ||
        get_curtoken().get_type() == Token::MINU || 
        get_curtoken().get_type() == Token::NOT ||
        get_curtoken().get_type() == Token::INTCON ||
        get_curtoken().get_type() == Token::CHRCON) {
        return_exp = parse_exp();
    } else {
        return_exp = nullptr;
    }
    if (get_curtoken().get_type() == Token::SEMICN) {
        next_token();
    } else { // i error
        unget_token();
        report_error(get_curtoken().get_line_number(), 'i');
        next_token();
    }
    return std::make_unique<ReturnStmt>(std::make_unique<Token>(return_token), std::move(return_exp));
}

std::unique_ptr<PrintfStmt> Parser::parse_printfstmt() {
    next_token(); // 跳过printf
    next_token(); // 跳过(
    auto str = parse_stringconst();
    auto exps = std::vector<std::unique_ptr<Exp>>();
    while (get_curtoken().get_type() == Token::COMMA) {
        next_token();
        exps.push_back(parse_exp());
    }
    if (get_curtoken().get_type() == Token::RPARENT) {
        next_token();
    } else { // j error
        unget_token();
        report_error(get_curtoken().get_line_number(), 'j');
        next_token();
    }
    if (get_curtoken().get_type() == Token::SEMICN) {
        next_token();
    } else { // i error
        unget_token();
        report_error(get_curtoken().get_line_number(), 'i');
        next_token();
    }
    return std::make_unique<PrintfStmt>(std::move(str), std::move(exps));
}

std::unique_ptr<Exp> Parser::parse_exp() {
    std::cout << "Exp : curtoken is " << get_curtoken().to_string() << std::endl;
    return std::make_unique<Exp>(parse_addexp());
}

std::unique_ptr<AssignStmt> Parser::parse_assignstmt() {
    auto lval = parse_lval();
    next_token(); // 跳过=
    auto exp = parse_exp();
    return std::make_unique<AssignStmt>(std::move(lval), std::move(exp));
}

std::unique_ptr<LVal> Parser::parse_lval() {
    std::cout << "LVal : curtoken is " << get_curtoken().to_string() << std::endl;
    auto ident = parse_ident();
    std::unique_ptr<Exp> exp;
    if (get_curtoken().get_type() == Token::LBRACK) {
        next_token();
        exp = parse_exp();
        if (get_curtoken().get_type() == Token::RBRACK) {
            next_token();
        } else { // k error
            unget_token();
            report_error(get_curtoken().get_line_number(), 'k');
            next_token();
        }
    } else {
        exp = nullptr;
    }
    return std::make_unique<LVal>(std::move(ident), std::move(exp));
}

std::unique_ptr<Number> Parser::parse_number() {
    std::cout << "Number : curtoken is " << get_curtoken().get_token() << std::endl;
    auto res = std::make_unique<Number>(std::make_unique<Token>(get_curtoken()));
    next_token();
    std::cout << "Number : outtoken is " << get_curtoken().get_token() << std::endl;
    return std::move(res);
}

std::unique_ptr<Character> Parser::parse_character() {
    auto res = std::make_unique<Character>(std::make_unique<Token>(get_curtoken()));
    next_token();
    return std::move(res);
}

std::unique_ptr<PrimaryExp> Parser::parse_primaryexp() {
    std::cout << "PrimaryExp : curtoken is " << get_curtoken().to_string() << std::endl;
    if (get_curtoken().get_type() == Token::LPARENT) {
        next_token(); // 跳过(
        auto exp = parse_exp();
        if (get_curtoken().get_type() == Token::RPARENT) {
            next_token();
        } else { // j error
            unget_token();
            report_error(get_curtoken().get_line_number(), 'j');
            next_token();
        }
        return std::make_unique<PrimaryExp>(std::in_place_type<Exp>,std::move(*exp));
    } else if (get_curtoken().get_type() == Token::IDENFR) {
        auto lval = parse_lval();
        return std::make_unique<PrimaryExp>(std::in_place_type<LVal>,std::move(*lval));
    } else if (get_curtoken().get_type() == Token::INTCON) {
        auto num = parse_number();
        return std::make_unique<PrimaryExp>(std::in_place_type<Number>,std::move(*num));
    } else {
        auto ch = parse_character();
        return std::make_unique<PrimaryExp>(std::in_place_type<Character>,std::move(*ch));
    }
}

std::unique_ptr<UnaryOp> Parser::parse_unaryop() {
    auto res = std::make_unique<UnaryOp>(std::make_unique<Token>(get_curtoken()));
    next_token();
    return std::move(res);
}

std::unique_ptr<UnaryExp> Parser::parse_unaryexp() {
    std::cout << "UnaryExp : curtoken is " << get_curtoken().to_string() << std::endl;
    if (get_curtoken().get_type() == Token::PLUS ||
        get_curtoken().get_type() == Token::MINU ||
        get_curtoken().get_type() == Token::NOT) {
        auto unary_op = parse_unaryop();
        auto unary_exp = parse_unaryexp();
        return std::make_unique<UnaryExp>(std::move(unary_op), std::move(unary_exp));
    } else {
        Token t1 = get_curtoken();
        next_token();
        Token t2 = get_curtoken();
        unget_token();
        if (t1.get_type() == Token::IDENFR && t2.get_type() == Token::LPARENT) {
            return parse_callfunc();
        } else {
            return std::make_unique<UnaryExp>(parse_primaryexp());
        }
    }
}

std::unique_ptr<UnaryExp> Parser::parse_callfunc() {
    auto ident = parse_ident();
    std::unique_ptr<FuncRParams> func_rparams;
    next_token(); // 跳过(
    if (get_curtoken().get_type() != Token::RPARENT) {
        func_rparams = parse_funcrparams();
    } else {
        func_rparams = nullptr;
    }
    if (get_curtoken().get_type() == Token::RPARENT) {
        next_token();
    } else { // j error
        unget_token();
        report_error(get_curtoken().get_line_number(), 'j');
        next_token();
    }
    return std::make_unique<UnaryExp>(std::move(ident), std::move(func_rparams));
}

std::unique_ptr<FuncRParams> Parser::parse_funcrparams() {
    auto exps = std::vector<std::unique_ptr<Exp>>();
    exps.push_back(parse_exp());
    while (get_curtoken().get_type() == Token::COMMA) {
        next_token();
        exps.push_back(parse_exp());
    }
    return std::make_unique<FuncRParams>(std::move(exps));
}

std::unique_ptr<MulExp> Parser::parse_mulexp() {
    std::cout << "MulExp : cur token is " << get_curtoken().get_token() << std::endl;
    std::unique_ptr<MulExp> mul_exp = std::make_unique<MulExp>(parse_unaryexp());
    while (get_curtoken().get_type() == Token::MULT ||
            get_curtoken().get_type() == Token::DIV ||
            get_curtoken().get_type() == Token::MOD) {
        Token op = get_curtoken();
        next_token();
        auto unaryexp = parse_unaryexp();
        mul_exp = std::make_unique<MulExp>(std::move(mul_exp), std::make_unique<Token>(op),std::move(unaryexp));
    }
    return std::move(mul_exp);
}

std::unique_ptr<AddExp> Parser::parse_addexp() {
    std::cout << "AddExp : cur token is " << get_curtoken().get_token() << std::endl;
    auto add_exp = std::make_unique<AddExp>(parse_mulexp());
    while (get_curtoken().get_type() == Token::PLUS ||
            get_curtoken().get_type() == Token::MINU ) {
        Token op = get_curtoken();
        next_token();
        auto mul_exp = parse_mulexp();
        add_exp = std::make_unique<AddExp>(std::move(add_exp), std::make_unique<Token>(op), std::move(mul_exp));            
    }
    //std::cout << "AddExp : jump token is " << get_curtoken().get_token() << "in line " << get_curtoken().get_line_number() << std::endl;
    return std::move(add_exp);
}

std::unique_ptr<RelExp> Parser::parse_relexp() {
    std::cout << "RelExp : cur token is " << get_curtoken().get_token() << std::endl;
    auto rel_exp = std::make_unique<RelExp>(parse_addexp());
    while (get_curtoken().get_type() == Token::GRE ||
            get_curtoken().get_type() == Token::GEQ ||
            get_curtoken().get_type() == Token::LEQ ||
            get_curtoken().get_type() == Token::LSS ) {
        Token op = get_curtoken();
        next_token();
        auto add_exp = parse_addexp();
        rel_exp = std::make_unique<RelExp>(std::move(rel_exp), std::make_unique<Token>(op), std::move(add_exp));        
    }
    return std::move(rel_exp);
}

std::unique_ptr<EqExp> Parser::parse_eqexp() {
    std::cout << "EqExp : cur token is " << get_curtoken().get_token() << std::endl;
    auto eq_exp = std::make_unique<EqExp>(parse_relexp());
    while (get_curtoken().get_type() == Token::EQL ||
            get_curtoken().get_type() == Token::NEQ ) {
        Token op = get_curtoken();
        next_token();
        auto rel_exp = parse_relexp();
        eq_exp = std::make_unique<EqExp>(std::move(eq_exp), std::make_unique<Token>(op), std::move(rel_exp));
    }
    return std::move(eq_exp);
}

std::unique_ptr<LAndExp> Parser::parse_landexp() {
    std::cout << "LAndExp : cur token is " << get_curtoken().get_token() << std::endl;
    auto land_exp = std::make_unique<LAndExp>(parse_eqexp());
    while (get_curtoken().get_type() == Token::AND) {
        next_token();
        auto eq_exp = parse_eqexp();
        land_exp = std::make_unique<LAndExp>(std::move(land_exp), std::move(eq_exp));
    }
    return std::move(land_exp);
}

std::unique_ptr<LOrExp> Parser::parse_lorexp() {
    std::cout << "LOrExp : cur token is " << get_curtoken().get_token() << std::endl;
    auto lor_exp = std::make_unique<LOrExp>(parse_landexp());
    while (get_curtoken().get_type() == Token::OR) {
        next_token();
        auto land_exp = parse_landexp();
        lor_exp = std::make_unique<LOrExp>(std::move(lor_exp), std::move(land_exp));
    }
    return std::move(lor_exp);
}


