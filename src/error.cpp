#include "error.h"

void report_error(int line_number, char type) {
    std::ofstream error_out("error.txt", std::ofstream::out);
    error_out << line_number << " " << type << std::endl;
    error_out.close();
}