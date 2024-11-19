declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@a = dso_local global i32 1

define dso_local i32 @add(i32 %0, i32 %1) {
	%3 = alloca i32
	%4 = alloca i32
	store i32 %0, i32* %3
	store i32 %1, i32* %4
	%5 = load i32, i32* %3
	%6 = load i32, i32* %4
	%7 = add i32 %5, %6
	ret i32 %7
}

define dso_local i32 @main() {
	%1 = alloca i32
	store i32 2, i32* %1
	%2 = load i32, i32* @a
	%3 = load i32, i32* %1
	%4= call i32 @add(i32 %2, i32 %3)
	ret i32 %4
}

