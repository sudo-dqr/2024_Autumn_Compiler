declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@arr = dso_local global [3 x i32] [i32 1, i32 2, i32 3]
@s = dso_local global [5 x i8] c"abcd\00"
@str = dso_local global [5 x i8] c"abcd\00"
@var1 = dso_local global i32 5
@var2 = dso_local global i32 2
@var3 = dso_local global i32 10
@var4 = dso_local global i8 7
@var5 = dso_local global i8 8
@dqr0 = private unnamed_addr constant [9 x i8] c"22371491\00"
@dqr1 = private unnamed_addr constant [5 x i8] c"pass\00"
@dqr2 = private unnamed_addr constant [7 x i8] c"failed\00"

define dso_local i32 @f3(i32* %0, i32* %1, i32 %2, i32 %3) {
4:
	%5 = alloca i32*
	%6 = alloca i32*
	%7 = alloca i32
	%8 = alloca i32
	store i32* %0, i32** %5
	store i32* %1, i32** %6
	store i32 %2, i32* %7
	store i32 %3, i32* %8
	%9 = alloca i32
	store i32 0, i32* %9
	br label %10
10:
	%11 = load i32, i32* %9
	%12 = icmp eq i32 %11, 0
	br i1 %12, label %13, label %20
13:
	%14 = load i32, i32* %7
	%15 = load i32, i32* %8
	%16 = add i32 %14, %15
	store i32 %16, i32* %7
	br label %17
17:
	%18 = load i32, i32* %9
	%19 = add i32 %18, 1
	store i32 %19, i32* %9
	br label %10
20:
	%21 = load i32*, i32** %5
	%22 = load i32, i32* %9
	%23 = getelementptr i32, i32* %21, i32 %22
	%24 = load i32, i32* %23
	%25 = load i32*, i32** %6
	%26 = load i32, i32* %9
	%27 = getelementptr i32, i32* %25, i32 %26
	%28 = load i32, i32* %27
	%29 = load i32, i32* %7
	%30 = add i32 %28, %29
	%31 = mul i32 %24, %30
	%32 = load i32, i32* %8
	%33 = sub i32 %31, %32
	ret i32 %33
}

define dso_local i32 @f4(i32 %0, i32 %1) {
2:
	%3 = alloca i32
	%4 = alloca i32
	store i32 %0, i32* %3
	store i32 %1, i32* %4
	%5 = load i32, i32* %3
	%6 = load i32, i32* %4
	%7 = add i32 %5, %6
	ret i32 %7
}

define dso_local i8 @f5(i8 %0, i8 %1) {
2:
	%3 = alloca i8
	%4 = alloca i8
	store i8 %0, i8* %3
	store i8 %1, i8* %4
	%5 = load i8, i8* %3
	%6 = load i8, i8* %4
	%7 = zext i8 %5 to i32
	%8 = zext i8 %6 to i32
	%9 = add i32 %7, %8
	%10 = trunc i32 %9 to i8
	ret i8 %10
}

define dso_local i32 @f7(i32 %0) {
1:
	%2 = alloca i32
	store i32 %0, i32* %2
	%3 = load i32, i32* %2
	ret i32 %3
}

define dso_local i8 @f8(i8 %0) {
1:
	%2 = alloca i8
	store i8 %0, i8* %2
	%3 = load i8, i8* %2
	ret i8 %3
}

define dso_local i32 @f6() {
0:
	ret i32 0
}

define dso_local void @f2(i32 %0) {
1:
	%2 = alloca i32
	store i32 %0, i32* %2
	%3 = load i32, i32* %2
	call void @putint(i32 %3)
	call void @putch(i32 10)
	ret void
}

define dso_local void @f9() {
0:
	ret void
}

define dso_local i32 @main() {
0:
	%1 = getelementptr [9 x i8], [9 x i8]* @dqr0, i32 0, i32 0
	call void @putstr(i8* %1)
	call void @putch(i32 10)
	%2 = alloca i32
	store i32 0, i32* %2
	call void @f9()
	%3 = alloca i32
	store i32 1, i32* %3
	%4 = alloca [3 x i32]
	%5 = alloca [3 x i32]
	%6 = getelementptr [3 x i32], [3 x i32]* %5, i32 0, i32 0
	store i32 1, i32* %6
	%7 = getelementptr [3 x i32], [3 x i32]* %5, i32 0, i32 1
	store i32 2, i32* %7
	%8 = getelementptr [3 x i32], [3 x i32]* %5, i32 0, i32 2
	store i32 3, i32* %8
	%9 = alloca [3 x i32]
	%10 = getelementptr [3 x i32], [3 x i32]* %9, i32 0, i32 0
	store i32 4, i32* %10
	%11 = getelementptr [3 x i32], [3 x i32]* %9, i32 0, i32 1
	store i32 5, i32* %11
	%12 = getelementptr [3 x i32], [3 x i32]* %9, i32 0, i32 2
	store i32 6, i32* %12
	%13 = alloca i32
	%14 = getelementptr [3 x i32], [3 x i32]* %5, i32 0, i32 0
	%15 = getelementptr [3 x i32], [3 x i32]* %9, i32 0, i32 0
	%16 = load i32, i32* %2
	%17 = load i32, i32* %3
	%18 = call i32 @f3(i32* %14, i32* %15, i32 %16, i32 %17)
	store i32 %18, i32* %13
	%19 = alloca i8
	store i8 99, i8* %19
	%20 = call i8 @f8(i8 99)
	store i8 %20, i8* %19
	%21 = load i32, i32* %2
	%22 = add i32 %21, 1
	%23 = add i32 %22, 1
	%24 = add i32 %23, 10
	store i32 %24, i32* %2
	%25 = load i32, i32* %2
	%26 = sub i32 0, %25
	store i32 %26, i32* %2
	%27 = load i32, i32* %2
	%28 = sub i32 0, %27
	%29 = load i32, i32* %2
	%30 = load i32, i32* %2
	%31 = sdiv i32 %30, 2
	store i32 %31, i32* %2
	%32 = load i32, i32* %2
	%33 = srem i32 %32, 2
	store i32 %33, i32* %2
	%34 = load i32, i32* %2
	%35 = icmp eq i32 %34, 0
	%36 = zext i1 %35 to i32
	%37 = icmp ne i32 %36, 0
	br i1 %37, label %38, label %39
38:
	br label %39
39:
	%40 = call i8 @f5(i8 103, i8 102)
	store i8 %40, i8* %19
	%41 = alloca i32
	%42 = load i32, i32* %2
	%43 = add i32 %42, 1
	store i32 %43, i32* %41
	%44 = load i32, i32* %2
	store i32 %44, i32* %41
	%45 = call i32 @getchar()
	%46 = trunc i32 %45 to i8
	store i8 %46, i8* %19
	%47 = alloca i32
	store i32 4, i32* %47
	%48 = alloca i32
	store i32 1, i32* %48
	%49 = alloca i32
	%50 = call i32 @f7(i32 0)
	store i32 %50, i32* %49
	%51 = call i32 @getint()
	store i32 %51, i32* %48
	%52 = load i32, i32* %2
	%53 = load i32, i32* %47
	%54 = call i32 @f4(i32 %52, i32 %53)
	store i32 %54, i32* %48
	store i32 0, i32* %49
	br label %55
55:
	%56 = load i32, i32* %49
	%57 = load i32, i32* %47
	%58 = icmp slt i32 %56, %57
	br i1 %58, label %59, label %86
59:
	%60 = load i32, i32* %2
	%61 = mul i32 %60, -1
	%62 = load i32, i32* %47
	%63 = load i32, i32* %49
	%64 = add i32 %63, 1
	%65 = sdiv i32 %62, %64
	%66 = srem i32 %65, 2
	%67 = add i32 %61, %66
	store i32 %67, i32* %48
	%68 = load i32, i32* %48
	call void @putint(i32 %68)
	call void @putch(i32 10)
	%69 = load i32, i32* %48
	%70 = icmp sgt i32 %69, 0
	br i1 %70, label %71, label %73
71:
	%72 = getelementptr [5 x i8], [5 x i8]* @dqr1, i32 0, i32 0
	call void @putstr(i8* %72)
	call void @putch(i32 10)
	br label %75
73:
	%74 = getelementptr [7 x i8], [7 x i8]* @dqr2, i32 0, i32 0
	call void @putstr(i8* %74)
	call void @putch(i32 10)
	br label %75
75:
	%76 = load i32, i32* %49
	%77 = icmp sge i32 %76, 0
	br i1 %77, label %78, label %80
78:
	br label %83
79:
	br label %82
80:
	br label %86
81:
	br label %82
82:
	br label %83
83:
	%84 = load i32, i32* %49
	%85 = add i32 %84, 1
	store i32 %85, i32* %49
	br label %55
86:
	store i32 0, i32* %49
	br label %87
87:
	%88 = load i32, i32* %49
	%89 = load i32, i32* %47
	%90 = icmp slt i32 %88, %89
	br i1 %90, label %91, label %96
91:
	br label %96
92:
	br label %93
93:
	%94 = load i32, i32* %49
	%95 = add i32 %94, 1
	store i32 %95, i32* %49
	br label %87
96:
	store i32 0, i32* %49
	br label %97
97:
	br label %98
98:
	br label %103
99:
	br label %100
100:
	%101 = load i32, i32* %49
	%102 = add i32 %101, 1
	store i32 %102, i32* %49
	br label %97
103:
	store i32 0, i32* %49
	br label %104
104:
	%105 = load i32, i32* %49
	%106 = load i32, i32* %47
	%107 = icmp slt i32 %105, %106
	br i1 %107, label %108, label %110
108:
	br label %110
109:
	br label %104
110:
	br label %111
111:
	br label %112
112:
	br label %117
113:
	br label %114
114:
	%115 = load i32, i32* %49
	%116 = add i32 %115, 1
	store i32 %116, i32* %49
	br label %111
117:
	br label %118
118:
	%119 = load i32, i32* %49
	%120 = load i32, i32* %47
	%121 = icmp slt i32 %119, %120
	br i1 %121, label %122, label %124
122:
	br label %124
123:
	br label %118
124:
	store i32 0, i32* %49
	br label %125
125:
	br label %126
126:
	br label %128
127:
	br label %125
128:
	br label %129
129:
	br label %130
130:
	br label %132
131:
	br label %129
132:
	br label %133
133:
	br label %135
134:
	br label %135
135:
	%136 = load i32, i32* %47
	%137 = load i32, i32* %2
	%138 = icmp sge i32 %136, %137
	br i1 %138, label %139, label %140
139:
	br label %140
140:
	%141 = load i32, i32* %47
	%142 = load i32, i32* %2
	%143 = icmp sle i32 %141, %142
	br i1 %143, label %144, label %145
144:
	br label %145
145:
	%146 = load i32, i32* %47
	%147 = load i32, i32* %2
	%148 = icmp eq i32 %146, %147
	br i1 %148, label %149, label %150
149:
	br label %150
150:
	%151 = load i32, i32* %47
	%152 = load i32, i32* %2
	%153 = icmp sgt i32 %151, %152
	br i1 %153, label %154, label %155
154:
	br label %155
155:
	%156 = load i32, i32* %47
	%157 = load i32, i32* %2
	%158 = icmp slt i32 %156, %157
	br i1 %158, label %159, label %160
159:
	br label %160
160:
	%161 = load i32, i32* %47
	%162 = load i32, i32* %2
	%163 = icmp ne i32 %161, %162
	br i1 %163, label %164, label %165
164:
	br label %165
165:
	%166 = call i32 @f6()
	br label %167
167:
	call void @f2(i32 1)
	br label %168
168:
	br label %174
169:
	%170 = load i32, i32* %47
	%171 = load i32, i32* %2
	%172 = icmp ne i32 %170, %171
	br i1 %172, label %173, label %174
173:
	br label %174
174:
	br label %178
175:
	%176 = load i32, i32* %2
	%177 = icmp sgt i32 %176, 0
	br i1 %177, label %178, label %179
178:
	br label %179
179:
	%180 = load i32, i32* %47
	%181 = icmp eq i32 %180, 0
	%182 = zext i1 %181 to i32
	%183 = load i32, i32* %2
	%184 = icmp eq i32 %182, %183
	br i1 %184, label %195, label %185
185:
	%186 = load i32, i32* %2
	%187 = icmp sgt i32 %186, 0
	br i1 %187, label %188, label %196
188:
	br label %189
189:
	%190 = load i32, i32* %47
	%191 = add i32 %190, 1
	%192 = srem i32 %191, 2
	%193 = sdiv i32 %192, 2
	%194 = icmp ne i32 %193, 0
	br i1 %194, label %195, label %196
195:
	br label %196
196:
	ret i32 0
}

