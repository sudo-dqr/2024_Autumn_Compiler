// A testfile for C standard

/* 多行注释测试*/

// FuncDef test
void hello() {
    printf("Hello, Compiler!\n");
    return;
}

void empty() {

}

int sum(int a, int b) {
    return a + b;
}

char transfer_to_upcase(char down) {
    if (down >= 'a') {
        if (down <= 'z') {
            return down - 32;
        }
        return down;
    } else {
        return down;
    }
}

int main() {
    printf("22373362\n");
    hello();
    empty();
    printf("The sum is %d\n", sum(1, 2));
    printf("The upcase of 'a' is %c\n", transfer_to_upcase('a'));
    return 0;
}