declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@a1 = dso_local global [10 x i32] zeroinitializer
@a2 = dso_local global [5 x i32] zeroinitializer
@a3 = dso_local global [5 x i32] zeroinitializer
@a4 = dso_local global [5 x i32] [i32 1, i32 2, i32 3, i32 0, i32 0]
@c1 = dso_local global [10 x i8] zeroinitializer
@c2 = dso_local global [5 x i8] zeroinitializer
@c3 = dso_local global [5 x i8] zeroinitializer
@c4 = dso_local global [5 x i8] c"hey\00\00"
@c5 = dso_local global [10 x i8] [i8 104, i8 101, i8 108, i8 108, i8 111, i8 0, i8 0, i8 0, i8 0, i8 0]
@dqr0 = private unnamed_addr constant [9 x i8] c"21374275\00"
@dqr1 = private unnamed_addr constant [7 x i8] c"sum = \00"
@dqr2 = private unnamed_addr constant [9 x i8] c"c4[0] = \00"
@dqr3 = private unnamed_addr constant [9 x i8] c"c5[0] = \00"
@dqr4 = private unnamed_addr constant [5 x i8] c"t = \00"
@dqr5 = private unnamed_addr constant [11 x i8] c"sum + 1 = \00"

define dso_local i32 @f1(i32* %0, i32 %1) {
2:
	%3 = alloca i32*
	%4 = alloca i32
	store i32* %0, i32** %3
	store i32 %1, i32* %4
	%5 = alloca i32
	store i32 0, i32* %5
	%6 = alloca i32
	store i32 0, i32* %6
	br label %7
7:
	%8 = load i32, i32* %6
	%9 = load i32, i32* %4
	%10 = icmp slt i32 %8, %9
	br i1 %10, label %11, label %21
11:
	%12 = load i32, i32* %5
	%13 = load i32*, i32** %3
	%14 = load i32, i32* %6
	%15 = getelementptr i32, i32* %13, i32 %14
	%16 = load i32, i32* %15
	%17 = add i32 %12, %16
	store i32 %17, i32* %5
	br label %18
18:
	%19 = load i32, i32* %6
	%20 = add i32 %19, 1
	store i32 %20, i32* %6
	br label %7
21:
	%22 = load i32, i32* %5
	ret i32 %22
}

define dso_local i32 @f2(i32 %0) {
1:
	%2 = alloca i32
	store i32 %0, i32* %2
	%3 = load i32, i32* %2
	%4 = icmp eq i32 %3, 1
	br i1 %4, label %5, label %7
5:
	ret i32 1
6:
	br label %22
7:
	%8 = load i32, i32* %2
	%9 = icmp eq i32 %8, 2
	br i1 %9, label %10, label %12
10:
	ret i32 1
11:
	br label %21
12:
	%13 = load i32, i32* %2
	%14 = sub i32 %13, 1
	%15 = call i32 @f2(i32 %14)
	%16 = load i32, i32* %2
	%17 = sub i32 %16, 2
	%18 = call i32 @f2(i32 %17)
	%19 = add i32 %15, %18
	ret i32 %19
20:
	br label %21
21:
	br label %22
22:
	ret i32 -1
}

define dso_local void @f3(i8* %0) {
1:
	%2 = alloca i8*
	store i8* %0, i8** %2
	%3 = load i8*, i8** %2
	%4 = getelementptr i8, i8* %3, i32 0
	%5 = load i8, i8* %4
	%6 = zext i8 %5 to i32
	call void @putch(i32 %6)
	call void @putch(i32 10)
	ret void
}

define dso_local i32 @f4(i32* %0, i32* %1, i32 %2) {
3:
	%4 = alloca i32*
	%5 = alloca i32*
	%6 = alloca i32
	store i32* %0, i32** %4
	store i32* %1, i32** %5
	store i32 %2, i32* %6
	%7 = alloca i32
	%8 = alloca i32
	store i32 0, i32* %8
	store i32 0, i32* %7
	br label %9
9:
	%10 = load i32, i32* %7
	%11 = load i32, i32* %6
	%12 = icmp slt i32 %10, %11
	br i1 %12, label %13, label %28
13:
	%14 = load i32, i32* %8
	%15 = load i32*, i32** %4
	%16 = load i32, i32* %7
	%17 = getelementptr i32, i32* %15, i32 %16
	%18 = load i32, i32* %17
	%19 = load i32*, i32** %5
	%20 = load i32, i32* %7
	%21 = getelementptr i32, i32* %19, i32 %20
	%22 = load i32, i32* %21
	%23 = mul i32 %18, %22
	%24 = add i32 %14, %23
	store i32 %24, i32* %8
	br label %25
25:
	%26 = load i32, i32* %7
	%27 = add i32 %26, 1
	store i32 %27, i32* %7
	br label %9
28:
	%29 = load i32, i32* %8
	ret i32 %29
}

define dso_local i32 @main() {
0:
	%1 = alloca i32
	%2 = getelementptr [9 x i8], [9 x i8]* @dqr0, i32 0, i32 0
	call void @putstr(i8* %2)
	call void @putch(i32 10)
	%3 = getelementptr [5 x i32], [5 x i32]* @a4, i32 0, i32 3
	store i32 4, i32* %3
	%4 = getelementptr [5 x i32], [5 x i32]* @a4, i32 0, i32 4
	store i32 5, i32* %4
	%5 = alloca i32
	%6 = getelementptr [5 x i32], [5 x i32]* @a4, i32 0, i32 0
	%7 = call i32 @f1(i32* %6, i32 5)
	store i32 %7, i32* %5
	%8 = load i32, i32* %5
	%9 = getelementptr [7 x i8], [7 x i8]* @dqr1, i32 0, i32 0
	call void @putstr(i8* %9)
	call void @putint(i32 %8)
	call void @putch(i32 10)
	%10 = getelementptr [5 x i8], [5 x i8]* @c4, i32 0, i32 0
	%11 = load i8, i8* %10
	%12 = getelementptr [9 x i8], [9 x i8]* @dqr2, i32 0, i32 0
	call void @putstr(i8* %12)
	%13 = zext i8 %11 to i32
	call void @putch(i32 %13)
	call void @putch(i32 10)
	%14 = getelementptr [10 x i8], [10 x i8]* @c5, i32 0, i32 0
	%15 = load i8, i8* %14
	%16 = getelementptr [9 x i8], [9 x i8]* @dqr3, i32 0, i32 0
	call void @putstr(i8* %16)
	%17 = zext i8 %15 to i32
	call void @putch(i32 %17)
	call void @putch(i32 10)
	%18 = alloca i32
	store i32 100, i32* %18
	%19 = load i32, i32* %18
	%20 = add i32 %19, 1
	%21 = srem i32 %20, 25
	%22 = mul i32 %21, 5
	%23 = sub i32 %22, 1
	store i32 %23, i32* %18
	%24 = load i32, i32* %18
	%25 = getelementptr [5 x i8], [5 x i8]* @dqr4, i32 0, i32 0
	call void @putstr(i8* %25)
	call void @putint(i32 %24)
	call void @putch(i32 10)
	%26 = call i32 @f2(i32 10)
	store i32 %26, i32* %18
	%27 = load i32, i32* %18
	call void @putint(i32 %27)
	call void @putch(i32 10)
	%28 = alloca [10 x i8]
	%29 = getelementptr [10 x i8], [10 x i8]* %28, i32 0, i32 0
	store i8 49, i8* %29
	%30 = getelementptr [10 x i8], [10 x i8]* %28, i32 0, i32 1
	store i8 50, i8* %30
	%31 = getelementptr [10 x i8], [10 x i8]* %28, i32 0, i32 2
	store i8 51, i8* %31
	%32 = getelementptr [10 x i8], [10 x i8]* %28, i32 0, i32 3
	store i8 52, i8* %32
	%33 = getelementptr [10 x i8], [10 x i8]* %28, i32 0, i32 4
	store i8 53, i8* %33
	%34 = getelementptr [10 x i8], [10 x i8]* %28, i32 0, i32 5
	store i8 54, i8* %34
	%35 = getelementptr [10 x i8], [10 x i8]* %28, i32 0, i32 6
	store i8 0, i8* %35
	%36 = getelementptr [10 x i8], [10 x i8]* %28, i32 0, i32 7
	store i8 0, i8* %36
	%37 = getelementptr [10 x i8], [10 x i8]* %28, i32 0, i32 8
	store i8 0, i8* %37
	%38 = getelementptr [10 x i8], [10 x i8]* %28, i32 0, i32 9
	store i8 0, i8* %38
	%39 = getelementptr [10 x i8], [10 x i8]* %28, i32 0, i32 0
	call void @f3(i8* %39)
	%40 = getelementptr [5 x i8], [5 x i8]* @c4, i32 0, i32 0
	call void @f3(i8* %40)
	%41 = getelementptr [10 x i8], [10 x i8]* @c5, i32 0, i32 0
	call void @f3(i8* %41)
	%42 = alloca [3 x i32]
	%43 = getelementptr [3 x i32], [3 x i32]* %42, i32 0, i32 0
	store i32 2, i32* %43
	%44 = getelementptr [3 x i32], [3 x i32]* %42, i32 0, i32 1
	store i32 3, i32* %44
	%45 = getelementptr [3 x i32], [3 x i32]* %42, i32 0, i32 2
	store i32 4, i32* %45
	%46 = alloca [3 x i32]
	%47 = getelementptr [3 x i32], [3 x i32]* %46, i32 0, i32 0
	store i32 1, i32* %47
	%48 = getelementptr [3 x i32], [3 x i32]* %46, i32 0, i32 1
	store i32 5, i32* %48
	%49 = getelementptr [3 x i32], [3 x i32]* %46, i32 0, i32 2
	store i32 7, i32* %49
	%50 = getelementptr [3 x i32], [3 x i32]* %42, i32 0, i32 0
	%51 = getelementptr [3 x i32], [3 x i32]* %46, i32 0, i32 0
	%52 = getelementptr [3 x i32], [3 x i32]* %42, i32 0, i32 1
	%53 = load i32, i32* %52
	%54 = call i32 @f4(i32* %50, i32* %51, i32 %53)
	%55 = add i32 %54, 1
	%56 = getelementptr [11 x i8], [11 x i8]* @dqr5, i32 0, i32 0
	call void @putstr(i8* %56)
	call void @putint(i32 %55)
	call void @putch(i32 10)
	ret i32 0
}

