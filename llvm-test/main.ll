declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@var2 = dso_local global i32 2
@var3 = dso_local global i32 3
@dqr0 = private unnamed_addr constant [9 x i8] c"21373457\00"
@dqr1 = private unnamed_addr constant [7 x i8] c"ERROR!\00"
@dqr2 = private unnamed_addr constant [13 x i8] c"And success!\00"
@dqr3 = private unnamed_addr constant [9 x i8] c"Or pass!\00"
@dqr4 = private unnamed_addr constant [15 x i8] c"Test1 Success!\00"

define dso_local void @fun() {
0:
	%1 = alloca i32
	store i32 1, i32* %1
	%2 = alloca i32
	store i32 1, i32* %2
	br label %3
3:
	%4 = load i32, i32* %2
	%5 = icmp slt i32 %4, 1000
	br i1 %5, label %6, label %9
6:
	%7 = load i32, i32* %2
	%8 = mul i32 %7, 2
	store i32 %8, i32* %2
	br label %3
9:
	%10 = load i32, i32* %2
	call void @putch(i32 10)
	call void @putint(i32 %10)
	ret void
}

define dso_local i32 @main() {
0:
	%1 = getelementptr [9 x i8], [9 x i8]* @dqr0, i32 0, i32 0
	call void @putstr(i8* %1)
	call void @putch(i32 10)
	%2 = load i32, i32* @var2
	%3 = load i32, i32* @var3
	%4 = sub i32 %3, 1
	%5 = icmp eq i32 %2, %4
	br i1 %5, label %6, label %18
6:
	br label %7
7:
	br label %8
8:
	br label %9
9:
	%10 = load i32, i32* @var2
	%11 = add i32 2, %10
	%12 = icmp slt i32 %11, 0
	br i1 %12, label %13, label %15
13:
	%14 = getelementptr [7 x i8], [7 x i8]* @dqr1, i32 0, i32 0
	call void @putstr(i8* %14)
	call void @putch(i32 10)
	br label %17
15:
	%16 = getelementptr [13 x i8], [13 x i8]* @dqr2, i32 0, i32 0
	call void @putstr(i8* %16)
	call void @putch(i32 10)
	br label %17
17:
	br label %18
18:
	%19 = load i32, i32* @var3
	%20 = icmp ne i32 %19, 3
	br i1 %20, label %25, label %21
21:
	%22 = load i32, i32* @var2
	%23 = sub i32 %22, 22
	%24 = icmp eq i32 %23, -20
	br i1 %24, label %25, label %35
25:
	%26 = load i32, i32* @var3
	%27 = add i32 -4, %26
	%28 = load i32, i32* @var2
	%29 = add i32 %27, %28
	%30 = icmp sle i32 %29, 100
	br i1 %30, label %32, label %31
31:
	br label %32
32:
	%33 = getelementptr [9 x i8], [9 x i8]* @dqr3, i32 0, i32 0
	call void @putstr(i8* %33)
	call void @putch(i32 10)
	br label %34
34:
	br label %35
35:
	%36 = getelementptr [15 x i8], [15 x i8]* @dqr4, i32 0, i32 0
	call void @putstr(i8* %36)
	call void @fun()
	call void @fun()
	call void @fun()
	call void @fun()
	call void @fun()
	call void @fun()
	ret i32 0
}

