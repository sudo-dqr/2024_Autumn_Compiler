#include "utils.h"

int Utils::counter = -1;
int Utils::str_gv_cnt = -1;

static int Utils::cut_str(const std::string &str, int start) {
    int i = start;
    while (i < str.length()) {
        if (str[i] == '%' && i + 1 < str.length()) {
            if (str[i + 1] == 'd' || str[i + 1] == 'c') {
                break;
            }
        }
        i++;
    }
    return i;
}

static int Utils::control_cnt(const std::string &str) { // %d | %c
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