#include "utils.h"

int Utils::counter = -1;
int Utils::str_gv_cnt = -1;

int Utils::cut_str(const std::string &str, int start) {
    int i = start;
    while (i < str.length() - 1) {
        if (str[i] == '%' && i + 1 < str.length() - 1) {
            if (str[i + 1] == 'd' || str[i + 1] == 'c') break;
        } else if (str[i] == '\\') break;
        //! if you wants to print standard llvm ir code, you need to recover the upper else code
        //! I turn it off when generating mips code
        i++;
    }
    return i;
}

int Utils::control_cnt(const std::string &str) { // %d | %c
    int cnt = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '%' && i + 1 < str.length()) {
            if (str[i + 1] == 'd' || str[i + 1] == 'c') {
                cnt++;
            }
        }
    }
    return cnt;
}

char Utils::get_escape_char(const std::string &str, int i) {
    switch (str[i])
    {
        case '0': return '\0';
        case 'a': return '\a';
        case 'b': return '\b';
        case 'f': return '\f';
        case 'v': return '\v';
        case 't': return '\t';
        case 'n': return '\n';
        case '\'': return '\'';
        case '\"': return '\"';
        case '\\': return '\\';
        default: return str[i];
    }
}