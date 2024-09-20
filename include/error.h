#ifndef ERROR_H
#define ERROR_H
class Error {
    private:
        int line_number;
        char error_type;

    public:
        Error(int line_number, char error_type);
        ~Error();
        int get_line_number();
        char get_error_type();    
}

#endif