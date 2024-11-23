declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@MININT = dso_local global i32 -2147483647
@MINCHAR = dso_local global i8 32
@ZERO_TO_TEN = dso_local global [11 x i32] [i32 0, i32 1, i32 2, i32 3, i32 4, i32 5, i32 6, i32 7, i32 8, i32 9, i32 10]
@NO_USE1 = dso_local global [11 x i32] [i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0]
@NO_USE2 = dso_local global [11 x i32] [i32 0, i32 1, i32 2, i32 3, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0]
@ABCDEFGHIJ = dso_local global [11 x i8] [i8 65, i8 66, i8 67, i8 68, i8 69, i8 70, i8 71, i8 72, i8 73, i8 74, i8 0]
@NO_USE3 = dso_local global [11 x i8] [i8 0, i8 0, i8 0, i8 0, i8 0, i8 0, i8 0, i8 0, i8 0, i8 0, i8 0]
@NO_USE4 = dso_local global [11 x i8] c"NO_USE4\00\00\00\00"
@fibonacci = dso_local global [15 x i32] zeroinitializer
@dqr0 = private unnamed_addr constant [17 x i8] c"Fibonacci Array \00"
@dqr1 = private unnamed_addr constant [4 x i8] c" : \00"
@dqr2 = private unnamed_addr constant [3 x i8] c"  \00"
@dqr3 = private unnamed_addr constant [4 x i8] c" : \00"
@dqr4 = private unnamed_addr constant [3 x i8] c"  \00"
@dqr5 = private unnamed_addr constant [4 x i8] c" : \00"
@dqr6 = private unnamed_addr constant [9 x i8] c"22371298\00"

define dso_local void @cal_fibonacci() {
0:
	%1 = getelementptr [15 x i32], [15 x i32]* @fibonacci, i32 0, i32 1
	store i32 1, i32* %1
	%2 = alloca i32
	store i32 2, i32* %2
	br label %3
3:
	%4 = load i32, i32* %2
	%5 = icmp slt i32 %4, 15
	br i1 %5, label %6, label %21
6:
	%7 = load i32, i32* %2
	%8 = getelementptr [15 x i32], [15 x i32]* @fibonacci, i32 0, i32 %7
	%9 = load i32, i32* %2
	%10 = sub i32 %9, 1
	%11 = getelementptr [15 x i32], [15 x i32]* @fibonacci, i32 0, i32 %10
	%12 = load i32, i32* %11
	%13 = load i32, i32* %2
	%14 = sub i32 %13, 2
	%15 = getelementptr [15 x i32], [15 x i32]* @fibonacci, i32 0, i32 %14
	%16 = load i32, i32* %15
	%17 = add i32 %12, %16
	store i32 %17, i32* %8
	br label %18
18:
	%19 = load i32, i32* %2
	%20 = add i32 %19, 1
	store i32 %20, i32* %2
	br label %3
21:
	ret void
}

define dso_local void @print_fibonacci_n(i32 %0, i32 %1, i32 %2) {
3:
	%4 = alloca i32
	%5 = alloca i32
	%6 = alloca i32
	store i32 %0, i32* %4
	store i32 %1, i32* %5
	store i32 %2, i32* %6
	%7 = load i32, i32* %4
	%8 = load i32, i32* %4
	%9 = getelementptr [15 x i32], [15 x i32]* @fibonacci, i32 0, i32 %8
	%10 = load i32, i32* %9
	%11 = load i32, i32* %5
	%12 = load i32, i32* %5
	%13 = getelementptr [15 x i32], [15 x i32]* @fibonacci, i32 0, i32 %12
	%14 = load i32, i32* %13
	%15 = load i32, i32* %6
	%16 = load i32, i32* %6
	%17 = getelementptr [15 x i32], [15 x i32]* @fibonacci, i32 0, i32 %16
	%18 = load i32, i32* %17
	%19 = getelementptr [17 x i8], [17 x i8]* @dqr0, i32 0, i32 0
	call void @putstr(i8* %19)
	call void @putint(i32 %7)
	%20 = getelementptr [4 x i8], [4 x i8]* @dqr1, i32 0, i32 0
	call void @putstr(i8* %20)
	call void @putint(i32 %10)
	%21 = getelementptr [3 x i8], [3 x i8]* @dqr2, i32 0, i32 0
	call void @putstr(i8* %21)
	call void @putint(i32 %11)
	%22 = getelementptr [4 x i8], [4 x i8]* @dqr3, i32 0, i32 0
	call void @putstr(i8* %22)
	call void @putint(i32 %14)
	%23 = getelementptr [3 x i8], [3 x i8]* @dqr4, i32 0, i32 0
	call void @putstr(i8* %23)
	call void @putint(i32 %15)
	%24 = getelementptr [4 x i8], [4 x i8]* @dqr5, i32 0, i32 0
	call void @putstr(i8* %24)
	call void @putint(i32 %18)
	call void @putch(i32 10)
	ret void
}

define dso_local i32 @main() {
0:
	%1 = getelementptr [9 x i8], [9 x i8]* @dqr6, i32 0, i32 0
	call void @putstr(i8* %1)
	call void @putch(i32 10)
	%2 = alloca i32
	%3 = call i32 @getint()
	store i32 %3, i32* %2
	%4 = alloca i32
	%5 = call i32 @getint()
	store i32 %5, i32* %4
	%6 = alloca i32
	%7 = call i32 @getint()
	store i32 %7, i32* %6
	call void @cal_fibonacci()
	%8 = load i32, i32* %2
	%9 = icmp sgt i32 %8, 14
	br i1 %9, label %16, label %10
10:
	%11 = load i32, i32* %4
	%12 = icmp sgt i32 %11, 14
	br i1 %12, label %16, label %13
13:
	%14 = load i32, i32* %6
	%15 = icmp sgt i32 %14, 14
	br i1 %15, label %16, label %17
16:
	br label %21
17:
	%18 = load i32, i32* %2
	%19 = load i32, i32* %4
	%20 = load i32, i32* %6
	call void @print_fibonacci_n(i32 %18, i32 %19, i32 %20)
	br label %21
21:
	%22 = alloca i32
	store i32 2147483647, i32* %22
	%23 = alloca i32
	%24 = getelementptr [11 x i32], [11 x i32]* @ZERO_TO_TEN, i32 0, i32 10
	%25 = load i32, i32* %24
	store i32 %25, i32* %23
	%26 = alloca i32
	store i32 1, i32* %26
	br label %27
27:
	%28 = load i32, i32* %26
	%29 = icmp slt i32 %28, 2
	br i1 %29, label %30, label %35
30:
	%31 = load i32, i32* %26
	call void @putint(i32 %31)
	call void @putch(i32 10)
	br label %32
32:
	%33 = load i32, i32* %26
	%34 = add i32 %33, 1
	store i32 %34, i32* %26
	br label %27
35:
	store i32 2, i32* %26
	br label %36
36:
	br label %37
37:
	%38 = load i32, i32* %26
	%39 = icmp eq i32 %38, 5
	br i1 %39, label %52, label %40
40:
	%41 = load i32, i32* %26
	%42 = icmp sle i32 %41, 6
	br i1 %42, label %52, label %43
43:
	%44 = load i32, i32* %26
	%45 = icmp sge i32 %44, 90
	br i1 %45, label %52, label %46
46:
	%47 = load i32, i32* %26
	%48 = icmp eq i32 %47, 100
	br i1 %48, label %52, label %49
49:
	%50 = load i32, i32* %26
	%51 = icmp ne i32 %50, 80
	br i1 %51, label %52, label %54
52:
	br label %58
53:
	br label %54
54:
	br label %55
55:
	%56 = load i32, i32* %26
	%57 = add i32 %56, 1
	store i32 %57, i32* %26
	br label %36
58:
	store i32 2, i32* %26
	br label %59
59:
	%60 = load i32, i32* %26
	%61 = icmp sle i32 %60, 5
	br i1 %61, label %62, label %68
62:
	%63 = load i32, i32* %26
	%64 = icmp ne i32 %63, 90
	br i1 %64, label %65, label %67
65:
	br label %68
66:
	br label %67
67:
	br label %59
68:
	store i32 100, i32* %26
	br label %69
69:
	br label %70
70:
	%71 = load i32, i32* %26
	%72 = icmp sgt i32 %71, 10
	br i1 %72, label %73, label %75
73:
	br label %79
74:
	br label %75
75:
	br label %76
76:
	%77 = load i32, i32* %26
	%78 = add i32 %77, 1
	store i32 %78, i32* %26
	br label %69
79:
	br label %80
80:
	%81 = load i32, i32* %26
	%82 = icmp sgt i32 %81, 50
	br i1 %82, label %83, label %97
83:
	%84 = load i32, i32* %26
	%85 = icmp sgt i32 %84, 80
	br i1 %85, label %86, label %89
86:
	%87 = load i32, i32* %26
	%88 = icmp slt i32 %87, 120
	br i1 %88, label %92, label %89
89:
	%90 = load i32, i32* %26
	%91 = icmp eq i32 %90, 100
	br i1 %91, label %92, label %94
92:
	br label %97
93:
	br label %96
94:
	br label %80
95:
	br label %96
96:
	br label %80
97:
	store i32 100, i32* %26
	br label %98
98:
	br label %99
99:
	%100 = load i32, i32* %26
	%101 = icmp eq i32 %100, 100
	br i1 %101, label %102, label %104
102:
	br label %107
103:
	br label %106
104:
	br label %98
105:
	br label %106
106:
	br label %98
107:
	br label %108
108:
	br label %109
109:
	br label %110
110:
	br label %113
111:
	br label %112
112:
	br label %108
113:
	%114 = alloca i8
	%115 = call i32 @getchar()
	%116 = trunc i32 %115 to i8
	store i8 %116, i8* %114
	call void @putch(i32 97)
	call void @putch(i32 10)
	call void @putch(i32 97)
	call void @putch(i32 10)
	call void @putch(i32 97)
	call void @putch(i32 10)
	call void @putch(i32 97)
	call void @putch(i32 10)
	call void @putch(i32 97)
	call void @putch(i32 10)
	call void @putch(i32 97)
	call void @putch(i32 10)
	call void @putch(i32 97)
	call void @putch(i32 10)
	ret i32 0
}

