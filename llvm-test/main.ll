declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@globalVarInt1 = dso_local global i32 4
@globalVarChar1 = dso_local global i8 100
@globalVarInt2 = dso_local global i32 5
@globalVarInt3 = dso_local global i32 6
@globalVarChar2 = dso_local global i8 101
@globalVarChar3 = dso_local global i8 102
@dqr0 = private unnamed_addr constant [9 x i8] c"22371443\00"
@dqr1 = private unnamed_addr constant [4 x i8] c"for\00"
@dqr2 = private unnamed_addr constant [20 x i8] c"lack 1, situation 1\00"
@dqr3 = private unnamed_addr constant [20 x i8] c"lack 1, situation 2\00"
@dqr4 = private unnamed_addr constant [25 x i8] c"lack 1, situation 3 and \00"
@dqr5 = private unnamed_addr constant [20 x i8] c"lack 2, situation 1\00"
@dqr6 = private unnamed_addr constant [20 x i8] c"lack 2, situation 2\00"
@dqr7 = private unnamed_addr constant [25 x i8] c"lack 2, situation 3 and \00"

define dso_local void @func1() {
0:
	%1 = alloca i32
	store i32 1, i32* %1
	ret void
}

define dso_local i32 @func2() {
0:
	ret i32 1
}

define dso_local i8 @func3() {
0:
	ret i8 97
}

define dso_local void @func4(i32 %0) {
1:
	%2 = alloca i32
	store i32 %0, i32* %2
	store i32 11, i32* %2
	ret void
}

define dso_local i32 @func5(i32 %0) {
1:
	%2 = alloca i32
	store i32 %0, i32* %2
	%3 = load i32, i32* %2
	ret i32 %3
}

define dso_local i8 @func6(i32 %0) {
1:
	%2 = alloca i32
	store i32 %0, i32* %2
	%3 = load i32, i32* %2
	%4 = add i32 %3, 1
	store i32 %4, i32* %2
	ret i8 97
}

define dso_local i32 @func7(i32 %0, i8 %1) {
2:
	%3 = alloca i32
	%4 = alloca i8
	store i32 %0, i32* %3
	store i8 %1, i8* %4
	%5 = load i32, i32* %3
	%6 = add i32 %5, 1
	store i32 %6, i32* %3
	store i8 97, i8* %4
	ret i32 0
}

define dso_local i32 @main() {
0:
	%1 = getelementptr [9 x i8], [9 x i8]* @dqr0, i32 0, i32 0
	call void @putstr(i8* %1)
	call void @putch(i32 10)
	%2 = alloca i32
	store i32 1, i32* %2
	%3 = alloca i8
	store i8 97, i8* %3
	%4 = alloca i32
	%5 = alloca i32
	%6 = alloca i8
	%7 = alloca i8
	%8 = call i32 @getint()
	store i32 %8, i32* %4
	%9 = call i32 @getchar()
	%10 = trunc i32 %9 to i8
	store i8 %10, i8* %6
	store i32 2, i32* %5
	store i8 98, i8* %7
	%11 = load i32, i32* %2
	%12 = icmp eq i32 %11, 1
	br i1 %12, label %13, label %15
13:
	%14 = load i32, i32* %2
	call void @putint(i32 %14)
	call void @putch(i32 10)
	br label %15
15:
	%16 = load i32, i32* %4
	%17 = icmp ne i32 %16, 2
	br i1 %17, label %18, label %20
18:
	%19 = load i32, i32* %4
	call void @putint(i32 %19)
	call void @putch(i32 10)
	br label %22
20:
	%21 = load i32, i32* %4
	call void @putint(i32 %21)
	call void @putch(i32 10)
	br label %22
22:
	%23 = alloca i32
	store i32 1, i32* %23
	store i32 1, i32* %23
	br label %24
24:
	%25 = load i32, i32* %23
	%26 = icmp slt i32 %25, 2
	br i1 %26, label %27, label %32
27:
	%28 = getelementptr [4 x i8], [4 x i8]* @dqr1, i32 0, i32 0
	call void @putstr(i8* %28)
	call void @putch(i32 10)
	br label %29
29:
	%30 = load i32, i32* %23
	%31 = add i32 %30, 1
	store i32 %31, i32* %23
	br label %24
32:
	store i32 1, i32* %23
	br label %33
33:
	%34 = load i32, i32* %23
	%35 = icmp slt i32 %34, 2
	br i1 %35, label %36, label %39
36:
	call void @func1()
	%37 = getelementptr [20 x i8], [20 x i8]* @dqr2, i32 0, i32 0
	call void @putstr(i8* %37)
	call void @putch(i32 10)
	br label %39
38:
	br label %33
39:
	br label %40
40:
	%41 = load i32, i32* %23
	%42 = icmp slt i32 %41, 2
	br i1 %42, label %43, label %53
43:
	%44 = call i32 @func2()
	%45 = icmp eq i32 %44, 1
	br i1 %45, label %46, label %49
46:
	%47 = getelementptr [20 x i8], [20 x i8]* @dqr3, i32 0, i32 0
	call void @putstr(i8* %47)
	call void @putch(i32 10)
	br label %53
48:
	br label %49
49:
	br label %50
50:
	%51 = load i32, i32* %23
	%52 = add i32 %51, 1
	store i32 %52, i32* %23
	br label %40
53:
	store i32 1, i32* %23
	br label %54
54:
	br label %55
55:
	%56 = call i8 @func3()
	%57 = getelementptr [25 x i8], [25 x i8]* @dqr4, i32 0, i32 0
	call void @putstr(i8* %57)
	%58 = zext i8 %56 to i32
	call void @putch(i32 %58)
	call void @putch(i32 10)
	br label %63
59:
	br label %60
60:
	%61 = load i32, i32* %23
	%62 = add i32 %61, 1
	store i32 %62, i32* %23
	br label %54
63:
	store i32 1, i32* %23
	br label %64
64:
	br label %65
65:
	call void @func4(i32 1)
	%66 = getelementptr [20 x i8], [20 x i8]* @dqr5, i32 0, i32 0
	call void @putstr(i8* %66)
	call void @putch(i32 10)
	br label %68
67:
	br label %64
68:
	br label %69
69:
	%70 = load i32, i32* %23
	%71 = icmp slt i32 %70, 2
	br i1 %71, label %72, label %76
72:
	%73 = call i32 @func5(i32 2)
	%74 = getelementptr [20 x i8], [20 x i8]* @dqr6, i32 0, i32 0
	call void @putstr(i8* %74)
	call void @putch(i32 10)
	br label %76
75:
	br label %69
76:
	br label %77
77:
	br label %78
78:
	%79 = alloca i8
	%80 = call i8 @func6(i32 3)
	store i8 %80, i8* %79
	%81 = load i8, i8* %79
	%82 = getelementptr [25 x i8], [25 x i8]* @dqr7, i32 0, i32 0
	call void @putstr(i8* %82)
	%83 = zext i8 %81 to i32
	call void @putch(i32 %83)
	call void @putch(i32 10)
	br label %88
84:
	br label %85
85:
	%86 = load i32, i32* %23
	%87 = sub i32 %86, 1
	store i32 %87, i32* %23
	br label %77
88:
	%89 = call i32 @func7(i32 1, i8 97)
	ret i32 0
}

