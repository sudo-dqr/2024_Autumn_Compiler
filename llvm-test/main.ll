declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@x = dso_local global [10 x i32] zeroinitializer
@i = dso_local global i32 0

define dso_local i32 @main() {
0:
	br label %1
1:
	%2 = load i32, i32* @i
	%3 = icmp sle i32 %2, 10
	br i1 %3, label %4, label %20
4:
	%5 = load i32, i32* @i
	%6 = icmp eq i32 %5, 2
	br i1 %6, label %7, label %9
7:
	store i32 4, i32* @i
	br label %1
8:
	br label %9
9:
	%10 = load i32, i32* @i
	%11 = getelementptr [10 x i32], [10 x i32]* @x, i32 0, i32 %10
	%12 = load i32, i32* @i
	store i32 %12, i32* @i
	%13 = load i32, i32* @i
	%14 = add i32 %13, 1
	store i32 %14, i32* @i
	%15 = load i32, i32* @i
	%16 = icmp eq i32 %15, 5
	br i1 %16, label %17, label %19
17:
	br label %20
18:
	br label %19
19:
	br label %1
20:
	ret i32 0
}

