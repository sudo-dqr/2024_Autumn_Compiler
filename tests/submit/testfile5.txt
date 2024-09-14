// A testfile for C 

int main() {
    printf("22373362\n");
    // operator test
    // 1. int
    int a = (1 + 9);
    int b = a + 2;
    int c = b * a;
    int d = c / 10;
    int e = d % 5;
    int f = e - 1;
    printf("a = %d, b = %d, c = %d, d = %d, e = %d, f = %d\n", a, b, c, d, e, f);
    int result = ( a + b ) * c / d % e + f;
    printf("result = %d\n", result);
    if (result != 100) {
        printf("result is not 100\n");
    }
    if (!result) {
        printf("result is 0\n");
    }
    // int & char
    int g = 1;
    char h = 'a' + 1;
    int i = g + h;
    int j = 'a' + 'b' + 'c';
    printf("g = %d, h = %c, i = %d, j = %d\n", g, h, i, j);

    int k = -1;
    int l = +2;
    int m = +-+k;
    printf("k = %d, l = %d, m = %d\n", k, l, m);
    return 0;
}

