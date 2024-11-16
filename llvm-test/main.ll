; ModuleID = 'main.c'
source_filename = "main.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@globalConstInt1 = dso_local constant i32 1, align 4
@globalConstChar1 = dso_local constant i8 97, align 1
@globalConstInt2 = dso_local constant i32 2, align 4
@globalConstInt3 = dso_local constant i32 3, align 4
@globalConstChar2 = dso_local constant i8 98, align 1
@globalConstChar3 = dso_local constant i8 99, align 1
@globalVarInt1 = dso_local global i32 4, align 4
@globalVarChar1 = dso_local global i8 100, align 1
@globalVarInt2 = dso_local global i32 5, align 4
@globalVarInt3 = dso_local global i32 6, align 4
@globalVarChar2 = dso_local global i8 101, align 1
@globalVarChar3 = dso_local global i8 102, align 1
@.str = private unnamed_addr constant [10 x i8] c"22371443\0A\00", align 1
@.str.1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c"for\0A\00", align 1
@.str.3 = private unnamed_addr constant [21 x i8] c"lack 1, situation 1\0A\00", align 1
@.str.4 = private unnamed_addr constant [21 x i8] c"lack 1, situation 2\0A\00", align 1
@.str.5 = private unnamed_addr constant [28 x i8] c"lack 1, situation 3 and %c\0A\00", align 1
@.str.6 = private unnamed_addr constant [21 x i8] c"lack 2, situation 1\0A\00", align 1
@.str.7 = private unnamed_addr constant [21 x i8] c"lack 2, situation 2\0A\00", align 1
@.str.8 = private unnamed_addr constant [28 x i8] c"lack 2, situation 3 and %c\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @func1() #0 {
  %1 = alloca i32, align 4
  store i32 1, i32* %1, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @func2() #0 {
  ret i32 1
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local signext i8 @func3() #0 {
  ret i8 97
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @func4(i32 %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  store i32 11, i32* %2, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @func5(i32 %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32, i32* %2, align 4
  ret i32 %3
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local signext i8 @func6(i32 %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32, i32* %2, align 4
  %4 = add nsw i32 %3, 1
  store i32 %4, i32* %2, align 4
  ret i8 97
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @func7(i32 %0, i8 signext %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i8, align 1
  store i32 %0, i32* %3, align 4
  store i8 %1, i8* %4, align 1
  %5 = load i32, i32* %3, align 4
  %6 = add nsw i32 %5, 1
  store i32 %6, i32* %3, align 4
  store i8 97, i8* %4, align 1
  ret i32 0
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i8, align 1
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i8, align 1
  %7 = alloca i8, align 1
  %8 = alloca i32, align 4
  %9 = alloca i8, align 1
  store i32 0, i32* %1, align 4
  %10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i64 0, i64 0))
  store i32 1, i32* %2, align 4
  store i8 97, i8* %3, align 1
  %11 = call i32 (...) @getint()
  store i32 %11, i32* %4, align 4
  %12 = call i32 @getchar()
  %13 = trunc i32 %12 to i8
  store i8 %13, i8* %6, align 1
  store i32 2, i32* %5, align 4
  store i8 98, i8* %7, align 1
  %14 = load i32, i32* %2, align 4
  %15 = icmp eq i32 %14, 1
  br i1 %15, label %16, label %19

16:                                               ; preds = %0
  %17 = load i32, i32* %2, align 4
  %18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i64 0, i64 0), i32 %17)
  br label %19

19:                                               ; preds = %16, %0
  %20 = load i32, i32* %4, align 4
  %21 = icmp ne i32 %20, 2
  br i1 %21, label %22, label %25

22:                                               ; preds = %19
  %23 = load i32, i32* %4, align 4
  %24 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i64 0, i64 0), i32 %23)
  br label %28

25:                                               ; preds = %19
  %26 = load i32, i32* %4, align 4
  %27 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i64 0, i64 0), i32 %26)
  br label %28

28:                                               ; preds = %25, %22
  store i32 1, i32* %8, align 4
  store i32 1, i32* %8, align 4
  br label %29

29:                                               ; preds = %34, %28
  %30 = load i32, i32* %8, align 4
  %31 = icmp slt i32 %30, 2
  br i1 %31, label %32, label %37

32:                                               ; preds = %29
  %33 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i64 0, i64 0))
  br label %34

34:                                               ; preds = %32
  %35 = load i32, i32* %8, align 4
  %36 = add nsw i32 %35, 1
  store i32 %36, i32* %8, align 4
  br label %29, !llvm.loop !2

37:                                               ; preds = %29
  store i32 1, i32* %8, align 4
  br label %38

38:                                               ; preds = %37
  %39 = load i32, i32* %8, align 4
  %40 = icmp slt i32 %39, 2
  br i1 %40, label %41, label %43

41:                                               ; preds = %38
  call void @func1()
  %42 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.3, i64 0, i64 0))
  br label %43

43:                                               ; preds = %41, %38
  br label %44

44:                                               ; preds = %53, %43
  %45 = load i32, i32* %8, align 4
  %46 = icmp slt i32 %45, 2
  br i1 %46, label %47, label %56

47:                                               ; preds = %44
  %48 = call i32 @func2()
  %49 = icmp eq i32 %48, 1
  br i1 %49, label %50, label %52

50:                                               ; preds = %47
  %51 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.4, i64 0, i64 0))
  br label %56

52:                                               ; preds = %47
  br label %53

53:                                               ; preds = %52
  %54 = load i32, i32* %8, align 4
  %55 = add nsw i32 %54, 1
  store i32 %55, i32* %8, align 4
  br label %44, !llvm.loop !4

56:                                               ; preds = %50, %44
  store i32 1, i32* %8, align 4
  br label %57

57:                                               ; preds = %61, %56
  %58 = call signext i8 @func3()
  %59 = sext i8 %58 to i32
  %60 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.5, i64 0, i64 0), i32 %59)
  br label %64

61:                                               ; No predecessors!
  %62 = load i32, i32* %8, align 4
  %63 = add nsw i32 %62, 1
  store i32 %63, i32* %8, align 4
  br label %57

64:                                               ; preds = %57
  store i32 1, i32* %8, align 4
  br label %65

65:                                               ; preds = %64
  call void @func4(i32 1)
  %66 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.6, i64 0, i64 0))
  br label %67

67:                                               ; preds = %65
  br label %68

68:                                               ; preds = %67
  %69 = load i32, i32* %8, align 4
  %70 = icmp slt i32 %69, 2
  br i1 %70, label %71, label %74

71:                                               ; preds = %68
  %72 = call i32 @func5(i32 2)
  %73 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.7, i64 0, i64 0))
  br label %74

74:                                               ; preds = %71, %68
  br label %75

75:                                               ; preds = %80, %74
  %76 = call signext i8 @func6(i32 3)
  store i8 %76, i8* %9, align 1
  %77 = load i8, i8* %9, align 1
  %78 = sext i8 %77 to i32
  %79 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.8, i64 0, i64 0), i32 %78)
  br label %83

80:                                               ; No predecessors!
  %81 = load i32, i32* %8, align 4
  %82 = sub nsw i32 %81, 1
  store i32 %82, i32* %8, align 4
  br label %75

83:                                               ; preds = %75
  %84 = call i32 @func7(i32 1, i8 signext 97)
  ret i32 0
}

declare dso_local i32 @printf(i8*, ...) #1

declare dso_local i32 @getint(...) #1

declare dso_local i32 @getchar() #1

attributes #0 = { noinline nounwind optnone uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"Ubuntu clang version 12.0.1-19ubuntu3"}
!2 = distinct !{!2, !3}
!3 = !{!"llvm.loop.mustprogress"}
!4 = distinct !{!4, !3}
