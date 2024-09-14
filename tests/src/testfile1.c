// A testfile for A standard
// 复杂条件判断 短路求值

int flag = 0;
int func() {
    flag = flag + 1;
    return 1;
}
int main() {
    printf("22373362\n");

    if (0 && func()){
        ;
    }
    printf("%d",flag); // 输出 0
    if (1 || func()) {
        ;
    }
    printf("%d",flag); // 输出 0
    return 0;
}