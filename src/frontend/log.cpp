#include "log.h"
#include <iostream>
#include <fstream>

CompilerLogger& CompilerLogger::get_instance() {
    static CompilerLogger instance = CompilerLogger(LOG_ALL, LOG_FILE);
    return instance;
}

void CompilerLogger::log(std::string function_name, std::string message, bool error, int line_number, LogLevel level) {
    if (level == LOG_PARSER) {
        if (error)
            error_log.push_back("[Error]: " + function_name + ": " + message + " at line " + std::to_string(line_number));
        else
            parser_log.push_back(function_name + ": " + message + " at line " + std::to_string(line_number));
    } else if (level == LOG_VISITOR) {
        if (error) 
            error_log.push_back("[Error]: " + function_name + ": " + message + " at line " + std::to_string(line_number));
        else 
            visitor_log.push_back(function_name + ": " + message + " at line " + std::to_string(line_number));
    }
}

void CompilerLogger::print_logs() {
    if (log_level == LOG_NONE) return;
    if (output_type == LOG_FILE) {
        std::ofstream log_file = std::ofstream("log.txt", std::ios::trunc);
        log_file << "---------[Start Compiling]---------" << std::endl;
        if (log_level == LOG_PARSER) {
            log_file << "----------[Parser Logs]----------" << std::endl;
            for (std::string log : parser_log) {
                log_file << log << std::endl;
            }
        } else if (log_level == LOG_VISITOR) {
            log_file << "----------[Visitor Logs]----------" << std::endl;
            for (std::string log : visitor_log) {
                log_file << log << std::endl;
            }
        } else {
            log_file << "----------[Parser Logs]----------" << std::endl;
            for (std::string log : parser_log) {
                log_file << log << std::endl;
            }
            log_file << "----------[Visitor Logs]---------" << std::endl;
            for (std::string log : visitor_log) {
                log_file << log << std::endl;
            }
        }
        log_file << "----------[Error Logs]----------" << std::endl;
        for (std::string log : error_log) {
            log_file << log << std::endl;
        }
        log_file << "----------[End of Logs]----------" << std::endl;
        log_file << "[A Simple SysY Compiler by sudo-dqr from 2206,SCSE,BUAA, 2024 Autumn]" << std::endl;
        log_file.close();
    } else {
        std::cout << "---------[Start Compiling]---------" << std::endl;
        if (log_level == LOG_PARSER) {
            std::cout << "----------[Parser Logs]----------" << std::endl;
            for (std::string log : parser_log) {
                std::cout << log << std::endl;
            }
        } else if (log_level == LOG_VISITOR) {
            std::cout << "----------[Visitor Logs]----------" << std::endl;
            for (std::string log : visitor_log) {
                std::cout << log << std::endl;
            }
        } else {
            std::cout << "----------[Parser Logs]----------" << std::endl;
            for (std::string log : parser_log) {
                std::cout << log << std::endl;
            }
            std::cout << "----------[Visitor Logs]----------" << std::endl;
            for (std::string log : visitor_log) {
                std::cout << log << std::endl;
            }
        }
        std::cout << "----------[Error Logs]----------" << std::endl;
        for (std::string log : error_log) {
            std::cout << log << std::endl;
        }
        std::cout << "----------[End of Logs]----------" << std::endl;
        std::cout << "[A Simple SysY Compiler by sudo-dqr from 2206,SCSE,BUAA, 2024 Autumn]" << std::endl;
    }
}