declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@dqr0 = private unnamed_addr constant [7 x i8] c"round \00"
@dqr1 = private unnamed_addr constant [3 x i8] c": \00"

define dso_local i32 @main() {
0:
	%1 = alloca i32
	store i32 1, i32* %1
	%2 = alloca i32
	%3 = load i32, i32* %1
	store i32 %3, i32* %2
	%4 = alloca i32
	%5 = alloca i32
	%6 = alloca i32
	%7 = call i32 @getint()
	store i32 %7, i32* %5
	%8 = load i32, i32* %1
	%9 = load i32, i32* %1
	%10 = mul i32 %8, %9
	store i32 %10, i32* %6
	br label %11
11:
	%12 = load i32, i32* %6
	%13 = load i32, i32* %5
	%14 = add i32 %13, 1
	%15 = icmp slt i32 %12, %14
	br i1 %15, label %16, label %38
16:
	%17 = load i32, i32* %2
	store i32 %17, i32* %4
	%18 = load i32, i32* %1
	%19 = load i32, i32* %2
	%20 = add i32 %18, %19
	store i32 %20, i32* %2
	%21 = load i32, i32* %4
	store i32 %21, i32* %1
	%22 = load i32, i32* %6
	%23 = srem i32 %22, 2
	%24 = icmp eq i32 %23, 1
	br i1 %24, label %25, label %26
25:
	br label %35
	br label %26
26:
	%27 = load i32, i32* %6
	%28 = load i32, i32* %1
	%29 = getelementptr [7 x i8], [7 x i8]* @dqr0, i32 0, i32 0
	call void @putstr(i8* %29)
	call void @putint(i32 %27)
	%30 = getelementptr [3 x i8], [3 x i8]* @dqr1, i32 0, i32 0
	call void @putstr(i8* %30)
	call void @putint(i32 %28)
	call void @putch(i32 10)
	%31 = load i32, i32* %6
	%32 = icmp sgt i32 %31, 19
	br i1 %32, label %33, label %34
33:
	br label %38
	br label %34
34:
	br label %35
35:
	%36 = load i32, i32* %6
	%37 = add i32 %36, 1
	store i32 %37, i32* %6
	br label %11
38:
	ret i32 0
}

