declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@constIntArray = dso_local global [3 x i32] [i32 10, i32 20, i32 30]
@constCharArray = dso_local global [5 x i8] [i8 65, i8 66, i8 67, i8 68, i8 69]
@constCharArray2 = dso_local global [5 x i8] c"abc\00\00"
@intArray = dso_local global [5 x i32] zeroinitializer
@charArray = dso_local global [5 x i8] zeroinitializer
@dqr0 = private unnamed_addr constant [31 x i8] c"Function with parameters: a = \00"
@dqr1 = private unnamed_addr constant [7 x i8] c", b = \00"
@dqr2 = private unnamed_addr constant [11 x i8] c" arr[0] = \00"
@dqr3 = private unnamed_addr constant [12 x i8] c", str[0] = \00"
@dqr4 = private unnamed_addr constant [25 x i8] c"Sum in func_with_param: \00"
@dqr5 = private unnamed_addr constant [9 x i8] c"22373141\00"
@dqr6 = private unnamed_addr constant [23 x i8] c"Negative intArray[0]: \00"
@dqr7 = private unnamed_addr constant [23 x i8] c"Positive intArray[0]: \00"
@dqr8 = private unnamed_addr constant [11 x i8] c"Quotient: \00"
@dqr9 = private unnamed_addr constant [14 x i8] c", Remainder: \00"
@dqr10 = private unnamed_addr constant [22 x i8] c"Sum of ASCII codes1: \00"
@dqr11 = private unnamed_addr constant [22 x i8] c"Sum of ASCII codes2: \00"
@dqr12 = private unnamed_addr constant [6 x i8] c"x1 = \00"
@dqr13 = private unnamed_addr constant [6 x i8] c"a1 = \00"
@dqr14 = private unnamed_addr constant [12 x i8] c", as char: \00"

define dso_local i32 @func_with_param(i32 %0, i8 %1, i32* %2, i8* %3) {
4:
	%5 = alloca i32
	%6 = alloca i8
	%7 = alloca i32*
	%8 = alloca i8*
	store i32 %0, i32* %5
	store i8 %1, i8* %6
	store i32* %2, i32** %7
	store i8* %3, i8** %8
	%9 = load i32, i32* %5
	%10 = load i8, i8* %6
	%11 = load i32*, i32** %7
	%12 = getelementptr i32, i32* %11, i32 0
	%13 = load i32, i32* %12
	%14 = load i8*, i8** %8
	%15 = getelementptr i8, i8* %14, i32 0
	%16 = load i8, i8* %15
	%17 = getelementptr [31 x i8], [31 x i8]* @dqr0, i32 0, i32 0
	call void @putstr(i8* %17)
	call void @putint(i32 %9)
	%18 = getelementptr [7 x i8], [7 x i8]* @dqr1, i32 0, i32 0
	call void @putstr(i8* %18)
	%19 = zext i8 %10 to i32
	call void @putch(i32 %19)
	%20 = getelementptr [11 x i8], [11 x i8]* @dqr2, i32 0, i32 0
	call void @putstr(i8* %20)
	call void @putint(i32 %13)
	%21 = getelementptr [12 x i8], [12 x i8]* @dqr3, i32 0, i32 0
	call void @putstr(i8* %21)
	%22 = zext i8 %16 to i32
	call void @putch(i32 %22)
	call void @putch(i32 10)
	%23 = alloca i32
	%24 = load i32, i32* %5
	%25 = load i8, i8* %6
	%26 = zext i8 %25 to i32
	%27 = add i32 %24, %26
	%28 = load i32*, i32** %7
	%29 = getelementptr i32, i32* %28, i32 0
	%30 = load i32, i32* %29
	%31 = add i32 %27, %30
	%32 = load i8*, i8** %8
	%33 = getelementptr i8, i8* %32, i32 0
	%34 = load i8, i8* %33
	%35 = zext i8 %34 to i32
	%36 = add i32 %31, %35
	store i32 %36, i32* %23
	%37 = load i32, i32* %23
	%38 = getelementptr [25 x i8], [25 x i8]* @dqr4, i32 0, i32 0
	call void @putstr(i8* %38)
	call void @putint(i32 %37)
	call void @putch(i32 10)
	%39 = load i32, i32* %23
	ret i32 %39
}

define dso_local i32 @main() {
0:
	%1 = getelementptr [9 x i8], [9 x i8]* @dqr5, i32 0, i32 0
	call void @putstr(i8* %1)
	call void @putch(i32 10)
	%2 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 0
	%3 = getelementptr [3 x i32], [3 x i32]* @constIntArray, i32 0, i32 0
	%4 = load i32, i32* %3
	store i32 %4, i32* %2
	%5 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 1
	%6 = getelementptr [3 x i32], [3 x i32]* @constIntArray, i32 0, i32 1
	%7 = load i32, i32* %6
	store i32 %7, i32* %5
	%8 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 2
	%9 = getelementptr [3 x i32], [3 x i32]* @constIntArray, i32 0, i32 2
	%10 = load i32, i32* %9
	store i32 %10, i32* %8
	%11 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 3
	%12 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 0
	%13 = load i32, i32* %12
	%14 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 1
	%15 = load i32, i32* %14
	%16 = add i32 %13, %15
	store i32 %16, i32* %11
	%17 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 4
	%18 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 3
	%19 = load i32, i32* %18
	%20 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 2
	%21 = load i32, i32* %20
	%22 = add i32 %19, %21
	store i32 %22, i32* %17
	%23 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 0
	%24 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 0
	%25 = load i32, i32* %24
	%26 = sub i32 0, %25
	store i32 %26, i32* %23
	%27 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 0
	%28 = load i32, i32* %27
	%29 = getelementptr [23 x i8], [23 x i8]* @dqr6, i32 0, i32 0
	call void @putstr(i8* %29)
	call void @putint(i32 %28)
	call void @putch(i32 10)
	%30 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 0
	%31 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 0
	%32 = load i32, i32* %31
	store i32 %32, i32* %30
	%33 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 0
	%34 = load i32, i32* %33
	%35 = getelementptr [23 x i8], [23 x i8]* @dqr7, i32 0, i32 0
	call void @putstr(i8* %35)
	call void @putint(i32 %34)
	call void @putch(i32 10)
	%36 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 1
	%37 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 3
	%38 = load i32, i32* %37
	%39 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 2
	%40 = load i32, i32* %39
	%41 = sdiv i32 %38, %40
	store i32 %41, i32* %36
	%42 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 2
	%43 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 3
	%44 = load i32, i32* %43
	%45 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 2
	%46 = load i32, i32* %45
	%47 = srem i32 %44, %46
	store i32 %47, i32* %42
	%48 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 1
	%49 = load i32, i32* %48
	%50 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 2
	%51 = load i32, i32* %50
	%52 = getelementptr [11 x i8], [11 x i8]* @dqr8, i32 0, i32 0
	call void @putstr(i8* %52)
	call void @putint(i32 %49)
	%53 = getelementptr [14 x i8], [14 x i8]* @dqr9, i32 0, i32 0
	call void @putstr(i8* %53)
	call void @putint(i32 %51)
	call void @putch(i32 10)
	%54 = getelementptr [5 x i8], [5 x i8]* @charArray, i32 0, i32 0
	%55 = getelementptr [5 x i8], [5 x i8]* @constCharArray, i32 0, i32 0
	%56 = load i8, i8* %55
	%57 = getelementptr [5 x i8], [5 x i8]* @constCharArray, i32 0, i32 1
	%58 = load i8, i8* %57
	%59 = zext i8 %56 to i32
	%60 = zext i8 %58 to i32
	%61 = add i32 %59, %60
	%62 = getelementptr [5 x i8], [5 x i8]* @constCharArray, i32 0, i32 2
	%63 = load i8, i8* %62
	%64 = zext i8 %63 to i32
	%65 = add i32 %61, %64
	%66 = getelementptr [5 x i8], [5 x i8]* @constCharArray, i32 0, i32 3
	%67 = load i8, i8* %66
	%68 = zext i8 %67 to i32
	%69 = add i32 %65, %68
	%70 = getelementptr [5 x i8], [5 x i8]* @constCharArray, i32 0, i32 4
	%71 = load i8, i8* %70
	%72 = zext i8 %71 to i32
	%73 = add i32 %69, %72
	%74 = trunc i32 %73 to i8
	store i8 %74, i8* %54
	%75 = getelementptr [5 x i8], [5 x i8]* @charArray, i32 0, i32 0
	%76 = load i8, i8* %75
	%77 = getelementptr [5 x i8], [5 x i8]* @charArray, i32 0, i32 0
	%78 = load i8, i8* %77
	%79 = getelementptr [22 x i8], [22 x i8]* @dqr10, i32 0, i32 0
	call void @putstr(i8* %79)
	%80 = zext i8 %76 to i32
	call void @putint(i32 %80)
	call void @putch(i32 32)
	%81 = zext i8 %78 to i32
	call void @putch(i32 %81)
	call void @putch(i32 10)
	%82 = alloca i32
	%83 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 0
	%84 = load i32, i32* %83
	%85 = getelementptr [5 x i8], [5 x i8]* @charArray, i32 0, i32 0
	%86 = load i8, i8* %85
	%87 = getelementptr [5 x i32], [5 x i32]* @intArray, i32 0, i32 0
	%88 = getelementptr [5 x i8], [5 x i8]* @charArray, i32 0, i32 0
	%89 = call i32 @func_with_param(i32 %84, i8 %86, i32* %87, i8* %88)
	store i32 %89, i32* %82
	%90 = alloca i32
	%91 = getelementptr [5 x i8], [5 x i8]* @constCharArray2, i32 0, i32 0
	%92 = load i8, i8* %91
	%93 = getelementptr [5 x i8], [5 x i8]* @constCharArray2, i32 0, i32 1
	%94 = load i8, i8* %93
	%95 = zext i8 %92 to i32
	%96 = zext i8 %94 to i32
	%97 = add i32 %95, %96
	%98 = getelementptr [5 x i8], [5 x i8]* @constCharArray2, i32 0, i32 2
	%99 = load i8, i8* %98
	%100 = zext i8 %99 to i32
	%101 = add i32 %97, %100
	%102 = getelementptr [5 x i8], [5 x i8]* @constCharArray2, i32 0, i32 3
	%103 = load i8, i8* %102
	%104 = zext i8 %103 to i32
	%105 = add i32 %101, %104
	%106 = getelementptr [5 x i8], [5 x i8]* @constCharArray2, i32 0, i32 4
	%107 = load i8, i8* %106
	%108 = zext i8 %107 to i32
	%109 = add i32 %105, %108
	store i32 %109, i32* %90
	%110 = alloca i8
	%111 = getelementptr [5 x i8], [5 x i8]* @constCharArray2, i32 0, i32 0
	%112 = load i8, i8* %111
	%113 = getelementptr [5 x i8], [5 x i8]* @constCharArray2, i32 0, i32 1
	%114 = load i8, i8* %113
	%115 = zext i8 %112 to i32
	%116 = zext i8 %114 to i32
	%117 = add i32 %115, %116
	%118 = getelementptr [5 x i8], [5 x i8]* @constCharArray2, i32 0, i32 2
	%119 = load i8, i8* %118
	%120 = zext i8 %119 to i32
	%121 = add i32 %117, %120
	%122 = getelementptr [5 x i8], [5 x i8]* @constCharArray2, i32 0, i32 3
	%123 = load i8, i8* %122
	%124 = zext i8 %123 to i32
	%125 = add i32 %121, %124
	%126 = getelementptr [5 x i8], [5 x i8]* @constCharArray2, i32 0, i32 4
	%127 = load i8, i8* %126
	%128 = zext i8 %127 to i32
	%129 = add i32 %125, %128
	%130 = trunc i32 %129 to i8
	store i8 %130, i8* %110
	%131 = load i32, i32* %90
	%132 = load i8, i8* %110
	%133 = getelementptr [22 x i8], [22 x i8]* @dqr11, i32 0, i32 0
	call void @putstr(i8* %133)
	call void @putint(i32 %131)
	call void @putch(i32 32)
	%134 = zext i8 %132 to i32
	call void @putch(i32 %134)
	call void @putch(i32 10)
	%135 = alloca i32
	store i32 107, i32* %135
	%136 = load i32, i32* %135
	%137 = getelementptr [6 x i8], [6 x i8]* @dqr12, i32 0, i32 0
	call void @putstr(i8* %137)
	call void @putint(i32 %136)
	call void @putch(i32 10)
	%138 = alloca i8
	store i8 41, i8* %138
	%139 = load i8, i8* %138
	%140 = load i8, i8* %138
	%141 = getelementptr [6 x i8], [6 x i8]* @dqr13, i32 0, i32 0
	call void @putstr(i8* %141)
	%142 = zext i8 %139 to i32
	call void @putint(i32 %142)
	%143 = getelementptr [12 x i8], [12 x i8]* @dqr14, i32 0, i32 0
	call void @putstr(i8* %143)
	%144 = zext i8 %140 to i32
	call void @putch(i32 %144)
	call void @putch(i32 10)
	ret i32 0
}

