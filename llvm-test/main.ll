declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@a = dso_local global i32 1000

define dso_local i32 @foo(i32 %0, i32 %1) {
	%3 = alloca i32
	%4 = alloca i32
	store i32 %0, i32* %3
	store i32 %1, i32* %4
	%5 = load i32, i32* %3
	%6 = load i32, i32* %4
	%7 = add i32 %5, %6
	ret i32 %7
}

define dso_local void @bar() {
	store i32 1200, i32* @a
	ret void
}

define dso_local i32 @main() {
	call void @bar()
	%1 = alloca i32
	%2 = load i32, i32* @a
	store i32 %2, i32* %1
	%3 = call i32 @getint()
	store i32 %3, i32* @a
	%4 = load i32, i32* @a
	%5 = load i32, i32* %1
	%6 = call i32 @foo(i32 %4, i32 %5)
	call void @putint(i32 %6)
	call void @putch(i32 10)
	ret i32 0
}

