// A testfile for B standard
// 数组定义 数组元素的使用 数组传参

// FuncDef test

void bubble_sort(int a[], int n) {
    int i, j;
    for (i = 0; i < n; i = i + 1) {
        for (j = 0; j < n - i - 1; j = j + 1) {
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
    return;
}

void print_char_array(char a[], int n) {
    int i;
    for (i = 0; i < n; i = i + 1) {
        printf("%c ", a[i]);
    }
    printf("\n");
    return;
}

void print_int_array(int a[], int n) {
    int i;
    for (i = 0; i < n; i = i + 1) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return;
}

int main() {
    printf("22373362\n");
    int a[10] = {10,9,8,7,6,5,4,3,2,1};
    char b[10] = {'a','b','c','d','e','f','g','h','i','j'};
    char hello[20] = "Hello, world!\n";
    printf("The first element of a is %d\n", a[0]);
    printf("The last element of b is %c\n", b[9]);
    print_char_array(hello, 20);
    print_char_array(b, 10);
    bubble_sort(a, 10);
    print_int_array(a, 10);
    return 0;
}