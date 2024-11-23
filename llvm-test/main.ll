declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@a = dso_local global [10 x i32] zeroinitializer
@b = dso_local global [2 x i32] [i32 1, i32 2]
@aa = dso_local global [10 x i8] zeroinitializer
@bb = dso_local global [10 x i8] c"hello\00\00\00\00\00"

define dso_local i32 @func1(i32* %0, i32 %1, i8* %2, i8 %3) {
4:
	%5 = alloca i32*
	%6 = alloca i32
	%7 = alloca i8*
	%8 = alloca i8
	store i32* %0, i32** %5
	store i32 %1, i32* %6
	store i8* %2, i8** %7
	store i8 %3, i8* %8
	%9 = load i32*, i32** %5
	%10 = getelementptr i32, i32* %9, i32 1
	%11 = load i32, i32* %10
	%12 = load i32, i32* %6
	%13 = load i8*, i8** %7
	%14 = getelementptr i8, i8* %13, i32 1
	%15 = load i8, i8* %14
	%16 = load i8, i8* %8
	call void @putint(i32 %11)
	call void @putch(i32 44)
	call void @putint(i32 %12)
	call void @putch(i32 44)
	%17 = zext i8 %15 to i32
	call void @putch(i32 %17)
	call void @putch(i32 44)
	%18 = zext i8 %16 to i32
	call void @putch(i32 %18)
	call void @putch(i32 10)
	%19 = load i32*, i32** %5
	%20 = getelementptr i32, i32* %19, i32 0
	%21 = load i8, i8* %8
	%22 = zext i8 %21 to i32
	store i32 %22, i32* %20
	%23 = load i32*, i32** %5
	%24 = getelementptr i32, i32* %23, i32 1
	%25 = load i32, i32* %6
	store i32 %25, i32* %24
	%26 = load i8*, i8** %7
	%27 = getelementptr i8, i8* %26, i32 1
	%28 = load i8, i8* %8
	store i8 %28, i8* %27
	ret i32 0
}

define dso_local i32 @func2(i32* %0, i32 %1, i8* %2, i8 %3) {
4:
	%5 = alloca i32*
	%6 = alloca i32
	%7 = alloca i8*
	%8 = alloca i8
	store i32* %0, i32** %5
	store i32 %1, i32* %6
	store i8* %2, i8** %7
	store i8 %3, i8* %8
	%9 = load i32*, i32** %5
	%10 = getelementptr i32, i32* %9, i32 0
	%11 = load i32, i32* %6
	%12 = load i8*, i8** %7
	%13 = getelementptr i8, i8* %12, i32 0
	%14 = load i8, i8* %8
	%15 = call i32 @func1(i32* %10, i32 %11, i8* %13, i8 %14)
	%16 = load i32*, i32** %5
	%17 = getelementptr i32, i32* %16, i32 1
	%18 = load i32, i32* %17
	%19 = load i32, i32* %6
	%20 = load i8*, i8** %7
	%21 = getelementptr i8, i8* %20, i32 1
	%22 = load i8, i8* %21
	%23 = load i8, i8* %8
	call void @putint(i32 %18)
	call void @putch(i32 44)
	call void @putint(i32 %19)
	call void @putch(i32 44)
	%24 = zext i8 %22 to i32
	call void @putch(i32 %24)
	call void @putch(i32 44)
	%25 = zext i8 %23 to i32
	call void @putch(i32 %25)
	call void @putch(i32 10)
	ret i32 0
}

define dso_local i32 @main() {
0:
	%1 = alloca [10 x i32]
	%2 = alloca [10 x i8]
	%3 = alloca [2 x i32]
	%4 = getelementptr [2 x i32], [2 x i32]* %3, i32 0, i32 0
	store i32 1, i32* %4
	%5 = getelementptr [2 x i32], [2 x i32]* %3, i32 0, i32 1
	store i32 2, i32* %5
	%6 = alloca [3 x i8]
	%7 = getelementptr [3 x i8], [3 x i8]* %6, i32 0, i32 0
	store i8 49, i8* %7
	%8 = getelementptr [3 x i8], [3 x i8]* %6, i32 0, i32 1
	store i8 0, i8* %8
	%9 = getelementptr [3 x i8], [3 x i8]* %6, i32 0, i32 2
	store i8 0, i8* %9
	%10 = getelementptr [10 x i32], [10 x i32]* @a, i32 0, i32 0
	%11 = getelementptr [10 x i32], [10 x i32]* @a, i32 0, i32 1
	%12 = load i32, i32* %11
	%13 = getelementptr [10 x i8], [10 x i8]* @aa, i32 0, i32 0
	%14 = getelementptr [10 x i8], [10 x i8]* @aa, i32 0, i32 1
	%15 = load i8, i8* %14
	%16 = call i32 @func2(i32* %10, i32 %12, i8* %13, i8 %15)
	%17 = getelementptr [10 x i32], [10 x i32]* %1, i32 0, i32 0
	%18 = getelementptr [10 x i32], [10 x i32]* %1, i32 0, i32 1
	%19 = load i32, i32* %18
	%20 = getelementptr [10 x i8], [10 x i8]* %2, i32 0, i32 0
	%21 = getelementptr [10 x i8], [10 x i8]* %2, i32 0, i32 1
	%22 = load i8, i8* %21
	%23 = call i32 @func2(i32* %17, i32 %19, i8* %20, i8 %22)
	%24 = getelementptr [2 x i32], [2 x i32]* %3, i32 0, i32 0
	%25 = getelementptr [2 x i32], [2 x i32]* %3, i32 0, i32 1
	%26 = load i32, i32* %25
	%27 = getelementptr [3 x i8], [3 x i8]* %6, i32 0, i32 0
	%28 = getelementptr [3 x i8], [3 x i8]* %6, i32 0, i32 1
	%29 = load i8, i8* %28
	%30 = call i32 @func2(i32* %24, i32 %26, i8* %27, i8 %29)
	ret i32 0
}

