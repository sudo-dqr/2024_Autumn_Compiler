declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@c = dso_local global [3 x i8] [i8 97, i8 39, i8 0]

define dso_local i32 @main() {
0:
	%1 = alloca [2 x i32]
	%2 = getelementptr [2 x i32], [2 x i32]* %1, i32 0, i32 0
	store i32 353, i32* %2
	%3 = getelementptr [2 x i32], [2 x i32]* %1, i32 0, i32 1
	store i32 355, i32* %3
	%4 = alloca i32
	store i32 356, i32* %4
	%5 = alloca [2 x i8]
	%6 = getelementptr [2 x i8], [2 x i8]* %5, i32 0, i32 0
	%7 = load i32, i32* %4
	%8 = trunc i32 %7 to i8
	store i8 %8, i8* %6
	%9 = getelementptr [2 x i8], [2 x i8]* %5, i32 0, i32 1
	store i8 97, i8* %9
	ret i32 0
}

