declare i32 @getchar()
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)
declare void @putstr(i8*)

@b = dso_local global [3 x i32] [i32 1, i32 2, i32 3]
@x = dso_local global i32 5
@z = dso_local global i32 114514
@y = dso_local global [3 x i32] zeroinitializer
@global_var = dso_local global i32 0
@buaa = dso_local global i8 0
@aa = dso_local global [5 x i8] c"abc\0"
@aaa = dso_local global [6 x i8] c"xyz\00\00\00"
@dqr0 = private unnamed_addr constant [9 x i8] c"21374067\00"
@dqr1 = private unnamed_addr constant [4 x i8] c"i: \00"

define dso_local i32 @g(i32* %0) {
1:
	%2 = alloca i32*
	store i32* %0, i32** %2
	%3 = load i32*, i32** %2
	%4 = getelementptr i32, i32* %3, i32 0
	%5 = load i32, i32* %4
	%6 = load i32*, i32** %2
	%7 = load i32*, i32** %2
	%8 = getelementptr i32, i32* %7, i32 1
	%9 = load i32, i32* %8
	%10 = load i32*, i32** %2
	%11 = getelementptr i32, i32* %10, i32 0
	%12 = load i32, i32* %11
	%13 = sub i32 0, %12
	%14 = add i32 %9, %13
	%15 = getelementptr i32, i32* %6, i32 %14
	%16 = load i32, i32* %15
	%17 = add i32 %5, %16
	ret i32 %17
}

define dso_local i8 @foo(i32 %0, i32 %1) {
2:
	%3 = alloca i32
	%4 = alloca i32
	store i32 %0, i32* %3
	store i32 %1, i32* %4
	ret i8 111
}

define dso_local void @fooo(i32 %0, i32 %1) {
2:
	%3 = alloca i32
	%4 = alloca i32
	store i32 %0, i32* %3
	store i32 %1, i32* %4
	ret void
}

define dso_local i32 @func() {
0:
	%1 = load i32, i32* @global_var
	%2 = add i32 %1, 1
	store i32 %2, i32* @global_var
	ret i32 1
}

define dso_local i32 @main() {
0:
	%1 = getelementptr [9 x i8], [9 x i8]* @dqr0, i32 0, i32 0
	call void @putstr(i8* %1)
	call void @putch(i32 10)
	%2 = alloca i32
	store i32 0, i32* %2
	%3 = alloca i8
	store i8 97, i8* %3
	%4 = alloca i32
	store i32 -10, i32* %4
	%5 = alloca i32
	%6 = load i32, i32* %4
	%7 = add i32 %6, 5
	%8 = mul i32 %7, 2
	store i32 %8, i32* %5
	%9 = load i32, i32* %4
	%10 = icmp slt i32 %9, 20
	br i1 %10, label %16, label %11
11:
	%12 = call i32 @func()
	%13 = icmp eq i32 %12, 0
	%14 = zext i1 %13 to i32
	%15 = icmp ne i32 %14, 0
	br i1 %15, label %16, label %19
16:
	%17 = load i32, i32* %4
	%18 = sub i32 %17, 1
	store i32 %18, i32* %4
	br label %31
19:
	%20 = load i32, i32* %4
	%21 = icmp sgt i32 %20, 0
	br i1 %21, label %22, label %30
22:
	%23 = call i32 @func()
	%24 = icmp ne i32 %23, 0
	br i1 %24, label %25, label %30
25:
	%26 = load i32, i32* %4
	%27 = add i32 %26, 1
	store i32 %27, i32* %4
	%28 = load i32, i32* %4
	%29 = add i32 %28, 1
	br label %30
30:
	br label %31
31:
	%32 = load i32, i32* %4
	call void @putint(i32 %32)
	call void @putch(i32 10)
	store i32 0, i32* %2
	br label %33
33:
	%34 = load i32, i32* %2
	%35 = icmp slt i32 %34, 6
	br i1 %35, label %36, label %43
36:
	%37 = load i32, i32* %2
	%38 = getelementptr [4 x i8], [4 x i8]* @dqr1, i32 0, i32 0
	call void @putstr(i8* %38)
	call void @putint(i32 %37)
	call void @putch(i32 10)
	br label %40
39:
	br label %40
40:
	%41 = load i32, i32* %2
	%42 = add i32 %41, 1
	store i32 %42, i32* %2
	br label %33
43:
	%44 = alloca [3 x i32]
	%45 = getelementptr [3 x i32], [3 x i32]* %44, i32 0, i32 0
	store i32 1, i32* %45
	%46 = getelementptr [3 x i32], [3 x i32]* %44, i32 0, i32 1
	store i32 2, i32* %46
	%47 = getelementptr [3 x i32], [3 x i32]* %44, i32 0, i32 2
	store i32 3, i32* %47
	%48 = alloca i32
	%49 = call i32 @func()
	store i32 %49, i32* %48
	%50 = alloca i32
	%51 = call i32 @getint()
	store i32 %51, i32* %50
	%52 = getelementptr [3 x i32], [3 x i32]* %44, i32 0, i32 0
	%53 = call i32 @g(i32* %52)
	store i32 %53, i32* %2
	%54 = call i32 @getchar()
	%55 = trunc i32 %54 to i8
	store i8 %55, i8* %3
	store i8 97, i8* %3
	br label %56
56:
	%57 = load i8, i8* %3
	%58 = zext i8 %57 to i32
	%59 = icmp slt i32 %58, 127
	br i1 %59, label %63, label %60
60:
	%61 = load i32, i32* %2
	%62 = icmp ne i32 %61, 0
	br i1 %62, label %63, label %79
63:
	%64 = load i8, i8* %3
	%65 = zext i8 %64 to i32
	%66 = add i32 %65, 1
	%67 = trunc i32 %66 to i8
	store i8 %67, i8* %3
	%68 = load i8, i8* %3
	%69 = zext i8 %68 to i32
	%70 = icmp eq i32 %69, 120
	br i1 %70, label %71, label %73
71:
	br label %79
72:
	br label %73
73:
	br label %74
74:
	%75 = load i8, i8* %3
	%76 = zext i8 %75 to i32
	%77 = add i32 %76, 1
	%78 = trunc i32 %77 to i8
	store i8 %78, i8* %3
	br label %56
79:
	store i8 97, i8* %3
	br label %80
80:
	br label %81
81:
	%82 = load i8, i8* %3
	%83 = zext i8 %82 to i32
	%84 = add i32 %83, 1
	%85 = trunc i32 %84 to i8
	store i8 %85, i8* %3
	%86 = load i8, i8* %3
	%87 = zext i8 %86 to i32
	%88 = icmp eq i32 %87, 120
	br i1 %88, label %89, label %91
89:
	br label %97
90:
	br label %91
91:
	br label %92
92:
	%93 = load i8, i8* %3
	%94 = zext i8 %93 to i32
	%95 = add i32 %94, 1
	%96 = trunc i32 %95 to i8
	store i8 %96, i8* %3
	br label %80
97:
	%98 = load i8, i8* %3
	%99 = zext i8 %98 to i32
	call void @putch(i32 %99)
	call void @putch(i32 10)
	%100 = load i8, i8* %3
	%101 = zext i8 %100 to i32
	call void @putint(i32 %101)
	call void @putch(i32 10)
	%102 = load i8, i8* %3
	%103 = zext i8 %102 to i32
	%104 = icmp sgt i32 %103, 0
	br i1 %104, label %105, label %194
105:
	%106 = load i8, i8* %3
	%107 = zext i8 %106 to i32
	%108 = icmp slt i32 %107, 0
	br i1 %108, label %109, label %194
109:
	%110 = load i8, i8* %3
	%111 = zext i8 %110 to i32
	%112 = icmp sle i32 %111, 0
	br i1 %112, label %113, label %194
113:
	%114 = load i8, i8* %3
	%115 = zext i8 %114 to i32
	%116 = icmp sge i32 %115, 0
	br i1 %116, label %117, label %194
117:
	%118 = load i8, i8* %3
	%119 = zext i8 %118 to i32
	%120 = icmp ne i32 %119, 0
	br i1 %120, label %121, label %194
121:
	%122 = load i8, i8* %3
	%123 = zext i8 %122 to i32
	%124 = icmp eq i32 %123, 0
	br i1 %124, label %125, label %194
125:
	br label %126
126:
	%127 = load i8, i8* %3
	%128 = zext i8 %127 to i32
	%129 = icmp eq i32 %128, 0
	%130 = zext i1 %129 to i32
	%131 = icmp ne i32 %130, 0
	br i1 %131, label %132, label %148
132:
	%133 = load i8, i8* %3
	%134 = zext i8 %133 to i32
	%135 = add i32 %134, 1
	%136 = trunc i32 %135 to i8
	store i8 %136, i8* %3
	%137 = load i8, i8* %3
	%138 = zext i8 %137 to i32
	%139 = icmp eq i32 %138, 120
	br i1 %139, label %140, label %142
140:
	br label %148
141:
	br label %142
142:
	br label %143
143:
	%144 = load i8, i8* %3
	%145 = zext i8 %144 to i32
	%146 = add i32 %145, 1
	%147 = trunc i32 %146 to i8
	store i8 %147, i8* %3
	br label %126
148:
	br label %149
149:
	br label %150
150:
	store i8 97, i8* %3
	br label %149
151:
	%152 = load i8, i8* %3
	store i8 %152, i8* %3
	br label %153
153:
	br label %154
154:
	store i8 98, i8* %3
	br label %153
155:
	br label %156
156:
	br label %157
157:
	store i8 99, i8* %3
	br label %158
158:
	%159 = load i8, i8* %3
	store i8 %159, i8* %3
	br label %156
160:
	br label %161
161:
	%162 = load i8, i8* %3
	%163 = load i8, i8* %3
	%164 = zext i8 %162 to i32
	%165 = zext i8 %163 to i32
	%166 = icmp ne i32 %164, %165
	br i1 %166, label %167, label %168
167:
	store i8 100, i8* %3
	br label %161
168:
	%169 = load i8, i8* %3
	store i8 %169, i8* %3
	br label %170
170:
	%171 = load i8, i8* %3
	%172 = load i8, i8* %3
	%173 = zext i8 %171 to i32
	%174 = zext i8 %172 to i32
	%175 = icmp ne i32 %173, %174
	br i1 %175, label %176, label %177
176:
	store i8 101, i8* %3
	br label %170
177:
	%178 = load i8, i8* %3
	store i8 %178, i8* %3
	br label %179
179:
	br label %180
180:
	store i8 102, i8* %3
	br label %181
181:
	%182 = load i8, i8* %3
	store i8 %182, i8* %3
	br label %179
183:
	br label %184
184:
	%185 = load i8, i8* %3
	%186 = load i8, i8* %3
	%187 = zext i8 %185 to i32
	%188 = zext i8 %186 to i32
	%189 = icmp ne i32 %187, %188
	br i1 %189, label %190, label %193
190:
	store i8 103, i8* %3
	br label %191
191:
	%192 = load i8, i8* %3
	store i8 %192, i8* %3
	br label %184
193:
	br label %194
194:
	ret i32 0
}

