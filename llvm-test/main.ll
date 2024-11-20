declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@a = dso_local global i32 1
@b = dso_local global i32 3

define dso_local i32 @main() {
	%1 = alloca i32
	%2 = load i32, i32* @b
	%3 = add i32 %2, 4
	store i32 %3, i32* %1
	%4 = load i32, i32* @a
	%5 = load i32, i32* @b
	%6 = add i32 %4, %5
	%7 = load i32, i32* %1
	%8 = add i32 %6, %7
	ret i32 %8
}

