; ModuleID = 'main.c'
source_filename = "main.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@aaaaaa = dso_local constant i32 100, align 4
@bbbbbb = dso_local constant i32 200, align 4
@cccccc = dso_local constant i32 300, align 4
@MAX = dso_local constant i32 1000000, align 4
@MAX_CHAR = dso_local constant i8 122, align 1
@dp = dso_local constant <{ i32, i32, i32, [17 x i32] }> <{ i32 1, i32 2, i32 4, [17 x i32] zeroinitializer }>, align 16
@dp1 = dso_local constant <{ i8, i8, i8, [17 x i8] }> <{ i8 97, i8 98, i8 99, [17 x i8] zeroinitializer }>, align 16
@fas = dso_local constant [7 x i8] c"dsadsa\00", align 1
@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@__const.main.bbbbb = private unnamed_addr constant [7 x i8] c"dsadsa\00", align 1
@.str.1 = private unnamed_addr constant [10 x i8] c"22371147\0A\00", align 1
@.str.2 = private unnamed_addr constant [7 x i8] c"%d %c\0A\00", align 1
@.str.3 = private unnamed_addr constant [34 x i8] c"%d %c %d %c %c %d %c %d %d %d %d\0A\00", align 1
@__const.main.arr = private unnamed_addr constant <{ [19 x i32], [11 x i32] }> <{ [19 x i32] [i32 -1, i32 -2, i32 3, i32 34, i32 5, i32 16, i32 7, i32 8, i32 -9, i32 10, i32 131, i32 -12, i32 13, i32 124, i32 15, i32 16, i32 137, i32 -18, i32 19], [11 x i32] zeroinitializer }>, align 16
@.str.4 = private unnamed_addr constant [8 x i8] c"%d%d%d\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @isPrime(i32 %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  %5 = load i32, i32* %3, align 4
  %6 = icmp sle i32 %5, 1
  br i1 %6, label %7, label %8

7:                                                ; preds = %1
  store i32 0, i32* %2, align 4
  br label %26

8:                                                ; preds = %1
  store i32 2, i32* %4, align 4
  br label %9

9:                                                ; preds = %22, %8
  %10 = load i32, i32* %4, align 4
  %11 = load i32, i32* %4, align 4
  %12 = mul nsw i32 %10, %11
  %13 = load i32, i32* %3, align 4
  %14 = icmp sle i32 %12, %13
  br i1 %14, label %15, label %25

15:                                               ; preds = %9
  %16 = load i32, i32* %3, align 4
  %17 = load i32, i32* %4, align 4
  %18 = srem i32 %16, %17
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %20, label %21

20:                                               ; preds = %15
  store i32 0, i32* %2, align 4
  br label %26

21:                                               ; preds = %15
  br label %22

22:                                               ; preds = %21
  %23 = load i32, i32* %4, align 4
  %24 = add nsw i32 %23, 1
  store i32 %24, i32* %4, align 4
  br label %9, !llvm.loop !2

25:                                               ; preds = %9
  store i32 1, i32* %2, align 4
  br label %26

26:                                               ; preds = %25, %20, %7
  %27 = load i32, i32* %2, align 4
  ret i32 %27
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local signext i8 @getAChar() #0 {
  ret i8 97
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @getSum(i32 %0, i32 %1, i32 %2) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store i32 %0, i32* %4, align 4
  store i32 %1, i32* %5, align 4
  store i32 %2, i32* %6, align 4
  %7 = load i32, i32* %4, align 4
  %8 = load i32, i32* %5, align 4
  %9 = add nsw i32 %7, %8
  %10 = load i32, i32* %6, align 4
  %11 = add nsw i32 %9, %10
  ret i32 %11
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @getSum1(i32 %0, i32 %1, i32 %2) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store i32 %0, i32* %4, align 4
  store i32 %1, i32* %5, align 4
  store i32 %2, i32* %6, align 4
  %7 = load i32, i32* %4, align 4
  %8 = load i32, i32* %5, align 4
  %9 = load i32, i32* %6, align 4
  %10 = sdiv i32 %8, %9
  %11 = add nsw i32 %7, %10
  ret i32 %11
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local signext i8 @getAChar1() #0 {
  %1 = call signext i8 @getAChar()
  ret i8 %1
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @sumOne2Ten() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 1, i32* %2, align 4
  br label %3

3:                                                ; preds = %10, %0
  %4 = load i32, i32* %2, align 4
  %5 = icmp sle i32 %4, 100
  br i1 %5, label %6, label %13

6:                                                ; preds = %3
  %7 = load i32, i32* %1, align 4
  %8 = load i32, i32* %2, align 4
  %9 = add nsw i32 %7, %8
  store i32 %9, i32* %1, align 4
  br label %10

10:                                               ; preds = %6
  %11 = load i32, i32* %2, align 4
  %12 = add nsw i32 %11, 1
  store i32 %12, i32* %2, align 4
  br label %3, !llvm.loop !4

13:                                               ; preds = %3
  %14 = load i32, i32* %1, align 4
  %15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 %14)
  ret void
}

declare dso_local i32 @printf(i8*, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @sumOne2Ten1() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 1, i32* %2, align 4
  br label %3

3:                                                ; preds = %10, %0
  %4 = load i32, i32* %2, align 4
  %5 = icmp sle i32 %4, 100
  br i1 %5, label %6, label %13

6:                                                ; preds = %3
  %7 = load i32, i32* %1, align 4
  %8 = load i32, i32* %2, align 4
  %9 = add nsw i32 %7, %8
  store i32 %9, i32* %1, align 4
  br label %10

10:                                               ; preds = %6
  %11 = load i32, i32* %2, align 4
  %12 = add nsw i32 %11, 1
  store i32 %12, i32* %2, align 4
  br label %3, !llvm.loop !5

13:                                               ; preds = %3
  %14 = load i32, i32* %1, align 4
  %15 = icmp sgt i32 %14, 0
  br i1 %15, label %16, label %17

16:                                               ; preds = %13
  br label %20

17:                                               ; preds = %13
  %18 = load i32, i32* %1, align 4
  %19 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 %18)
  br label %20

20:                                               ; preds = %17, %16
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @BubbleSort(i32* %0, i32 %1) #0 {
  %3 = alloca i32*, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  store i32* %0, i32** %3, align 8
  store i32 %1, i32* %4, align 4
  store i32 0, i32* %5, align 4
  br label %9

9:                                                ; preds = %65, %2
  %10 = load i32, i32* %5, align 4
  %11 = load i32, i32* %4, align 4
  %12 = icmp slt i32 %10, %11
  br i1 %12, label %13, label %68

13:                                               ; preds = %9
  store i32 0, i32* %7, align 4
  store i32 0, i32* %6, align 4
  br label %14

14:                                               ; preds = %57, %13
  %15 = load i32, i32* %6, align 4
  %16 = load i32, i32* %4, align 4
  %17 = load i32, i32* %5, align 4
  %18 = sub nsw i32 %16, %17
  %19 = sub nsw i32 %18, 1
  %20 = icmp slt i32 %15, %19
  br i1 %20, label %21, label %60

21:                                               ; preds = %14
  %22 = load i32*, i32** %3, align 8
  %23 = load i32, i32* %6, align 4
  %24 = sext i32 %23 to i64
  %25 = getelementptr inbounds i32, i32* %22, i64 %24
  %26 = load i32, i32* %25, align 4
  %27 = load i32*, i32** %3, align 8
  %28 = load i32, i32* %6, align 4
  %29 = add nsw i32 %28, 1
  %30 = sext i32 %29 to i64
  %31 = getelementptr inbounds i32, i32* %27, i64 %30
  %32 = load i32, i32* %31, align 4
  %33 = icmp sgt i32 %26, %32
  br i1 %33, label %34, label %56

34:                                               ; preds = %21
  %35 = load i32*, i32** %3, align 8
  %36 = load i32, i32* %6, align 4
  %37 = sext i32 %36 to i64
  %38 = getelementptr inbounds i32, i32* %35, i64 %37
  %39 = load i32, i32* %38, align 4
  store i32 %39, i32* %8, align 4
  %40 = load i32*, i32** %3, align 8
  %41 = load i32, i32* %6, align 4
  %42 = add nsw i32 %41, 1
  %43 = sext i32 %42 to i64
  %44 = getelementptr inbounds i32, i32* %40, i64 %43
  %45 = load i32, i32* %44, align 4
  %46 = load i32*, i32** %3, align 8
  %47 = load i32, i32* %6, align 4
  %48 = sext i32 %47 to i64
  %49 = getelementptr inbounds i32, i32* %46, i64 %48
  store i32 %45, i32* %49, align 4
  %50 = load i32, i32* %8, align 4
  %51 = load i32*, i32** %3, align 8
  %52 = load i32, i32* %6, align 4
  %53 = add nsw i32 %52, 1
  %54 = sext i32 %53 to i64
  %55 = getelementptr inbounds i32, i32* %51, i64 %54
  store i32 %50, i32* %55, align 4
  store i32 1, i32* %7, align 4
  br label %56

56:                                               ; preds = %34, %21
  br label %57

57:                                               ; preds = %56
  %58 = load i32, i32* %6, align 4
  %59 = add nsw i32 %58, 1
  store i32 %59, i32* %6, align 4
  br label %14, !llvm.loop !6

60:                                               ; preds = %14
  %61 = load i32, i32* %7, align 4
  %62 = icmp eq i32 %61, 0
  br i1 %62, label %63, label %64

63:                                               ; preds = %60
  br label %68

64:                                               ; preds = %60
  br label %65

65:                                               ; preds = %64
  %66 = load i32, i32* %5, align 4
  %67 = add nsw i32 %66, 1
  store i32 %67, i32* %5, align 4
  br label %9, !llvm.loop !7

68:                                               ; preds = %63, %9
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i8, align 1
  %3 = alloca i32, align 4
  %4 = alloca [100 x i32], align 16
  %5 = alloca [7 x i8], align 1
  %6 = alloca i32, align 4
  %7 = alloca i8, align 1
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i8, align 1
  %14 = alloca i8, align 1
  %15 = alloca i8, align 1
  %16 = alloca i32, align 4
  %17 = alloca i32, align 4
  %18 = alloca i32, align 4
  %19 = alloca i8, align 1
  %20 = alloca i32, align 4
  %21 = alloca i32, align 4
  %22 = alloca i32, align 4
  %23 = alloca i32, align 4
  %24 = alloca [30 x i32], align 16
  %25 = alloca i32, align 4
  %26 = alloca i32, align 4
  %27 = alloca i32, align 4
  %28 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i8 108, i8* %2, align 1
  store i32 20, i32* %3, align 4
  %29 = bitcast [7 x i8]* %5 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %29, i8* align 1 getelementptr inbounds ([7 x i8], [7 x i8]* @__const.main.bbbbb, i32 0, i32 0), i64 7, i1 false)
  %30 = call i32 (...) @getint()
  store i32 %30, i32* %6, align 4
  %31 = call i32 (...) @getchar()
  %32 = trunc i32 %31 to i8
  store i8 %32, i8* %7, align 1
  store i32 0, i32* %9, align 4
  %33 = load i32, i32* %9, align 4
  store i32 %33, i32* %8, align 4
  %34 = load i32, i32* %8, align 4
  %35 = icmp ne i32 %34, 0
  %36 = xor i1 %35, true
  %37 = zext i1 %36 to i32
  store i32 %37, i32* %8, align 4
  store i32 0, i32* %10, align 4
  store i32 0, i32* %11, align 4
  store i32 0, i32* %12, align 4
  store i8 97, i8* %13, align 1
  store i8 97, i8* %14, align 1
  store i8 97, i8* %15, align 1
  %38 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.1, i64 0, i64 0))
  %39 = load i32, i32* %6, align 4
  %40 = load i8, i8* %7, align 1
  %41 = sext i8 %40 to i32
  %42 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.2, i64 0, i64 0), i32 %39, i32 %41)
  store i32 0, i32* %17, align 4
  store i32 0, i32* %16, align 4
  br label %43

43:                                               ; preds = %54, %0
  %44 = load i32, i32* %16, align 4
  %45 = icmp slt i32 %44, 100
  br i1 %45, label %46, label %57

46:                                               ; preds = %43
  %47 = load i32, i32* %16, align 4
  %48 = call i32 @isPrime(i32 %47)
  %49 = icmp ne i32 %48, 0
  br i1 %49, label %50, label %53

50:                                               ; preds = %46
  %51 = load i32, i32* %17, align 4
  %52 = add nsw i32 %51, 1
  store i32 %52, i32* %17, align 4
  br label %53

53:                                               ; preds = %50, %46
  br label %54

54:                                               ; preds = %53
  %55 = load i32, i32* %16, align 4
  %56 = add nsw i32 %55, 1
  store i32 %56, i32* %16, align 4
  br label %43, !llvm.loop !8

57:                                               ; preds = %43
  store i32 0, i32* %16, align 4
  br label %58

58:                                               ; preds = %69, %57
  %59 = load i32, i32* %16, align 4
  %60 = icmp slt i32 %59, 100
  br i1 %60, label %61, label %72

61:                                               ; preds = %58
  %62 = load i32, i32* %16, align 4
  %63 = call i32 @isPrime(i32 %62)
  %64 = icmp ne i32 %63, 0
  br i1 %64, label %65, label %68

65:                                               ; preds = %61
  %66 = load i32, i32* %17, align 4
  %67 = add nsw i32 %66, 1
  store i32 %67, i32* %17, align 4
  br label %68

68:                                               ; preds = %65, %61
  br label %69

69:                                               ; preds = %68
  %70 = load i32, i32* %16, align 4
  %71 = add nsw i32 %70, 1
  store i32 %71, i32* %16, align 4
  br label %58, !llvm.loop !9

72:                                               ; preds = %58
  store i32 0, i32* %16, align 4
  br label %73

73:                                               ; preds = %85, %72
  store i32 100, i32* %18, align 4
  %74 = load i32, i32* %16, align 4
  %75 = icmp sge i32 %74, 100
  br i1 %75, label %76, label %77

76:                                               ; preds = %73
  br label %88

77:                                               ; preds = %73
  %78 = load i32, i32* %16, align 4
  %79 = call i32 @isPrime(i32 %78)
  %80 = icmp ne i32 %79, 0
  br i1 %80, label %81, label %84

81:                                               ; preds = %77
  %82 = load i32, i32* %17, align 4
  %83 = add nsw i32 %82, 1
  store i32 %83, i32* %17, align 4
  br label %84

84:                                               ; preds = %81, %77
  br label %85

85:                                               ; preds = %84
  %86 = load i32, i32* %16, align 4
  %87 = add nsw i32 %86, 1
  store i32 %87, i32* %16, align 4
  br label %73

88:                                               ; preds = %76
  store i32 0, i32* %16, align 4
  br label %89

89:                                               ; preds = %101, %88
  %90 = load i32, i32* %16, align 4
  %91 = icmp sge i32 %90, 100
  br i1 %91, label %92, label %93

92:                                               ; preds = %89
  br label %104

93:                                               ; preds = %89
  %94 = load i32, i32* %16, align 4
  %95 = call i32 @isPrime(i32 %94)
  %96 = icmp ne i32 %95, 0
  br i1 %96, label %97, label %100

97:                                               ; preds = %93
  %98 = load i32, i32* %17, align 4
  %99 = add nsw i32 %98, 1
  store i32 %99, i32* %17, align 4
  br label %100

100:                                              ; preds = %97, %93
  br label %101

101:                                              ; preds = %100
  %102 = load i32, i32* %16, align 4
  %103 = add nsw i32 %102, 1
  store i32 %103, i32* %16, align 4
  br label %89

104:                                              ; preds = %92
  store i32 0, i32* %16, align 4
  br label %105

105:                                              ; preds = %115, %104
  %106 = load i32, i32* %16, align 4
  %107 = icmp slt i32 %106, 100
  br i1 %107, label %108, label %118

108:                                              ; preds = %105
  %109 = load i32, i32* %16, align 4
  %110 = call i32 @isPrime(i32 %109)
  %111 = icmp ne i32 %110, 0
  br i1 %111, label %112, label %115

112:                                              ; preds = %108
  %113 = load i32, i32* %17, align 4
  %114 = add nsw i32 %113, 1
  store i32 %114, i32* %17, align 4
  br label %115

115:                                              ; preds = %112, %108
  %116 = load i32, i32* %16, align 4
  %117 = add nsw i32 %116, 1
  store i32 %117, i32* %16, align 4
  br label %105, !llvm.loop !10

118:                                              ; preds = %105
  store i32 0, i32* %16, align 4
  br label %119

119:                                              ; preds = %130, %118
  %120 = load i32, i32* %16, align 4
  %121 = icmp sge i32 %120, 100
  br i1 %121, label %122, label %123

122:                                              ; preds = %119
  br label %133

123:                                              ; preds = %119
  %124 = load i32, i32* %16, align 4
  %125 = call i32 @isPrime(i32 %124)
  %126 = icmp ne i32 %125, 0
  br i1 %126, label %127, label %130

127:                                              ; preds = %123
  %128 = load i32, i32* %17, align 4
  %129 = add nsw i32 %128, 1
  store i32 %129, i32* %17, align 4
  br label %130

130:                                              ; preds = %127, %123
  %131 = load i32, i32* %16, align 4
  %132 = add nsw i32 %131, 1
  store i32 %132, i32* %16, align 4
  br label %119

133:                                              ; preds = %122
  store i32 0, i32* %16, align 4
  br label %134

134:                                              ; preds = %145, %133
  %135 = load i32, i32* %16, align 4
  %136 = icmp sge i32 %135, 100
  br i1 %136, label %137, label %138

137:                                              ; preds = %134
  br label %148

138:                                              ; preds = %134
  %139 = load i32, i32* %16, align 4
  %140 = call i32 @isPrime(i32 %139)
  %141 = icmp ne i32 %140, 0
  br i1 %141, label %142, label %145

142:                                              ; preds = %138
  %143 = load i32, i32* %17, align 4
  %144 = add nsw i32 %143, 1
  store i32 %144, i32* %17, align 4
  br label %145

145:                                              ; preds = %142, %138
  %146 = load i32, i32* %16, align 4
  %147 = add nsw i32 %146, 1
  store i32 %147, i32* %16, align 4
  br label %134

148:                                              ; preds = %137
  store i32 0, i32* %16, align 4
  br label %149

149:                                              ; preds = %159, %148
  %150 = load i32, i32* %16, align 4
  %151 = icmp slt i32 %150, 100
  br i1 %151, label %152, label %162

152:                                              ; preds = %149
  %153 = load i32, i32* %16, align 4
  %154 = call i32 @isPrime(i32 %153)
  %155 = icmp ne i32 %154, 0
  br i1 %155, label %156, label %159

156:                                              ; preds = %152
  %157 = load i32, i32* %17, align 4
  %158 = add nsw i32 %157, 1
  store i32 %158, i32* %17, align 4
  br label %159

159:                                              ; preds = %156, %152
  %160 = load i32, i32* %16, align 4
  %161 = add nsw i32 %160, 1
  store i32 %161, i32* %16, align 4
  br label %149, !llvm.loop !11

162:                                              ; preds = %149
  store i32 0, i32* %16, align 4
  store i32 0, i32* %16, align 4
  br label %163

163:                                              ; preds = %171, %162
  %164 = load i32, i32* %16, align 4
  %165 = icmp slt i32 %164, 100
  br i1 %165, label %166, label %174

166:                                              ; preds = %163
  %167 = load i32, i32* %16, align 4
  %168 = icmp sgt i32 %167, 50
  br i1 %168, label %169, label %170

169:                                              ; preds = %166
  br label %171

170:                                              ; preds = %166
  br label %171

171:                                              ; preds = %170, %169
  %172 = load i32, i32* %16, align 4
  %173 = add nsw i32 %172, 1
  store i32 %173, i32* %16, align 4
  br label %163, !llvm.loop !12

174:                                              ; preds = %163
  store i32 0, i32* %16, align 4
  br label %175

175:                                              ; preds = %185, %174
  %176 = load i32, i32* %16, align 4
  %177 = icmp slt i32 %176, 100
  br i1 %177, label %178, label %188

178:                                              ; preds = %175
  %179 = load i32, i32* %16, align 4
  %180 = icmp sgt i32 %179, 50
  br i1 %180, label %181, label %184

181:                                              ; preds = %178
  %182 = load i32, i32* %17, align 4
  %183 = add nsw i32 %182, 1
  store i32 %183, i32* %17, align 4
  br label %188

184:                                              ; preds = %178
  br label %185

185:                                              ; preds = %184
  %186 = load i32, i32* %16, align 4
  %187 = add nsw i32 %186, 1
  store i32 %187, i32* %16, align 4
  br label %175, !llvm.loop !13

188:                                              ; preds = %181, %175
  %189 = load i32, i32* %17, align 4
  %190 = mul nsw i32 %189, 10
  store i32 %190, i32* %17, align 4
  %191 = load i32, i32* %17, align 4
  %192 = sdiv i32 %191, 2
  store i32 %192, i32* %17, align 4
  %193 = load i32, i32* %17, align 4
  %194 = srem i32 %193, 3
  store i32 %194, i32* %17, align 4
  %195 = load i32, i32* %17, align 4
  %196 = add nsw i32 %195, 156
  %197 = sub nsw i32 %196, 99
  store i32 %197, i32* %17, align 4
  %198 = load i32, i32* %17, align 4
  %199 = icmp sgt i32 %198, 0
  br i1 %199, label %200, label %203

200:                                              ; preds = %188
  %201 = load i32, i32* %17, align 4
  %202 = sub nsw i32 0, %201
  store i32 %202, i32* %17, align 4
  br label %205

203:                                              ; preds = %188
  %204 = load i32, i32* %17, align 4
  store i32 %204, i32* %17, align 4
  br label %205

205:                                              ; preds = %203, %200
  %206 = load i32, i32* %17, align 4
  %207 = icmp slt i32 %206, 0
  br i1 %207, label %208, label %211

208:                                              ; preds = %205
  %209 = load i32, i32* %17, align 4
  %210 = sub nsw i32 0, %209
  store i32 %210, i32* %17, align 4
  br label %213

211:                                              ; preds = %205
  %212 = load i32, i32* %17, align 4
  store i32 %212, i32* %17, align 4
  br label %213

213:                                              ; preds = %211, %208
  %214 = load i32, i32* %17, align 4
  %215 = icmp ne i32 %214, 0
  br i1 %215, label %216, label %218

216:                                              ; preds = %213
  %217 = load i32, i32* %17, align 4
  store i32 %217, i32* %17, align 4
  br label %218

218:                                              ; preds = %216, %213
  store i8 120, i8* %19, align 1
  %219 = load i8, i8* %19, align 1
  %220 = sext i8 %219 to i32
  %221 = icmp sge i32 %220, 97
  br i1 %221, label %222, label %227

222:                                              ; preds = %218
  %223 = load i8, i8* %19, align 1
  %224 = sext i8 %223 to i32
  %225 = add nsw i32 %224, 1
  %226 = trunc i32 %225 to i8
  store i8 %226, i8* %19, align 1
  br label %227

227:                                              ; preds = %222, %218
  %228 = load i8, i8* %19, align 1
  %229 = sext i8 %228 to i32
  %230 = icmp sle i32 %229, 122
  br i1 %230, label %231, label %236

231:                                              ; preds = %227
  %232 = load i8, i8* %19, align 1
  %233 = sext i8 %232 to i32
  %234 = add nsw i32 %233, 1
  %235 = trunc i32 %234 to i8
  store i8 %235, i8* %19, align 1
  br label %236

236:                                              ; preds = %231, %227
  %237 = load i8, i8* %19, align 1
  %238 = sext i8 %237 to i32
  %239 = icmp ne i32 %238, 122
  br i1 %239, label %240, label %245

240:                                              ; preds = %236
  %241 = load i8, i8* %19, align 1
  %242 = sext i8 %241 to i32
  %243 = sub nsw i32 %242, 1
  %244 = trunc i32 %243 to i8
  store i8 %244, i8* %19, align 1
  br label %245

245:                                              ; preds = %240, %236
  %246 = load i8, i8* %19, align 1
  %247 = sext i8 %246 to i32
  %248 = icmp eq i32 %247, 122
  br i1 %248, label %249, label %254

249:                                              ; preds = %245
  %250 = load i8, i8* %19, align 1
  %251 = sext i8 %250 to i32
  %252 = sub nsw i32 %251, 10
  %253 = trunc i32 %252 to i8
  store i8 %253, i8* %19, align 1
  br label %254

254:                                              ; preds = %249, %245
  store i32 10, i32* %20, align 4
  %255 = load i32, i32* %20, align 4
  %256 = add nsw i32 %255, 1
  store i32 %256, i32* %20, align 4
  %257 = load i32, i32* %20, align 4
  %258 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 %257)
  %259 = load i32, i32* %17, align 4
  %260 = icmp ne i32 %259, 0
  br i1 %260, label %261, label %264

261:                                              ; preds = %254
  %262 = load i32, i32* %17, align 4
  %263 = call i32 @getSum(i32 1, i32 2, i32 %262)
  store i32 %263, i32* %17, align 4
  br label %264

264:                                              ; preds = %261, %254
  %265 = load i32, i32* %17, align 4
  store i32 %265, i32* %21, align 4
  store i32 0, i32* %22, align 4
  %266 = load i32, i32* %17, align 4
  %267 = call signext i8 @getAChar()
  %268 = sext i8 %267 to i32
  %269 = call signext i8 @getAChar1()
  %270 = sext i8 %269 to i32
  %271 = call i32 @getSum(i32 1, i32 2, i32 20)
  %272 = load i8, i8* %19, align 1
  %273 = sext i8 %272 to i32
  %274 = load i32, i32* %17, align 4
  %275 = load i32, i32* %21, align 4
  %276 = load i32, i32* %22, align 4
  %277 = call i32 @getSum1(i32 1, i32 2, i32 3)
  %278 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.3, i64 0, i64 0), i32 %266, i32 108, i32 20, i32 %268, i32 %270, i32 %271, i32 %273, i32 %274, i32 %275, i32 %276, i32 %277)
  call void @sumOne2Ten()
  call void @sumOne2Ten1()
  %279 = load i32, i32* %17, align 4
  store i32 %279, i32* %23, align 4
  %280 = load i32, i32* %23, align 4
  %281 = icmp sgt i32 %280, 0
  br i1 %281, label %282, label %308

282:                                              ; preds = %264
  %283 = load i32, i32* %23, align 4
  %284 = icmp slt i32 %283, 100
  br i1 %284, label %285, label %308

285:                                              ; preds = %282
  %286 = load i32, i32* %23, align 4
  %287 = srem i32 %286, 2
  %288 = icmp eq i32 %287, 0
  br i1 %288, label %293, label %289

289:                                              ; preds = %285
  %290 = load i32, i32* %23, align 4
  %291 = srem i32 %290, 3
  %292 = icmp eq i32 %291, 0
  br i1 %292, label %293, label %296

293:                                              ; preds = %289, %285
  %294 = load i32, i32* %17, align 4
  %295 = add nsw i32 %294, 1
  store i32 %295, i32* %17, align 4
  br label %296

296:                                              ; preds = %293, %289
  %297 = load i32, i32* %23, align 4
  %298 = srem i32 %297, 5
  %299 = icmp eq i32 %298, 0
  br i1 %299, label %304, label %300

300:                                              ; preds = %296
  %301 = load i32, i32* %23, align 4
  %302 = call i32 @isPrime(i32 %301)
  %303 = icmp ne i32 %302, 0
  br i1 %303, label %304, label %307

304:                                              ; preds = %300, %296
  %305 = load i32, i32* %17, align 4
  %306 = add nsw i32 %305, 1
  store i32 %306, i32* %17, align 4
  br label %307

307:                                              ; preds = %304, %300
  br label %308

308:                                              ; preds = %307, %282, %264
  %309 = load i32, i32* %23, align 4
  %310 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 %309)
  %311 = bitcast [30 x i32]* %24 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 16 %311, i8* align 16 bitcast (<{ [19 x i32], [11 x i32] }>* @__const.main.arr to i8*), i64 120, i1 false)
  store i32 0, i32* %25, align 4
  %312 = load i32, i32* %25, align 4
  %313 = add nsw i32 %312, 1
  store i32 %313, i32* %25, align 4
  store i32 %313, i32* %25, align 4
  store i32 20, i32* %26, align 4
  store i32 0, i32* %16, align 4
  br label %314

314:                                              ; preds = %364, %308
  %315 = load i32, i32* %16, align 4
  %316 = load i32, i32* %26, align 4
  %317 = icmp slt i32 %315, %316
  br i1 %317, label %318, label %367

318:                                              ; preds = %314
  store i32 0, i32* %27, align 4
  store i32 0, i32* %8, align 4
  br label %319

319:                                              ; preds = %356, %318
  %320 = load i32, i32* %8, align 4
  %321 = load i32, i32* %26, align 4
  %322 = load i32, i32* %16, align 4
  %323 = sub nsw i32 %321, %322
  %324 = sub nsw i32 %323, 1
  %325 = icmp slt i32 %320, %324
  br i1 %325, label %326, label %359

326:                                              ; preds = %319
  %327 = load i32, i32* %8, align 4
  %328 = sext i32 %327 to i64
  %329 = getelementptr inbounds [30 x i32], [30 x i32]* %24, i64 0, i64 %328
  %330 = load i32, i32* %329, align 4
  %331 = load i32, i32* %8, align 4
  %332 = add nsw i32 %331, 1
  %333 = sext i32 %332 to i64
  %334 = getelementptr inbounds [30 x i32], [30 x i32]* %24, i64 0, i64 %333
  %335 = load i32, i32* %334, align 4
  %336 = icmp sgt i32 %330, %335
  br i1 %336, label %337, label %355

337:                                              ; preds = %326
  %338 = load i32, i32* %8, align 4
  %339 = sext i32 %338 to i64
  %340 = getelementptr inbounds [30 x i32], [30 x i32]* %24, i64 0, i64 %339
  %341 = load i32, i32* %340, align 4
  store i32 %341, i32* %28, align 4
  %342 = load i32, i32* %8, align 4
  %343 = add nsw i32 %342, 1
  %344 = sext i32 %343 to i64
  %345 = getelementptr inbounds [30 x i32], [30 x i32]* %24, i64 0, i64 %344
  %346 = load i32, i32* %345, align 4
  %347 = load i32, i32* %8, align 4
  %348 = sext i32 %347 to i64
  %349 = getelementptr inbounds [30 x i32], [30 x i32]* %24, i64 0, i64 %348
  store i32 %346, i32* %349, align 4
  %350 = load i32, i32* %28, align 4
  %351 = load i32, i32* %8, align 4
  %352 = add nsw i32 %351, 1
  %353 = sext i32 %352 to i64
  %354 = getelementptr inbounds [30 x i32], [30 x i32]* %24, i64 0, i64 %353
  store i32 %350, i32* %354, align 4
  store i32 1, i32* %27, align 4
  br label %355

355:                                              ; preds = %337, %326
  br label %356

356:                                              ; preds = %355
  %357 = load i32, i32* %8, align 4
  %358 = add nsw i32 %357, 1
  store i32 %358, i32* %8, align 4
  br label %319, !llvm.loop !14

359:                                              ; preds = %319
  %360 = load i32, i32* %27, align 4
  %361 = icmp eq i32 %360, 0
  br i1 %361, label %362, label %363

362:                                              ; preds = %359
  br label %367

363:                                              ; preds = %359
  br label %364

364:                                              ; preds = %363
  %365 = load i32, i32* %16, align 4
  %366 = add nsw i32 %365, 1
  store i32 %366, i32* %16, align 4
  br label %314, !llvm.loop !15

367:                                              ; preds = %362, %314
  %368 = getelementptr inbounds [30 x i32], [30 x i32]* %24, i64 0, i64 0
  %369 = load i32, i32* %368, align 16
  %370 = getelementptr inbounds [30 x i32], [30 x i32]* %24, i64 0, i64 1
  %371 = load i32, i32* %370, align 4
  %372 = getelementptr inbounds [30 x i32], [30 x i32]* %24, i64 0, i64 2
  %373 = load i32, i32* %372, align 8
  %374 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.4, i64 0, i64 0), i32 %369, i32 %371, i32 %373)
  ret i32 0
}

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* noalias nocapture writeonly, i8* noalias nocapture readonly, i64, i1 immarg) #2

declare dso_local i32 @getint(...) #1

declare dso_local i32 @getchar(...) #1

attributes #0 = { noinline nounwind optnone uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { argmemonly nofree nosync nounwind willreturn }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"Ubuntu clang version 12.0.1-19ubuntu3"}
!2 = distinct !{!2, !3}
!3 = !{!"llvm.loop.mustprogress"}
!4 = distinct !{!4, !3}
!5 = distinct !{!5, !3}
!6 = distinct !{!6, !3}
!7 = distinct !{!7, !3}
!8 = distinct !{!8, !3}
!9 = distinct !{!9, !3}
!10 = distinct !{!10, !3}
!11 = distinct !{!11, !3}
!12 = distinct !{!12, !3}
!13 = distinct !{!13, !3}
!14 = distinct !{!14, !3}
!15 = distinct !{!15, !3}
