declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@dqr0 = private unnamed_addr constant [30 x i8] c"Sun Mon Tue Wed Thu Fri Sat\n\00"
@dqr1 = private unnamed_addr constant [5 x i8] c"    \00"
@dqr2 = private unnamed_addr constant [3 x i8] c"  \00"
@dqr3 = private unnamed_addr constant [3 x i8] c"\n\00"
@dqr4 = private unnamed_addr constant [3 x i8] c"\n\00"

define dso_local i32 @is_leap_year(i32 %0) {
1:
	%2 = alloca i32
	store i32 %0, i32* %2
	%3 = load i32, i32* %2
	%4 = srem i32 %3, 400
	%5 = icmp eq i32 %4, 0
	br i1 %5, label %6, label %8
6:
	ret i32 1
7:
	br label %21
8:
	%9 = load i32, i32* %2
	%10 = srem i32 %9, 4
	%11 = icmp eq i32 %10, 0
	br i1 %11, label %12, label %18
12:
	%13 = load i32, i32* %2
	%14 = srem i32 %13, 100
	%15 = icmp ne i32 %14, 0
	br i1 %15, label %16, label %18
16:
	ret i32 1
17:
	br label %20
18:
	ret i32 0
19:
	br label %20
20:
	br label %21
}

define dso_local i32 @zeller(i32 %0, i32 %1, i32 %2) {
3:
	%4 = alloca i32
	%5 = alloca i32
	%6 = alloca i32
	store i32 %0, i32* %4
	store i32 %1, i32* %5
	store i32 %2, i32* %6
	%7 = load i32, i32* %5
	%8 = icmp slt i32 %7, 3
	br i1 %8, label %9, label %14
9:
	%10 = load i32, i32* %5
	%11 = add i32 %10, 12
	store i32 %11, i32* %5
	%12 = load i32, i32* %6
	%13 = sub i32 %12, 1
	store i32 %13, i32* %6
	br label %14
14:
	%15 = alloca i32
	%16 = load i32, i32* %6
	%17 = srem i32 %16, 100
	store i32 %17, i32* %15
	%18 = alloca i32
	%19 = load i32, i32* %6
	%20 = sdiv i32 %19, 100
	store i32 %20, i32* %18
	%21 = alloca i32
	%22 = load i32, i32* %4
	%23 = load i32, i32* %5
	%24 = add i32 %23, 1
	%25 = mul i32 13, %24
	%26 = sdiv i32 %25, 5
	%27 = add i32 %22, %26
	%28 = load i32, i32* %15
	%29 = add i32 %27, %28
	%30 = load i32, i32* %15
	%31 = sdiv i32 %30, 4
	%32 = add i32 %29, %31
	%33 = load i32, i32* %18
	%34 = sdiv i32 %33, 4
	%35 = add i32 %32, %34
	%36 = load i32, i32* %18
	%37 = mul i32 5, %36
	%38 = add i32 %35, %37
	%39 = srem i32 %38, 7
	store i32 %39, i32* %21
	%40 = load i32, i32* %21
	%41 = add i32 %40, 5
	%42 = srem i32 %41, 7
	ret i32 %42
}

define dso_local void @calendar(i32 %0, i32 %1) {
2:
	%3 = alloca i32
	%4 = alloca i32
	store i32 %0, i32* %3
	store i32 %1, i32* %4
	%5 = alloca i32
	%6 = alloca [15 x i32]
	%7 = getelementptr [15 x i32], [15 x i32]* %6, i32 0, i32 0
	store i32 31, i32* %7
	%8 = getelementptr [15 x i32], [15 x i32]* %6, i32 0, i32 1
	store i32 28, i32* %8
	%9 = getelementptr [15 x i32], [15 x i32]* %6, i32 0, i32 2
	store i32 31, i32* %9
	%10 = getelementptr [15 x i32], [15 x i32]* %6, i32 0, i32 3
	store i32 30, i32* %10
	%11 = getelementptr [15 x i32], [15 x i32]* %6, i32 0, i32 4
	store i32 31, i32* %11
	%12 = getelementptr [15 x i32], [15 x i32]* %6, i32 0, i32 5
	store i32 30, i32* %12
	%13 = getelementptr [15 x i32], [15 x i32]* %6, i32 0, i32 6
	store i32 31, i32* %13
	%14 = getelementptr [15 x i32], [15 x i32]* %6, i32 0, i32 7
	store i32 31, i32* %14
	%15 = getelementptr [15 x i32], [15 x i32]* %6, i32 0, i32 8
	store i32 30, i32* %15
	%16 = getelementptr [15 x i32], [15 x i32]* %6, i32 0, i32 9
	store i32 31, i32* %16
	%17 = getelementptr [15 x i32], [15 x i32]* %6, i32 0, i32 10
	store i32 30, i32* %17
	%18 = getelementptr [15 x i32], [15 x i32]* %6, i32 0, i32 11
	store i32 31, i32* %18
	%19 = load i32, i32* %3
	%20 = call i32 @is_leap_year(i32 %19)
	%21 = icmp ne i32 %20, 0
	br i1 %21, label %22, label %27
22:
	%23 = load i32, i32* %4
	%24 = icmp eq i32 %23, 2
	br i1 %24, label %25, label %27
25:
	%26 = getelementptr [15 x i32], [15 x i32]* %6, i32 0, i32 1
	store i32 29, i32* %26
	br label %27
27:
	%28 = alloca i32
	%29 = load i32, i32* %4
	%30 = load i32, i32* %3
	%31 = call i32 @zeller(i32 1, i32 %29, i32 %30)
	store i32 %31, i32* %28
	%32 = getelementptr [30 x i8], [30 x i8]* @dqr0, i32 0, i32 0
	call void @putstr(i8* %32)
	store i32 0, i32* %5
	br label %33
33:
	%34 = load i32, i32* %5
	%35 = load i32, i32* %28
	%36 = icmp slt i32 %34, %35
	br i1 %36, label %37, label %42
37:
	%38 = getelementptr [5 x i8], [5 x i8]* @dqr1, i32 0, i32 0
	call void @putstr(i8* %38)
	br label %39
39:
	%40 = load i32, i32* %5
	%41 = add i32 %40, 1
	store i32 %41, i32* %5
	br label %33
42:
	%43 = alloca i32
	store i32 1, i32* %43
	%44 = alloca i32
	%45 = load i32, i32* %28
	store i32 %45, i32* %44
	br label %46
46:
	%47 = load i32, i32* %43
	%48 = load i32, i32* %4
	%49 = sub i32 %48, 1
	%50 = getelementptr [15 x i32], [15 x i32]* %6, i32 0, i32 %49
	%51 = load i32, i32* %50
	%52 = icmp sle i32 %47, %51
	br i1 %52, label %53, label %72
53:
	%54 = load i32, i32* %43
	%55 = icmp slt i32 %54, 10
	br i1 %55, label %56, label %59
56:
	%57 = load i32, i32* %43
	%58 = getelementptr [3 x i8], [3 x i8]* @dqr2, i32 0, i32 0
	call void @putstr(i8* %58)
	call void @putint(i32 %57)
	call void @putch(i32 32)
	br label %61
59:
	%60 = load i32, i32* %43
	call void @putch(i32 32)
	call void @putint(i32 %60)
	call void @putch(i32 32)
	br label %61
61:
	%62 = load i32, i32* %44
	%63 = srem i32 %62, 7
	%64 = icmp eq i32 %63, 6
	br i1 %64, label %65, label %67
65:
	%66 = getelementptr [3 x i8], [3 x i8]* @dqr3, i32 0, i32 0
	call void @putstr(i8* %66)
	br label %67
67:
	%68 = load i32, i32* %43
	%69 = add i32 %68, 1
	store i32 %69, i32* %43
	%70 = load i32, i32* %44
	%71 = add i32 %70, 1
	store i32 %71, i32* %44
	br label %46
72:
	%73 = load i32, i32* %28
	%74 = load i32, i32* %4
	%75 = sub i32 %74, 1
	%76 = getelementptr [15 x i32], [15 x i32]* %6, i32 0, i32 %75
	%77 = load i32, i32* %76
	%78 = add i32 %73, %77
	%79 = srem i32 %78, 7
	%80 = icmp ne i32 %79, 0
	br i1 %80, label %81, label %83
81:
	%82 = getelementptr [3 x i8], [3 x i8]* @dqr4, i32 0, i32 0
	call void @putstr(i8* %82)
	br label %83
83:
	ret void
}

define dso_local i32 @main() {
0:
	%1 = alloca i32
	%2 = alloca i32
	%3 = call i32 @getint()
	store i32 %3, i32* %1
	%4 = call i32 @getint()
	store i32 %4, i32* %2
	%5 = load i32, i32* %1
	%6 = load i32, i32* %2
	call void @calendar(i32 %5, i32 %6)
	ret i32 0
}

