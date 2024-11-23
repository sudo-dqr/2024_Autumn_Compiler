declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@dqr0 = private unnamed_addr constant [4 x i8] c"YEP\00"

define dso_local i32 @main() {
0:
	%1 = alloca i32
	store i32 1, i32* %1
	%2 = load i32, i32* %1
	%3 = icmp sle i32 97, %2
	br i1 %3, label %4, label %6
4:
	%5 = getelementptr [4 x i8], [4 x i8]* @dqr0, i32 0, i32 0
	call void @putstr(i8* %5)
	br label %6
6:
	ret i32 0
}

