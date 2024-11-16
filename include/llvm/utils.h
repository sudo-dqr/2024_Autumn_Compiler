#ifndef IR_UTILS_H
#define IR_UTILS_H

struct Utils {
    static int counter;
    static void reset_counter() { counter = -1; }
    static int get_counter() { return counter; }
    static int get_next_counter() { return ++counter; }
};

#endif