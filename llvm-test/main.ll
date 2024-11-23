declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@const_int_b2 = dso_local global [5 x i32] [i32 0, i32 1, i32 2, i32 3, i32 4]
@str = dso_local global [10 x i8] c"hello!\00\00\00\00"
@char_a = dso_local global i8 97
@char_b1 = dso_local global i8 98
@char_b2 = dso_local global [5 x i8] [i8 97, i8 98, i8 99, i8 100, i8 101]
@char_b3 = dso_local global [10 x i8] c"world!\00\00\00\00"
@int_b2 = dso_local global [5 x i32] zeroinitializer
@dqr0 = private unnamed_addr constant [32 x i8] c"test_stmt_getint_getchar_printf\00"
@dqr1 = private unnamed_addr constant [23 x i8] c"test_Lval_exp success!\00"
@dqr2 = private unnamed_addr constant [26 x i8] c"test_primary_exp success!\00"
@dqr3 = private unnamed_addr constant [24 x i8] c"test_unary_exp success!\00"
@dqr4 = private unnamed_addr constant [22 x i8] c"test_mul_exp success!\00"
@dqr5 = private unnamed_addr constant [22 x i8] c"test_add_exp_success!\00"
@dqr6 = private unnamed_addr constant [22 x i8] c"test_rel_exp success!\00"
@dqr7 = private unnamed_addr constant [20 x i8] c"test_Eqexp success!\00"
@dqr8 = private unnamed_addr constant [19 x i8] c"test_Lexp success!\00"
@dqr9 = private unnamed_addr constant [9 x i8] c"22371236\00"

define dso_local void @print_int_arr(i32* %0, i32 %1) {
2:
	%3 = alloca i32*
	%4 = alloca i32
	store i32* %0, i32** %3
	store i32 %1, i32* %4
	%5 = alloca i32
	store i32 0, i32* %5
	store i32 0, i32* %5
	br label %6
6:
	%7 = load i32, i32* %5
	%8 = load i32, i32* %4
	%9 = icmp slt i32 %7, %8
	br i1 %9, label %10, label %18
10:
	%11 = load i32*, i32** %3
	%12 = load i32, i32* %5
	%13 = getelementptr i32, i32* %11, i32 %12
	%14 = load i32, i32* %13
	call void @putint(i32 %14)
	call void @putch(i32 32)
	br label %15
15:
	%16 = load i32, i32* %5
	%17 = add i32 %16, 1
	store i32 %17, i32* %5
	br label %6
18:
	call void @putch(i32 10)
	ret void
}

define dso_local void @test_stmt_1_3() {
0:
	store i8 65, i8* @char_a
	ret void
}

define dso_local void @test_stmt_if_else() {
0:
	br label %1
1:
	br label %2
2:
	br label %4
3:
	br label %5
4:
	br label %5
5:
	ret void
}

define dso_local void @test_stmt_for_break_continue() {
0:
	%1 = alloca i32
	store i32 0, i32* %1
	%2 = alloca i32
	store i32 1, i32* %2
	store i32 0, i32* %1
	br label %3
3:
	%4 = load i32, i32* %1
	%5 = load i32, i32* %2
	%6 = icmp slt i32 %4, %5
	br i1 %6, label %7, label %13
7:
	%8 = load i32, i32* %1
	%9 = add i32 %8, 1
	store i32 %9, i32* %1
	br label %10
10:
	%11 = load i32, i32* %1
	%12 = add i32 %11, 1
	store i32 %12, i32* %1
	br label %3
13:
	store i32 0, i32* %1
	br label %14
14:
	%15 = load i32, i32* %1
	%16 = load i32, i32* %2
	%17 = icmp slt i32 %15, %16
	br i1 %17, label %18, label %25
18:
	br label %22
19:
	%20 = load i32, i32* %1
	%21 = add i32 %20, 1
	store i32 %21, i32* %1
	br label %22
22:
	%23 = load i32, i32* %1
	%24 = add i32 %23, 1
	store i32 %24, i32* %1
	br label %14
25:
	store i32 0, i32* %1
	br label %26
26:
	br label %27
27:
	br label %32
28:
	br label %29
29:
	%30 = load i32, i32* %1
	%31 = add i32 %30, 1
	store i32 %31, i32* %1
	br label %26
32:
	store i32 0, i32* %1
	br label %33
33:
	%34 = load i32, i32* %1
	%35 = load i32, i32* %2
	%36 = icmp slt i32 %34, %35
	br i1 %36, label %37, label %40
37:
	%38 = load i32, i32* %1
	%39 = add i32 %38, 1
	store i32 %39, i32* %1
	br label %33
40:
	br label %41
41:
	br label %42
42:
	br label %47
43:
	br label %44
44:
	%45 = load i32, i32* %1
	%46 = add i32 %45, 1
	store i32 %46, i32* %1
	br label %41
47:
	store i32 0, i32* %1
	br label %48
48:
	%49 = load i32, i32* %1
	%50 = load i32, i32* %2
	%51 = icmp slt i32 %49, %50
	br i1 %51, label %52, label %54
52:
	br label %54
53:
	br label %48
54:
	store i32 0, i32* %1
	br label %55
55:
	br label %56
56:
	br label %58
57:
	br label %55
58:
	br label %59
59:
	br label %60
60:
	br label %62
61:
	br label %59
62:
	ret void
}

define dso_local void @test_stmt_return_null() {
0:
	ret void
}

define dso_local i32 @test_stmt_return_exp() {
0:
	ret i32 1
}

define dso_local void @test_stmt_getint_getchar_printf() {
0:
	%1 = alloca i32
	store i32 1, i32* %1
	%2 = alloca i8
	store i8 97, i8* %2
	%3 = call i32 @getint()
	store i32 %3, i32* %1
	%4 = call i32 @getchar()
	%5 = trunc i32 %4 to i8
	store i8 %5, i8* %2
	%6 = getelementptr [32 x i8], [32 x i8]* @dqr0, i32 0, i32 0
	call void @putstr(i8* %6)
	call void @putch(i32 115)
	call void @putch(i32 117)
	call void @putch(i32 99)
	call void @putch(i32 99)
	call void @putch(i32 101)
	call void @putch(i32 115)
	call void @putch(i32 115)
	call void @putch(i32 10)
	ret void
}

define dso_local void @test_block() {
0:
	ret void
}

define dso_local i32 @add_int(i32 %0, i32 %1) {
2:
	%3 = alloca i32
	%4 = alloca i32
	store i32 %0, i32* %3
	store i32 %1, i32* %4
	%5 = load i32, i32* %3
	%6 = load i32, i32* %4
	%7 = add i32 %5, %6
	ret i32 %7
}

define dso_local i8 @read_char(i8 %0) {
1:
	%2 = alloca i8
	store i8 %0, i8* %2
	%3 = load i8, i8* %2
	ret i8 %3
}

define dso_local void @test_Lval_exp() {
0:
	%1 = load i8, i8* @char_a
	%2 = getelementptr [5 x i8], [5 x i8]* @char_b2, i32 0, i32 0
	%3 = load i8, i8* %2
	%4 = getelementptr [23 x i8], [23 x i8]* @dqr1, i32 0, i32 0
	call void @putstr(i8* %4)
	call void @putch(i32 10)
	ret void
}

define dso_local void @test_primary_exp() {
0:
	%1 = load i8, i8* @char_a
	%2 = getelementptr [26 x i8], [26 x i8]* @dqr2, i32 0, i32 0
	call void @putstr(i8* %2)
	call void @putch(i32 10)
	ret void
}

define dso_local void @test_func_int(i32 %0) {
1:
	%2 = alloca i32
	store i32 %0, i32* %2
	ret void
}

define dso_local void @test_func_int_arr(i32* %0) {
1:
	%2 = alloca i32*
	store i32* %0, i32** %2
	ret void
}

define dso_local void @test_func_mul_int(i32 %0, i32 %1) {
2:
	%3 = alloca i32
	%4 = alloca i32
	store i32 %0, i32* %3
	store i32 %1, i32* %4
	ret void
}

define dso_local void @test_unary_exp() {
0:
	call void @test_func_int(i32 0)
	%1 = getelementptr [5 x i32], [5 x i32]* @int_b2, i32 0, i32 0
	%2 = load i32, i32* %1
	call void @test_func_int(i32 %2)
	%3 = getelementptr [5 x i32], [5 x i32]* @int_b2, i32 0, i32 0
	call void @test_func_int_arr(i32* %3)
	call void @test_func_mul_int(i32 0, i32 1)
	br label %5
4:
	br label %5
5:
	%6 = getelementptr [24 x i8], [24 x i8]* @dqr3, i32 0, i32 0
	call void @putstr(i8* %6)
	call void @putch(i32 10)
	ret void
}

define dso_local void @test_mul_exp() {
0:
	%1 = getelementptr [22 x i8], [22 x i8]* @dqr4, i32 0, i32 0
	call void @putstr(i8* %1)
	call void @putch(i32 10)
	ret void
}

define dso_local void @test_add_exp() {
0:
	%1 = getelementptr [22 x i8], [22 x i8]* @dqr5, i32 0, i32 0
	call void @putstr(i8* %1)
	call void @putch(i32 10)
	ret void
}

define dso_local void @test_rel_exp() {
0:
	br label %1
1:
	br label %2
2:
	br label %4
3:
	br label %4
4:
	br label %5
5:
	br label %6
6:
	br label %8
7:
	br label %8
8:
	%9 = getelementptr [22 x i8], [22 x i8]* @dqr6, i32 0, i32 0
	call void @putstr(i8* %9)
	call void @putch(i32 10)
	ret void
}

define dso_local void @test_Eqexp() {
0:
	br label %1
1:
	br label %2
2:
	br label %4
3:
	br label %4
4:
	%5 = getelementptr [20 x i8], [20 x i8]* @dqr7, i32 0, i32 0
	call void @putstr(i8* %5)
	call void @putch(i32 10)
	ret void
}

define dso_local void @test_Lexp() {
0:
	br label %1
1:
	br label %2
2:
	br label %3
3:
	br label %5
4:
	br label %5
5:
	br label %6
6:
	%7 = getelementptr [19 x i8], [19 x i8]* @dqr8, i32 0, i32 0
	call void @putstr(i8* %7)
	call void @putch(i32 10)
	ret void
}

define dso_local void @test() {
0:
	call void @test_stmt_1_3()
	call void @test_stmt_for_break_continue()
	call void @test_stmt_getint_getchar_printf()
	call void @test_stmt_if_else()
	%1 = call i32 @test_stmt_return_exp()
	call void @test_stmt_return_null()
	call void @test_Eqexp()
	call void @test_Lval_exp()
	call void @test_add_exp()
	call void @test_mul_exp()
	call void @test_primary_exp()
	call void @test_rel_exp()
	call void @test_unary_exp()
	ret void
}

define dso_local i32 @main() {
0:
	%1 = getelementptr [9 x i8], [9 x i8]* @dqr9, i32 0, i32 0
	call void @putstr(i8* %1)
	call void @putch(i32 10)
	call void @test()
	ret i32 0
}

