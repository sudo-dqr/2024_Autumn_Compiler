declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@dqr0 = private unnamed_addr constant [9 x i8] c"21371295\00"

define dso_local i32 @main() {
	%1 = getelementptr inbounds [9 x i8], [9 x i8]* @dqr0, i32 0, i32 0
	call void @putstr(i8* %1)
	ret i32 0
}





