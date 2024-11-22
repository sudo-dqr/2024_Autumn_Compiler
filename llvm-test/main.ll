declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@x = dso_local global i8 97
@y = dso_local global i32 2

define dso_local void @test(i32 %0, i8 %1) {
2:
	%3 = alloca i32
	%4 = alloca i8
	store i32 %0, i32* %3
	store i8 %1, i8* %4
	ret void
}

define dso_local i32 @main() {
0:
	%1 = alloca i32
	store i32 20, i32* %1
	%2 = alloca i8
	store i8 97, i8* %2
	%3 = load i8, i8* %2
	%4 = zext i8 %3 to i32
	%5 = load i32, i32* %1
	%6 = trunc i32 %5 to i8
	call void @test(i32 %4, i8 %6)
	ret i32 0
}

