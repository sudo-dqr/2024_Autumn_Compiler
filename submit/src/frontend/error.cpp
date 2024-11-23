#include "error.h"

std::deque<Error> ErrorList::errors = std::deque<Error>();

void ErrorList::report_error(int line_number, char type) {
    errors.push_back({line_number, type});
}

void ErrorList::print_errors() {
    if (errors.empty()) {
        return;
    }
    std::ofstream error_out("error.txt", std::ios::trunc);
    sort(errors.begin(), errors.end(), [](const Error &a, const Error &b) {
        return a.line_number < b.line_number;
    });
    for (const auto &error : errors) {
        error_out << error.line_number << " " << error.type << std::endl;
    }
    error_out.close();
}

/*
 * b 函数名/变量名在当前作用域已经定义
 * g 有返回值函数缺号return语句
 * h 不能改变常量的值
 * m 在非循环块中使用break/conitnue
 * f 无返回值函数存在不匹配的return语句
 * c 使用了未定义标识符
 * d 函数调用语句中，参数个数与函数定义中的参数个数不匹配
 * e 函数参数类型不匹配
 * l printf中格式字符与表达式个数不匹配
 */