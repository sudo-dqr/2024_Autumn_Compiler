declare i32 @getint(...) 
declare i32 @getchar(...) 
declare void @putint(i32)
declare void @putstr(i8* )
declare void @putchar(i32)



@g0 = dso_local global [10 x i32] zeroinitializer
@g1 = dso_local global [2 x i32] [i32 1, i32 2]
@g2 = dso_local global [10 x i8] zeroinitializer
@g3 = dso_local global [10 x i8] [i8 104, i8 101, i8 108, i8 108, i8 111, i8 0, i8 0, i8 0, i8 0, i8 0]

define dso_local i32 @f_foo2(i32* %a0, i32 %a1, i8* %a2, i8 %a3) {
b0:
	%v0 = alloca i32
	store i32 %a1, i32* %v0
	%v2 = alloca i8
	store i8 %a3, i8* %v2
	ret i32 0
}

define dso_local i32 @f_foo(i32* %a4, i32 %a5, i8* %a6, i8 %a7) {
b1:
	%v0 = alloca i32
	store i32 %a5, i32* %v0
	%v2 = alloca i8
	store i8 %a7, i8* %v2
	%v4 = getelementptr inbounds i32, i32* %a4, i32 0
	%v5 = load i32, i32* %v0
	%v6 = getelementptr inbounds i8, i8* %a6, i32 0
	%v7 = load i8, i8* %v2
	%v8 = zext i8 %v7 to i32
	%v9 = trunc i32 %v8 to i8
	%v10 = call i32 @f_foo2(i32* %v4, i32 %v5, i8* %v6, i8 %v9)
	ret i32 0
}

define dso_local i32 @main() {
b2:
	%v0 = alloca [10 x i32]
	%v1 = alloca [10 x i8]
	%v2 = alloca [2 x i32]
	%v3 = getelementptr inbounds [2 x i32], [2 x i32]* %v2, i32 0, i32 0
	store i32 1, i32* %v3
	%v5 = getelementptr inbounds [2 x i32], [2 x i32]* %v2, i32 0, i32 1
	store i32 2, i32* %v5
	%v7 = alloca [3 x i8]
	%v8 = getelementptr inbounds [3 x i8], [3 x i8]* %v7, i32 0, i32 0
	store i8 49, i8* %v8
	%v10 = getelementptr inbounds [3 x i8], [3 x i8]* %v7, i32 0, i32 1
	store i8 0, i8* %v10
	%v12 = getelementptr inbounds [3 x i8], [3 x i8]* %v7, i32 0, i32 2
	store i8 0, i8* %v12
	%v14 = getelementptr inbounds [10 x i32], [10 x i32]* @g0, i32 0, i32 0
	%v15 = getelementptr inbounds [10 x i32], [10 x i32]* @g0, i32 0, i32 1
	%v16 = load i32, i32* %v15
	%v17 = getelementptr inbounds [10 x i8], [10 x i8]* @g2, i32 0, i32 0
	%v18 = getelementptr inbounds [10 x i8], [10 x i8]* @g2, i32 0, i32 1
	%v19 = load i8, i8* %v18
	%v20 = zext i8 %v19 to i32
	%v21 = trunc i32 %v20 to i8
	%v22 = call i32 @f_foo(i32* %v14, i32 %v16, i8* %v17, i8 %v21)
	%v23 = getelementptr inbounds [2 x i32], [2 x i32]* @g1, i32 0, i32 0
	%v24 = getelementptr inbounds [2 x i32], [2 x i32]* @g1, i32 0, i32 1
	%v25 = load i32, i32* %v24
	%v26 = getelementptr inbounds [10 x i8], [10 x i8]* @g3, i32 0, i32 0
	%v27 = getelementptr inbounds [10 x i8], [10 x i8]* @g3, i32 0, i32 1
	%v28 = load i8, i8* %v27
	%v29 = zext i8 %v28 to i32
	%v30 = trunc i32 %v29 to i8
	%v31 = call i32 @f_foo(i32* %v23, i32 %v25, i8* %v26, i8 %v30)
	%v32 = getelementptr inbounds [10 x i32], [10 x i32]* %v0, i32 0, i32 0
	%v33 = getelementptr inbounds [10 x i32], [10 x i32]* %v0, i32 0, i32 1
	%v34 = load i32, i32* %v33
	%v35 = getelementptr inbounds [10 x i8], [10 x i8]* %v1, i32 0, i32 0
	%v36 = getelementptr inbounds [10 x i8], [10 x i8]* %v1, i32 0, i32 1
	%v37 = load i8, i8* %v36
	%v38 = zext i8 %v37 to i32
	%v39 = trunc i32 %v38 to i8
	%v40 = call i32 @f_foo(i32* %v32, i32 %v34, i8* %v35, i8 %v39)
	%v41 = getelementptr inbounds [2 x i32], [2 x i32]* %v2, i32 0, i32 0
	%v42 = getelementptr inbounds [2 x i32], [2 x i32]* %v2, i32 0, i32 1
	%v43 = load i32, i32* %v42
	%v44 = getelementptr inbounds [3 x i8], [3 x i8]* %v7, i32 0, i32 0
	%v45 = getelementptr inbounds [3 x i8], [3 x i8]* %v7, i32 0, i32 1
	%v46 = load i8, i8* %v45
	%v47 = zext i8 %v46 to i32
	%v48 = trunc i32 %v47 to i8
	%v49 = call i32 @f_foo(i32* %v41, i32 %v43, i8* %v44, i8 %v48)
	ret i32 0
}