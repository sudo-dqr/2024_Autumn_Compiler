declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@c1 = dso_local global [4 x i8] c"\0A\0A\0A\00"
@c2 = dso_local global [5 x i8] c"\0A\0A\00\00\00"

define dso_local i32 @main() {
0:
	ret i32 0
}

