#ifndef ERROR_H
#define ERROR_H

#include <fstream>
#include <deque>
#include <algorithm>

struct Error {
    int line_number;
    char type;
};

struct ErrorList {
    static std::deque<Error> errors;
    void static report_error(int line_number, char type);
    void static print_errors();
};

#endif // ERROR_H