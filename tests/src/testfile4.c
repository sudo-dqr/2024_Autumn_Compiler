// A testfile for C standard
// 关于C级标准的说明：不允许出现数组 以及&& ||

//   Decl test
int v0 = 0;
int v1 = 1, v2 = 2;
const int v3 = 3, v4 = 4;
const int v5 = 5;
char ch = 'a';
char ch1 = 'b', ch2 = 'c';
const char ch3 = 'd', ch4 = 'e';

int main() {
   printf("22373362\n");
   printf("v0 = %d, v1 = %d, v2 = %d, v3 = %d, v4 = %d, ch = %c, ch1 = %c, ch2 = %c, ch3 = %c, ch4 = %c\n", v0, v1, v2, v3, v4, ch, ch1, ch2, ch3, ch4);
   const int arr[3] = {1,2,3};
   const char str[20] = "hello,world";
   // Stmt test
   int cnt1 = 0;
   int cnt2 = 0;
   int cnt3 = 0;
   int cnt4 = 0;
   int cnt5 = 0;
   int cnt6 = 0;
   int cnt7 = 0;
   int cnt8 = 0;
   int i = 0;
   for (i = 0; i < 1; i = i + 1) {
      cnt1 = cnt1 + 1;
   }
   for (; i < 2; i = i + 1) {
      cnt2 = cnt2 + 1;
   }
   for (i = 0; ;i = i + 1) {
      cnt3 = cnt3 + 1;
      if (i == 1) {
         break;
      } else {
         continue;
      }
   }
   for (i = 0; i < 1; ) {
      cnt4 = cnt4 + 1;
      i = i + 1;
   }

   for (i = 0; ; ) {
      cnt5 = cnt5 + 1;
      i = i + 1;
      if (i == 1) {
         break;
      }
   }

   i = 0;
   for ( ; i < 1; ) {
      cnt6 = cnt6 + 1;
      i = i + 1;
   }

   i = 0;
   for ( ; ;i = i + 1) {
      cnt7 = cnt7 + 1;
      if (i == 1) {
         break;
      }
   }

   i = 0;
   for ( ; ; ) {
      cnt8 = cnt8 + 1;
      i = i + 1;
      if (i == 1) {
         break;
      }
   }

   printf("For loop test: cnt1 = %d, cnt2 = %d, cnt3 = %d, cnt4 = %d, cnt5 = %d, cnt6 = %d, cnt7 = %d, cnt8 = %d\n", cnt1, cnt2, cnt3, cnt4, cnt5, cnt6, cnt7, cnt8);
   return 0;
}