declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@singleVarDecl = dso_local global i32 -10
@singleVarDecl_0 = dso_local global i32 23
@singleVarDecl_1 = dso_local global i32 10
@singleVarDecl_2 = dso_local global i32 0
@dqr0 = private unnamed_addr constant [13 x i8] c"print int : \00"
@dqr1 = private unnamed_addr constant [9 x i8] c"19373479\00"

define dso_local void @funcDef_void() {
0:
	ret void
}

define dso_local i32 @funcDef_0(i32 %0) {
1:
	%2 = alloca i32
	store i32 %0, i32* %2
	%3 = alloca i32
	%4 = load i32, i32* %2
	%5 = mul i32 %4, 10
	store i32 %5, i32* %3
	%6 = load i32, i32* %3
	ret i32 %6
}

define dso_local i32 @funcDef_1(i32 %0, i32 %1) {
2:
	%3 = alloca i32
	%4 = alloca i32
	store i32 %0, i32* %3
	store i32 %1, i32* %4
	%5 = alloca i32
	%6 = load i32, i32* %3
	%7 = load i32, i32* %4
	%8 = mul i32 %6, %7
	store i32 %8, i32* %5
	%9 = alloca i32
	%10 = alloca i32
	%11 = load i32, i32* %4
	%12 = icmp ne i32 %11, 0
	br i1 %12, label %13, label %22
13:
	%14 = load i32, i32* %5
	%15 = load i32, i32* %3
	%16 = load i32, i32* %4
	%17 = srem i32 %15, %16
	%18 = add i32 %14, %17
	store i32 %18, i32* %9
	%19 = load i32, i32* %3
	%20 = load i32, i32* %4
	%21 = sdiv i32 %19, %20
	store i32 %21, i32* %10
	br label %28
22:
	%23 = load i32, i32* %5
	%24 = load i32, i32* %3
	%25 = add i32 %23, %24
	store i32 %25, i32* %9
	%26 = load i32, i32* %3
	%27 = sdiv i32 %26, 2
	store i32 %27, i32* %10
	br label %28
28:
	%29 = load i32, i32* %9
	%30 = load i32, i32* %5
	%31 = sub i32 %29, %30
	store i32 %31, i32* %9
	%32 = load i32, i32* %5
	%33 = load i32, i32* %9
	%34 = add i32 %32, %33
	%35 = load i32, i32* %5
	%36 = icmp slt i32 %35, 0
	br i1 %36, label %37, label %40
37:
	%38 = load i32, i32* %5
	%39 = sub i32 0, %38
	store i32 %39, i32* %5
	br label %40
40:
	%41 = load i32, i32* %5
	%42 = add i32 1, %41
	%43 = load i32, i32* %9
	%44 = load i32, i32* %10
	%45 = add i32 %43, %44
	%46 = mul i32 %42, %45
	ret i32 %46
}

define dso_local void @printInt(i32 %0) {
1:
	%2 = alloca i32
	store i32 %0, i32* %2
	%3 = load i32, i32* %2
	%4 = getelementptr [13 x i8], [13 x i8]* @dqr0, i32 0, i32 0
	call void @putstr(i8* %4)
	call void @putint(i32 %3)
	call void @putch(i32 10)
	ret void
}

define dso_local i32 @main() {
0:
	%1 = getelementptr [9 x i8], [9 x i8]* @dqr1, i32 0, i32 0
	call void @putstr(i8* %1)
	call void @putch(i32 10)
	%2 = alloca i32
	store i32 10, i32* %2
	%3 = alloca i32
	%4 = alloca i32
	%5 = alloca i32
	%6 = alloca i32
	%7 = call i32 @getint()
	store i32 %7, i32* %3
	%8 = call i32 @getint()
	store i32 %8, i32* %4
	%9 = call i32 @getint()
	store i32 %9, i32* %5
	%10 = call i32 @getint()
	store i32 %10, i32* %6
	%11 = load i32, i32* %3
	%12 = icmp sgt i32 %11, 5
	br i1 %12, label %13, label %14
13:
	store i32 5, i32* %3
	br label %14
14:
	br label %15
15:
	%16 = load i32, i32* %2
	%17 = icmp ne i32 %16, 0
	br i1 %17, label %18, label %69
18:
	%19 = load i32, i32* %2
	%20 = sub i32 %19, 1
	store i32 %20, i32* %2
	%21 = load i32, i32* %4
	%22 = load i32, i32* %2
	%23 = icmp sge i32 %21, %22
	br i1 %23, label %24, label %31
24:
	%25 = load i32, i32* %4
	%26 = load i32, i32* %2
	%27 = add i32 %26, 1
	%28 = sdiv i32 %25, %27
	%29 = load i32, i32* %2
	%30 = add i32 %28, %29
	store i32 %30, i32* %4
	br label %31
31:
	%32 = load i32, i32* %5
	%33 = load i32, i32* %2
	%34 = icmp sle i32 %32, %33
	br i1 %34, label %35, label %39
35:
	%36 = load i32, i32* %5
	%37 = load i32, i32* %2
	%38 = mul i32 %36, %37
	store i32 %38, i32* %5
	br label %44
39:
	%40 = load i32, i32* %5
	%41 = load i32, i32* %2
	%42 = add i32 %41, 3
	%43 = srem i32 %40, %42
	store i32 %43, i32* %5
	br label %44
44:
	br label %45
45:
	%46 = load i32, i32* %6
	%47 = load i32, i32* %5
	%48 = icmp slt i32 %46, %47
	br i1 %48, label %49, label %68
49:
	%50 = load i32, i32* %6
	%51 = load i32, i32* %2
	%52 = add i32 %50, %51
	store i32 %52, i32* %6
	%53 = load i32, i32* %6
	%54 = load i32, i32* %3
	%55 = icmp eq i32 %53, %54
	br i1 %55, label %56, label %58
56:
	br label %68
57:
	br label %58
58:
	%59 = load i32, i32* %6
	%60 = load i32, i32* %4
	%61 = icmp ne i32 %59, %60
	br i1 %61, label %62, label %67
62:
	%63 = load i32, i32* %4
	%64 = load i32, i32* %6
	%65 = add i32 %63, %64
	store i32 %65, i32* %6
	br label %45
66:
	br label %67
67:
	br label %45
68:
	br label %15
69:
	%70 = load i32, i32* %2
	%71 = icmp eq i32 %70, 0
	%72 = zext i1 %71 to i32
	%73 = icmp ne i32 %72, 0
	br i1 %73, label %74, label %76
74:
	%75 = load i32, i32* %2
	call void @printInt(i32 %75)
	br label %76
76:
	%77 = load i32, i32* %3
	call void @printInt(i32 %77)
	%78 = load i32, i32* %4
	call void @printInt(i32 %78)
	%79 = load i32, i32* %5
	call void @printInt(i32 %79)
	%80 = load i32, i32* %6
	call void @printInt(i32 %80)
	%81 = alloca i32
	%82 = load i32, i32* %6
	%83 = load i32, i32* %5
	%84 = call i32 @funcDef_1(i32 %82, i32 %83)
	store i32 %84, i32* %81
	%85 = alloca i32
	%86 = load i32, i32* %81
	%87 = load i32, i32* %4
	%88 = call i32 @funcDef_0(i32 %87)
	%89 = call i32 @funcDef_1(i32 %86, i32 %88)
	store i32 %89, i32* %85
	call void @funcDef_void()
	%90 = load i32, i32* %81
	call void @printInt(i32 %90)
	%91 = load i32, i32* %85
	call void @printInt(i32 %91)
	%92 = load i32, i32* @singleVarDecl
	%93 = load i32, i32* @singleVarDecl_2
	%94 = call i32 @funcDef_1(i32 %92, i32 %93)
	%95 = call i32 @funcDef_1(i32 13, i32 3)
	%96 = call i32 @funcDef_1(i32 %94, i32 %95)
	store i32 %96, i32* @singleVarDecl_2
	%97 = load i32, i32* @singleVarDecl_2
	call void @printInt(i32 %97)
	ret i32 0
}

