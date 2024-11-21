declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@a = dso_local global [6 x i32] [i32 1, i32 2, i32 3, i32 4, i32 5, i32 6]
@dqr0 = private unnamed_addr constant [4 x i8] c" - \00"

define dso_local i32 @foo(i32 %0, i32* %1) {
2:
	%3 = alloca i32
	%4 = alloca i32*
	store i32 %0, i32* %3
	store i32* %1, i32** %4
	%5 = load i32, i32* %3
	%6 = load i32*, i32** %4
	%7 = getelementptr i32, i32* %6, i32 2
	%8 = load i32, i32* %7
	%9 = add i32 %5, %8
	ret i32 %9
}

define dso_local i32 @main() {
0:
	%1 = alloca [3 x i32]
	%2 = getelementptr [3 x i32], [3 x i32]* %1, i32 0, i32 0
	store i32 1, i32* %2
	%3 = getelementptr [3 x i32], [3 x i32]* %1, i32 0, i32 1
	store i32 2, i32* %3
	%4 = getelementptr [3 x i32], [3 x i32]* %1, i32 0, i32 2
	store i32 3, i32* %4
	%5 = alloca i32
	%6 = getelementptr [6 x i32], [6 x i32]* @a, i32 0, i32 4
	%7 = load i32, i32* %6
	%8 = getelementptr [6 x i32], [6 x i32]* @a, i32 0, i32 0
	store i32 0, i32* %5
	%9 = load i32, i32* %5
	%10 = getelementptr [3 x i32], [3 x i32]* %1, i32 0, i32 0
	%11 = load i32, i32* %10
	%12 = getelementptr [3 x i32], [3 x i32]* %1, i32 0, i32 0
	call void @putint(i32 %9)
	%13 = getelementptr [4 x i8], [4 x i8]* @dqr0, i32 0, i32 0
	call void @putstr(i8* %13)
	call void @putint(i32 0)
	call void @putch(i32 10)
	ret i32 0
}

