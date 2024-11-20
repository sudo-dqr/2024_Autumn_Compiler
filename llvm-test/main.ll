declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@dqr0 = private unnamed_addr constant [8 x i8] c"Hello: \00"
@dqr1 = private unnamed_addr constant [3 x i8] c", \00"

define dso_local i32 @main() {
	%1 = alloca i32
	%2 = alloca i8
	%3 = call i32 @getint()
	store i32 %3, i32* %1
	%4 = call i32 @getchar()
	%5 = trunc i32 %4 to i8
	store i8 %5, i8* %2
	%6 = load i32, i32* %1
	%7 = load i8, i8* %2
	%8 = getelementptr [8 x i8], [8 x i8]* @dqr0, i32 0, i32 0
	call void @putstr(i8* %8)
	call void @putint(i32 %6)
	%9 = getelementptr [3 x i8], [3 x i8]* @dqr1, i32 0, i32 0
	call void @putstr(i8* %9)
	%10 = zext i8 %7 to i32
	call void @putch(i32 %10)
	ret i32 0
}

