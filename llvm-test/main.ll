declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@a = dso_local global i32 1
@dqr0 = private unnamed_addr constant [4 x i8] c"--1\00"
@dqr1 = private unnamed_addr constant [4 x i8] c"--2\00"
@dqr2 = private unnamed_addr constant [4 x i8] c"--3\00"

define dso_local i32 @func() {
0:
	store i32 2, i32* @a
	ret i32 1
}

define dso_local i32 @func2() {
0:
	store i32 4, i32* @a
	ret i32 10
}

define dso_local i32 @func3() {
0:
	store i32 3, i32* @a
	ret i32 0
}

define dso_local i32 @main() {
0:
	br label %1
1:
	%2 = call i32 @func()
	%3 = icmp ne i32 %2, 0
	br i1 %3, label %4, label %7
4:
	%5 = call i32 @func3()
	%6 = icmp ne i32 %5, 0
	br i1 %6, label %10, label %7
7:
	%8 = call i32 @func2()
	%9 = icmp ne i32 %8, 0
	br i1 %9, label %10, label %13
10:
	%11 = load i32, i32* @a
	call void @putint(i32 %11)
	%12 = getelementptr [4 x i8], [4 x i8]* @dqr0, i32 0, i32 0
	call void @putstr(i8* %12)
	br label %13
13:
	br label %17
14:
	%15 = call i32 @func3()
	%16 = icmp ne i32 %15, 0
	br i1 %16, label %17, label %20
17:
	%18 = load i32, i32* @a
	call void @putint(i32 %18)
	%19 = getelementptr [4 x i8], [4 x i8]* @dqr1, i32 0, i32 0
	call void @putstr(i8* %19)
	br label %20
20:
	br label %21
21:
	%22 = call i32 @func3()
	%23 = icmp ne i32 %22, 0
	br i1 %23, label %29, label %24
24:
	%25 = call i32 @func()
	%26 = call i32 @func2()
	%27 = icmp slt i32 %25, %26
	%28 = icmp ne i1 %27, 0
	br i1 %28, label %29, label %32
29:
	%30 = load i32, i32* @a
	call void @putint(i32 %30)
	%31 = getelementptr [4 x i8], [4 x i8]* @dqr2, i32 0, i32 0
	call void @putstr(i8* %31)
	br label %32
32:
	ret i32 0
}

