#include "err.h"

Error::Error(int line_number, char error_type) {
    this->line_number = line_number;
    this->error_type = error_type;
}

Error::~Error() {

}

int Error::get_line_number() {
    return this->line_number;
}

char Error::get_error_type() {
    return this->error_type;
}


