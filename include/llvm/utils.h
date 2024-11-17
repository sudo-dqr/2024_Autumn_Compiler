#ifndef IR_UTILS_H
#define IR_UTILS_H

struct Utils {
    static int counter;
    static void reset_counter() { counter = -1; }
    static int get_counter() { return counter; }
    static int get_next_counter() { return ++counter; }

    static int str_gv_cnt; // 字符串全局变量计数
    static int get_next_str_cnt() { return ++str_gv_cnt; }

    static int control_cnt(const std::string &str);
    static int cut_str(const std::string &str, int start);
};

#endif