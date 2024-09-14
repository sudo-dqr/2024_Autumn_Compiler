// A testfile for B standard

int getchar(){
    char c;
    scanf("%c",&c);
    return (int)c;
}
int getint(){
    int t;
    scanf("%d",&t);
    while(getchar()!='\n');
    return t;
}


int main() {
    const int arr[3] = {1,2,3};
    const char str[20] = "hello,world";
    printf("22373362\n");
    int a[10];
    a[0] = getchar();
    printf("%d\n",a[0]);
    char b[10];
    b[0] = getint();
    printf("%c\n",b[0]);
    return 0;
}