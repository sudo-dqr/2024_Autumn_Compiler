declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@x = dso_local global i32 0
@dqr0 = private unnamed_addr constant [6 x i8] c"a is \00"
@dqr1 = private unnamed_addr constant [3 x i8] c"\n\00"
@dqr2 = private unnamed_addr constant [7 x i8] c"f4 is \00"
@dqr3 = private unnamed_addr constant [3 x i8] c"\n\00"
@dqr4 = private unnamed_addr constant [11 x i8] c"21373457\n\00"
@dqr5 = private unnamed_addr constant [18 x i8] c"Empty for pass!\n\00"
@dqr6 = private unnamed_addr constant [21 x i8] c"One stmt for pass!\n\00"
@dqr7 = private unnamed_addr constant [41 x i8] c"Basic for and no params function pass!\n\00"
@dqr8 = private unnamed_addr constant [34 x i8] c"Please input 5 number (no zero)\n\00"
@dqr9 = private unnamed_addr constant [42 x i8] c"Basic for and one params function pass!\n\00"
@dqr10 = private unnamed_addr constant [47 x i8] c"Basic for and multiple params function pass!\n\00"
@dqr11 = private unnamed_addr constant [28 x i8] c"Recursive Success, count = \00"
@dqr12 = private unnamed_addr constant [3 x i8] c"\n\00"
@dqr13 = private unnamed_addr constant [81 x i8] c"This C level file include decl, if, for ,continue, break, basic cond. No block\n\00"
@dqr14 = private unnamed_addr constant [14 x i8] c"Pass Success!\00"

define dso_local void @f1() {
0:
	%1 = alloca i32
	store i32 0, i32* %1
	br label %2
2:
	%3 = load i32, i32* %1
	%4 = icmp slt i32 %3, 5
	br i1 %4, label %5, label %11
5:
	%6 = load i32, i32* @x
	%7 = add i32 %6, 1
	store i32 %7, i32* @x
	br label %8
8:
	%9 = load i32, i32* %1
	%10 = add i32 %9, 1
	store i32 %10, i32* %1
	br label %2
11:
	ret void
}

define dso_local i32 @f2() {
0:
	%1 = load i32, i32* @x
	%2 = icmp sgt i32 %1, 0
	br i1 %2, label %3, label %5
3:
	ret i32 -1
4:
	br label %7
5:
	ret i32 1
6:
	br label %7
7:
	%8 = load i32, i32* @x
	ret i32 %8
}

define dso_local void @f3(i32 %0) {
1:
	%2 = alloca i32
	store i32 %0, i32* %2
	%3 = load i32, i32* %2
	store i32 %3, i32* @x
	ret void
}

define dso_local i32 @f4(i32 %0) {
1:
	%2 = alloca i32
	store i32 %0, i32* %2
	%3 = load i32, i32* %2
	%4 = icmp sgt i32 %3, 0
	br i1 %4, label %5, label %8
5:
	%6 = load i32, i32* %2
	ret i32 %6
7:
	br label %8
8:
	%9 = load i32, i32* %2
	%10 = sub i32 0, %9
	ret i32 %10
}

define dso_local i32 @f5(i32 %0, i32 %1, i32 %2) {
3:
	%4 = alloca i32
	%5 = alloca i32
	%6 = alloca i32
	store i32 %0, i32* %4
	store i32 %1, i32* %5
	store i32 %2, i32* %6
	%7 = load i32, i32* %4
	%8 = load i32, i32* %5
	%9 = icmp sgt i32 %7, %8
	br i1 %9, label %10, label %21
10:
	%11 = load i32, i32* %4
	%12 = load i32, i32* %6
	%13 = icmp sgt i32 %11, %12
	br i1 %13, label %14, label %17
14:
	%15 = load i32, i32* %4
	ret i32 %15
16:
	br label %20
17:
	%18 = load i32, i32* %6
	ret i32 %18
19:
	br label %20
20:
	br label %21
21:
	%22 = load i32, i32* %5
	%23 = load i32, i32* %6
	%24 = icmp sgt i32 %22, %23
	br i1 %24, label %25, label %36
25:
	%26 = load i32, i32* %5
	%27 = load i32, i32* %4
	%28 = icmp sgt i32 %26, %27
	br i1 %28, label %29, label %32
29:
	%30 = load i32, i32* %5
	ret i32 %30
31:
	br label %35
32:
	%33 = load i32, i32* %4
	ret i32 %33
34:
	br label %35
35:
	br label %36
36:
	%37 = load i32, i32* %6
	%38 = load i32, i32* %4
	%39 = icmp sgt i32 %37, %38
	br i1 %39, label %40, label %51
40:
	%41 = load i32, i32* %6
	%42 = load i32, i32* %5
	%43 = icmp sgt i32 %41, %42
	br i1 %43, label %44, label %47
44:
	%45 = load i32, i32* %6
	ret i32 %45
46:
	br label %50
47:
	%48 = load i32, i32* %5
	ret i32 %48
49:
	br label %50
50:
	br label %51
51:
	%52 = load i32, i32* %4
	%53 = getelementptr [6 x i8], [6 x i8]* @dqr0, i32 0, i32 0
	call void @putstr(i8* %53)
	call void @putint(i32 %52)
	%54 = getelementptr [3 x i8], [3 x i8]* @dqr1, i32 0, i32 0
	call void @putstr(i8* %54)
	%55 = load i32, i32* %4
	%56 = call i32 @f4(i32 %55)
	%57 = getelementptr [7 x i8], [7 x i8]* @dqr2, i32 0, i32 0
	call void @putstr(i8* %57)
	call void @putint(i32 %56)
	%58 = getelementptr [3 x i8], [3 x i8]* @dqr3, i32 0, i32 0
	call void @putstr(i8* %58)
	%59 = load i32, i32* %4
	%60 = call i32 @f4(i32 %59)
	ret i32 %60
}

define dso_local i32 @f6(i32 %0) {
1:
	%2 = alloca i32
	store i32 %0, i32* %2
	%3 = load i32, i32* @x
	%4 = load i32, i32* %2
	%5 = add i32 %3, %4
	store i32 %5, i32* @x
	%6 = load i32, i32* %2
	%7 = icmp eq i32 %6, 0
	br i1 %7, label %8, label %10
8:
	ret i32 0
9:
	br label %10
10:
	%11 = load i32, i32* %2
	%12 = sub i32 %11, 1
	%13 = call i32 @f6(i32 %12)
	ret i32 %13
}

define dso_local i32 @main() {
0:
	%1 = getelementptr [11 x i8], [11 x i8]* @dqr4, i32 0, i32 0
	call void @putstr(i8* %1)
	%2 = alloca i32
	%3 = alloca i32
	store i32 5, i32* %3
	%4 = alloca i32
	store i32 0, i32* %2
	br label %5
5:
	%6 = load i32, i32* %2
	%7 = icmp slt i32 %6, 5
	br i1 %7, label %8, label %12
8:
	br label %9
9:
	%10 = load i32, i32* %2
	%11 = add i32 %10, 1
	store i32 %11, i32* %2
	br label %5
12:
	%13 = load i32, i32* %2
	%14 = icmp eq i32 %13, 5
	br i1 %14, label %15, label %17
15:
	%16 = getelementptr [18 x i8], [18 x i8]* @dqr5, i32 0, i32 0
	call void @putstr(i8* %16)
	br label %17
17:
	store i32 0, i32* %2
	br label %18
18:
	%19 = load i32, i32* %2
	%20 = icmp slt i32 %19, 2
	br i1 %20, label %21, label %24
21:
	%22 = load i32, i32* %2
	%23 = add i32 %22, 1
	store i32 %23, i32* %2
	br label %18
24:
	store i32 2, i32* %2
	br label %25
25:
	br label %26
26:
	%27 = load i32, i32* %2
	%28 = icmp eq i32 %27, 4
	br i1 %28, label %29, label %31
29:
	br label %35
30:
	br label %31
31:
	br label %32
32:
	%33 = load i32, i32* %2
	%34 = add i32 %33, 1
	store i32 %34, i32* %2
	br label %25
35:
	br label %36
36:
	%37 = load i32, i32* %2
	%38 = icmp slt i32 %37, 5
	br i1 %38, label %39, label %50
39:
	%40 = load i32, i32* %2
	%41 = icmp slt i32 %40, 5
	br i1 %41, label %42, label %44
42:
	br label %47
43:
	br label %44
44:
	%45 = load i32, i32* %2
	%46 = add i32 %45, 2
	store i32 %46, i32* %2
	br label %47
47:
	%48 = load i32, i32* %2
	%49 = add i32 %48, 1
	store i32 %49, i32* %2
	br label %36
50:
	store i32 5, i32* %2
	br label %51
51:
	br label %52
52:
	%53 = load i32, i32* %2
	%54 = add i32 %53, 1
	store i32 %54, i32* %2
	%55 = load i32, i32* %2
	%56 = icmp eq i32 %55, 6
	br i1 %56, label %57, label %59
57:
	br label %60
58:
	br label %59
59:
	br label %51
60:
	br label %61
61:
	%62 = load i32, i32* %2
	%63 = icmp slt i32 %62, 7
	br i1 %63, label %64, label %67
64:
	%65 = load i32, i32* %2
	%66 = add i32 %65, 1
	store i32 %66, i32* %2
	br label %61
67:
	br label %68
68:
	br label %69
69:
	%70 = load i32, i32* %2
	%71 = icmp eq i32 %70, 8
	br i1 %71, label %72, label %74
72:
	br label %78
73:
	br label %74
74:
	br label %75
75:
	%76 = load i32, i32* %2
	%77 = add i32 %76, 1
	store i32 %77, i32* %2
	br label %68
78:
	br label %79
79:
	br label %80
80:
	%81 = load i32, i32* %2
	%82 = add i32 %81, 1
	store i32 %82, i32* %2
	%83 = load i32, i32* %2
	%84 = icmp eq i32 %83, 10
	br i1 %84, label %85, label %88
85:
	%86 = getelementptr [21 x i8], [21 x i8]* @dqr6, i32 0, i32 0
	call void @putstr(i8* %86)
	br label %89
87:
	br label %88
88:
	br label %79
89:
	call void @f1()
	%90 = load i32, i32* @x
	%91 = icmp eq i32 %90, 5
	br i1 %91, label %92, label %98
92:
	%93 = call i32 @f2()
	%94 = icmp eq i32 %93, -1
	br i1 %94, label %95, label %97
95:
	%96 = getelementptr [41 x i8], [41 x i8]* @dqr7, i32 0, i32 0
	call void @putstr(i8* %96)
	br label %97
97:
	br label %98
98:
	%99 = getelementptr [34 x i8], [34 x i8]* @dqr8, i32 0, i32 0
	call void @putstr(i8* %99)
	store i32 -1, i32* @x
	store i32 0, i32* %2
	br label %100
100:
	%101 = load i32, i32* %2
	%102 = load i32, i32* %2
	%103 = mul i32 %101, %102
	%104 = load i32, i32* %3
	%105 = load i32, i32* %3
	%106 = mul i32 %104, %105
	%107 = icmp slt i32 %103, %106
	br i1 %107, label %108, label %127
108:
	%109 = call i32 @getint()
	store i32 %109, i32* %4
	%110 = load i32, i32* %4
	%111 = call i32 @f4(i32 %110)
	call void @f3(i32 %111)
	%112 = load i32, i32* @x
	%113 = icmp slt i32 %112, 0
	br i1 %113, label %114, label %116
114:
	br label %127
115:
	br label %116
116:
	%117 = load i32, i32* @x
	%118 = icmp sgt i32 %117, 0
	br i1 %118, label %119, label %121
119:
	br label %124
120:
	br label %121
121:
	%122 = load i32, i32* %2
	%123 = add i32 %122, 1
	store i32 %123, i32* %2
	br label %124
124:
	%125 = load i32, i32* %2
	%126 = add i32 %125, 1
	store i32 %126, i32* %2
	br label %100
127:
	%128 = load i32, i32* @x
	%129 = icmp sge i32 %128, 0
	br i1 %129, label %130, label %132
130:
	%131 = getelementptr [42 x i8], [42 x i8]* @dqr9, i32 0, i32 0
	call void @putstr(i8* %131)
	br label %132
132:
	store i32 10, i32* %2
	store i32 5, i32* %3
	store i32 7, i32* %4
	%133 = load i32, i32* %2
	%134 = load i32, i32* %3
	%135 = load i32, i32* %4
	%136 = call i32 @f5(i32 %133, i32 %134, i32 %135)
	%137 = load i32, i32* %2
	%138 = icmp eq i32 %136, %137
	br i1 %138, label %139, label %141
139:
	%140 = getelementptr [47 x i8], [47 x i8]* @dqr10, i32 0, i32 0
	call void @putstr(i8* %140)
	br label %141
141:
	store i32 0, i32* @x
	%142 = call i32 @f6(i32 10)
	%143 = load i32, i32* @x
	%144 = getelementptr [28 x i8], [28 x i8]* @dqr11, i32 0, i32 0
	call void @putstr(i8* %144)
	call void @putint(i32 %143)
	%145 = getelementptr [3 x i8], [3 x i8]* @dqr12, i32 0, i32 0
	call void @putstr(i8* %145)
	%146 = getelementptr [81 x i8], [81 x i8]* @dqr13, i32 0, i32 0
	call void @putstr(i8* %146)
	%147 = getelementptr [14 x i8], [14 x i8]* @dqr14, i32 0, i32 0
	call void @putstr(i8* %147)
	ret i32 0
}

