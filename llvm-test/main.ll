declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@s = dso_local global [10 x i8] c"\0Adqr\00\00\00\00\00\00"
@a = dso_local global [10 x i8] c"h\0Ax\00\00\00\00\00\00\00"

define dso_local i32 @main() {
0:
	%1 = getelementptr [10 x i8], [10 x i8]* @s, i32 0, i32 0
	%2 = load i8, i8* %1
	%3 = zext i8 %2 to i32
	call void @putch(i32 %3)
	%4 = getelementptr [10 x i8], [10 x i8]* @a, i32 0, i32 0
	%5 = load i8, i8* %4
	%6 = getelementptr [10 x i8], [10 x i8]* @a, i32 0, i32 1
	%7 = load i8, i8* %6
	%8 = getelementptr [10 x i8], [10 x i8]* @a, i32 0, i32 2
	%9 = load i8, i8* %8
	%10 = zext i8 %5 to i32
	call void @putch(i32 %10)
	%11 = zext i8 %7 to i32
	call void @putch(i32 %11)
	%12 = zext i8 %9 to i32
	call void @putch(i32 %12)
	ret i32 0
}

