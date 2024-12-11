int pos_r[500];
int pos_e[500];
char s[500] = "RexloveStudybutstudyemmmrx";

int main()
{
    //scanf("%s", s);
    int l, i;
    l = getint();
    int size_r = 0, size_R = 0, size_e = 0, size_E = 0, top_r = 0, top_e = 0;
    for (i = 0; i < l; i = i + 1) {
        if (s[i] == 'R' || s[i] == 'r') {
            pos_r[size_r++] = i;
            size_R++;
        }
        if ((s[i] == 'e' || s[i] == 'E') && (size_R > size_E)) {
            pos_e[size_e++] = i;
            size_E++;
        }
        if (s[i] == 'x' || s[i] == 'X') {
            if (size_R && size_E) {
                s[pos_r[top_r++]] = '\0';
                size_R--;
                s[pos_e[top_e++]] = '\0';
                size_E--;
                s[i] = '\0';
            }
        }
    }
    for (i = 0; i < l; i = i + 1){
        if (s[i] != '\0') {
            printf("%c", s[i]);
        }
    }
}