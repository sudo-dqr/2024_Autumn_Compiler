declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@global_var = dso_local global i32 0
@str = dso_local global [10 x i8] [i8 51, i8 39, i8 0, i8 0, i8 0, i8 0, i8 0, i8 0, i8 0, i8 0]
@dqr0 = private unnamed_addr constant [9 x i8] c"22373040\00"
@dqr1 = private unnamed_addr constant [16 x i8] c"Input integer: \00"
@dqr2 = private unnamed_addr constant [18 x i8] c"Input character: \00"
@dqr3 = private unnamed_addr constant [13 x i8] c"i is 4 or 9!\00"
@dqr4 = private unnamed_addr constant [9 x i8] c"j is 32!\00"
@dqr5 = private unnamed_addr constant [24 x i8] c"Sum of array elements: \00"
@dqr6 = private unnamed_addr constant [15 x i8] c"Test finished!\00"

define dso_local i32 @add(i32 %0, i32 %1) {
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

define dso_local i32 @calculate(i32 %0, i32* %1) {
2:
	%3 = alloca i32
	%4 = alloca i32*
	store i32 %0, i32* %3
	store i32* %1, i32** %4
	%5 = alloca i32
	%6 = load i32, i32* %3
	%7 = load i32*, i32** %4
	%8 = getelementptr i32, i32* %7, i32 0
	%9 = load i32, i32* %8
	%10 = call i32 @add(i32 %6, i32 %9)
	%11 = load i32, i32* %3
	%12 = load i32*, i32** %4
	%13 = getelementptr i32, i32* %12, i32 1
	%14 = load i32, i32* %13
	%15 = sub i32 %11, %14
	%16 = mul i32 %10, %15
	%17 = load i32*, i32** %4
	%18 = getelementptr i32, i32* %17, i32 2
	%19 = load i32, i32* %18
	%20 = sdiv i32 %16, %19
	%21 = load i32, i32* %3
	%22 = srem i32 %20, %21
	%23 = sub i32 %22, -3
	%24 = add i32 %23, 6
	store i32 %24, i32* %5
	%25 = load i32, i32* %5
	%26 = icmp sle i32 %25, 5
	br i1 %26, label %27, label %29
27:
	ret i32 1
28:
	br label %31
29:
	ret i32 0
30:
	br label %31
31:
	ret i32 -1
}

define dso_local void @printName() {
0:
	%1 = load i32, i32* @global_var
	%2 = add i32 %1, 1
	store i32 %2, i32* @global_var
	%3 = load i32, i32* @global_var
	%4 = icmp ne i32 %3, 0
	br i1 %4, label %5, label %7
5:
	%6 = getelementptr [9 x i8], [9 x i8]* @dqr0, i32 0, i32 0
	call void @putstr(i8* %6)
	call void @putch(i32 10)
	br label %7
7:
	ret void
}

define dso_local void @print(i8 %0) {
1:
	%2 = alloca i8
	store i8 %0, i8* %2
	%3 = load i8, i8* %2
	%4 = zext i8 %3 to i32
	call void @putch(i32 %4)
	call void @putch(i32 10)
	ret void
}

define dso_local i8 @get_first(i8* %0) {
1:
	%2 = alloca i8*
	store i8* %0, i8** %2
	%3 = load i8*, i8** %2
	%4 = getelementptr i8, i8* %3, i32 0
	%5 = load i8, i8* %4
	ret i8 %5
}

define dso_local i32 @main() {
0:
	call void @printName()
	%1 = alloca i32
	store i32 0, i32* %1
	%2 = alloca i32
	store i32 8, i32* %2
	%3 = alloca i8
	%4 = call i32 @getint()
	store i32 %4, i32* %1
	%5 = call i32 @getchar()
	%6 = trunc i32 %5 to i8
	store i8 %6, i8* %3
	%7 = load i32, i32* %1
	%8 = getelementptr [16 x i8], [16 x i8]* @dqr1, i32 0, i32 0
	call void @putstr(i8* %8)
	call void @putint(i32 %7)
	call void @putch(i32 10)
	%9 = load i8, i8* %3
	%10 = getelementptr [18 x i8], [18 x i8]* @dqr2, i32 0, i32 0
	call void @putstr(i8* %10)
	%11 = zext i8 %9 to i32
	call void @putch(i32 %11)
	call void @putch(i32 10)
	%12 = alloca [10 x i32]
	%13 = alloca [12 x i8]
	%14 = getelementptr [12 x i8], [12 x i8]* %13, i32 0, i32 0
	store i8 113, i8* %14
	%15 = getelementptr [12 x i8], [12 x i8]* %13, i32 0, i32 1
	store i8 119, i8* %15
	%16 = getelementptr [12 x i8], [12 x i8]* %13, i32 0, i32 2
	store i8 101, i8* %16
	%17 = getelementptr [12 x i8], [12 x i8]* %13, i32 0, i32 3
	store i8 114, i8* %17
	%18 = getelementptr [12 x i8], [12 x i8]* %13, i32 0, i32 4
	store i8 116, i8* %18
	%19 = getelementptr [12 x i8], [12 x i8]* %13, i32 0, i32 5
	store i8 121, i8* %19
	%20 = getelementptr [12 x i8], [12 x i8]* %13, i32 0, i32 6
	store i8 117, i8* %20
	%21 = getelementptr [12 x i8], [12 x i8]* %13, i32 0, i32 7
	store i8 105, i8* %21
	%22 = getelementptr [12 x i8], [12 x i8]* %13, i32 0, i32 8
	store i8 111, i8* %22
	%23 = getelementptr [12 x i8], [12 x i8]* %13, i32 0, i32 9
	store i8 112, i8* %23
	%24 = getelementptr [12 x i8], [12 x i8]* %13, i32 0, i32 10
	store i8 92, i8* %24
	%25 = getelementptr [12 x i8], [12 x i8]* %13, i32 0, i32 11
	store i8 110, i8* %25
	%26 = alloca [10 x i8]
	%27 = getelementptr [10 x i8], [10 x i8]* %26, i32 0, i32 0
	store i8 115, i8* %27
	%28 = getelementptr [10 x i8], [10 x i8]* %26, i32 0, i32 1
	store i8 116, i8* %28
	%29 = getelementptr [10 x i8], [10 x i8]* %26, i32 0, i32 2
	store i8 114, i8* %29
	%30 = getelementptr [10 x i8], [10 x i8]* %26, i32 0, i32 3
	store i8 0, i8* %30
	%31 = getelementptr [10 x i8], [10 x i8]* %26, i32 0, i32 4
	store i8 0, i8* %31
	%32 = getelementptr [10 x i8], [10 x i8]* %26, i32 0, i32 5
	store i8 0, i8* %32
	%33 = getelementptr [10 x i8], [10 x i8]* %26, i32 0, i32 6
	store i8 0, i8* %33
	%34 = getelementptr [10 x i8], [10 x i8]* %26, i32 0, i32 7
	store i8 0, i8* %34
	%35 = getelementptr [10 x i8], [10 x i8]* %26, i32 0, i32 8
	store i8 0, i8* %35
	%36 = getelementptr [10 x i8], [10 x i8]* %26, i32 0, i32 9
	store i8 0, i8* %36
	store i32 0, i32* %1
	br label %37
37:
	%38 = load i32, i32* %1
	%39 = icmp slt i32 %38, 10
	br i1 %39, label %40, label %90
40:
	%41 = load i32, i32* %1
	%42 = getelementptr [10 x i32], [10 x i32]* %12, i32 0, i32 %41
	%43 = load i32, i32* %1
	store i32 %43, i32* %42
	%44 = load i32, i32* %1
	%45 = icmp eq i32 %44, 4
	br i1 %45, label %46, label %51
46:
	%47 = load i32, i32* %1
	%48 = load i8, i8* %3
	%49 = zext i8 %48 to i32
	%50 = icmp slt i32 %47, %49
	br i1 %50, label %54, label %51
51:
	%52 = load i32, i32* %1
	%53 = icmp sge i32 %52, 9
	br i1 %53, label %54, label %76
54:
	%55 = getelementptr [13 x i8], [13 x i8]* @dqr3, i32 0, i32 0
	call void @putstr(i8* %55)
	call void @putch(i32 10)
	%56 = alloca i32
	store i32 1, i32* %56
	br label %57
57:
	br label %58
58:
	%59 = load i32, i32* %56
	%60 = icmp sgt i32 %59, 100
	br i1 %60, label %61, label %63
61:
	br label %75
62:
	br label %69
63:
	%64 = load i32, i32* %56
	%65 = icmp ne i32 %64, 32
	br i1 %65, label %66, label %68
66:
	br label %71
67:
	br label %68
68:
	br label %69
69:
	%70 = getelementptr [9 x i8], [9 x i8]* @dqr4, i32 0, i32 0
	call void @putstr(i8* %70)
	call void @putch(i32 10)
	br label %71
71:
	%72 = load i32, i32* %56
	%73 = load i32, i32* %56
	%74 = add i32 %72, %73
	store i32 %74, i32* %56
	br label %57
75:
	br label %76
76:
	%77 = load i32, i32* %1
	%78 = srem i32 %77, 2
	%79 = icmp eq i32 %78, 0
	br i1 %79, label %80, label %85
80:
	br label %81
81:
	br label %82
82:
	br label %84
83:
	br label %81
84:
	br label %86
85:
	br label %86
86:
	br label %87
87:
	%88 = load i32, i32* %1
	%89 = add i32 %88, 1
	store i32 %89, i32* %1
	br label %37
90:
	%91 = alloca [20 x i32]
	%92 = getelementptr [20 x i32], [20 x i32]* %91, i32 0, i32 0
	store i32 3, i32* %92
	%93 = getelementptr [20 x i32], [20 x i32]* %91, i32 0, i32 1
	store i32 2, i32* %93
	%94 = getelementptr [20 x i32], [20 x i32]* %91, i32 0, i32 2
	store i32 1, i32* %94
	%95 = alloca i32
	store i32 0, i32* %95
	%96 = alloca i32
	store i32 0, i32* %96
	br label %97
97:
	%98 = load i32, i32* %96
	%99 = icmp slt i32 %98, 10
	br i1 %99, label %100, label %113
100:
	%101 = load i32, i32* %96
	%102 = icmp slt i32 %101, 3
	br i1 %102, label %103, label %109
103:
	%104 = load i32, i32* %95
	%105 = load i32, i32* %96
	%106 = getelementptr [20 x i32], [20 x i32]* %91, i32 0, i32 %105
	%107 = load i32, i32* %106
	%108 = add i32 %104, %107
	store i32 %108, i32* %95
	br label %109
109:
	br label %110
110:
	%111 = load i32, i32* %96
	%112 = add i32 %111, 1
	store i32 %112, i32* %96
	br label %97
113:
	%114 = load i32, i32* %95
	%115 = getelementptr [24 x i8], [24 x i8]* @dqr5, i32 0, i32 0
	call void @putstr(i8* %115)
	call void @putint(i32 %114)
	call void @putch(i32 10)
	%116 = load i32, i32* %1
	%117 = getelementptr [10 x i32], [10 x i32]* %12, i32 0, i32 0
	%118 = call i32 @calculate(i32 %116, i32* %117)
	%119 = icmp eq i32 %118, 0
	%120 = zext i1 %119 to i32
	%121 = icmp ne i32 %120, 0
	br i1 %121, label %122, label %125
122:
	%123 = getelementptr [12 x i8], [12 x i8]* %13, i32 0, i32 0
	%124 = call i8 @get_first(i8* %123)
	call void @print(i8 %124)
	br label %125
125:
	%126 = getelementptr [15 x i8], [15 x i8]* @dqr6, i32 0, i32 0
	call void @putstr(i8* %126)
	call void @putch(i32 10)
	ret i32 0
}

