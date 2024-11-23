char str[7]  = {'\a', '\t', '\'', 0};
const char str4[45]  = {'a', 'b', 'c', 0};
char c = '\n';
char c1[4] = "\n\n\n";
const char c2[5] = "\n\n\0";
int func() {
    char str5[10]  = {'a', 'b', 'c', 0};
    const char str6[4]  = {'a', 'b', 'c', 0};
    return str5[6];
}
int main(){
    int a = 4;
    if (!a) {
        char str2[4]  = {'a', 'b', 'c', 0};
        const char str3[95]  = {'a', 'b', 'c', 0};
    } else if (!func()) {
        char tt[4] = "%c\n";
        printf("\nthis is \n %c\n\n", tt[2]);
        return 6;
    }
    return 0;
}