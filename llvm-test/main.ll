declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@ch = dso_local global i8 97
@a = dso_local global [3 x i8] [i8 99, i8 100, i8 101]
@b = dso_local global i8 98

define dso_local i32 @main() {
0:
	%1 = alloca [3 x i8]
	%2 = getelementptr [3 x i8], [3 x i8]* %1, i32 0, i32 0
	store i8 102, i8* %2
	%3 = getelementptr [3 x i8], [3 x i8]* %1, i32 0, i32 1
	store i8 103, i8* %3
	%4 = getelementptr [3 x i8], [3 x i8]* %1, i32 0, i32 2
	store i8 104, i8* %4
	%5 = alloca i8
	store i8 99, i8* %5
	ret i32 0
}

