declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@dqr0 = private unnamed_addr constant [4 x i8] c"yes\00"

define dso_local i32 @main() {
0:
	%1 = alloca i32
	store i32 1, i32* %1
	%2 = alloca i8
	store i8 98, i8* %2
	%3 = alloca i8
	store i8 99, i8* %3
	%4 = load i32, i32* %1
	%5 = load i8, i8* %2
	%6 = zext i8 %5 to i32
	%7 = icmp eq i32 %4, %6
	br i1 %7, label %8, label %16
8:
	%9 = load i8, i8* %2
	%10 = load i8, i8* %3
	%11 = zext i8 %9 to i32
	%12 = zext i8 %10 to i32
	%13 = icmp eq i32 %11, %12
	br i1 %13, label %14, label %16
14:
	%15 = getelementptr [4 x i8], [4 x i8]* @dqr0, i32 0, i32 0
	call void @putstr(i8* %15)
	call void @putch(i32 10)
	br label %16
16:
	%17 = alloca i32
	%18 = load i32, i32* %1
	%19 = load i8, i8* %2
	%20 = zext i8 %19 to i32
	%21 = add i32 %18, %20
	%22 = load i8, i8* %3
	%23 = zext i8 %22 to i32
	%24 = add i32 %21, %23
	store i32 %24, i32* %17
	%25 = load i32, i32* %17
	call void @putint(i32 %25)
	ret i32 0
}

