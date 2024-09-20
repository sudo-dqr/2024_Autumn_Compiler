#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <iostream>

class Error {
    private:
        int line_number;
        char error_type;

    public:
        Error(int line_number, char error_type);
        ~Error();

        int get_line_number();
        char get_error_type();
        std::string to_string();
};

#endif // ERROR_H