#ifndef LOG_H
#define LOG_H
#include <string>
#include <vector>

enum LogLevel {
    LOG_PARSER,
    LOG_VISITOR,
    LOG_ALL,
    LOG_NONE
};

enum OutputType {
    LOG_FILE,
    CONSOLE
};

class CompilerLogger {

    private:
    LogLevel log_level = LOG_NONE;
    OutputType output_type = LOG_FILE;
    std::vector<std::string> parser_log;
    std::vector<std::string> visitor_log;
    std::vector<std::string> error_log;

    CompilerLogger(LogLevel log_level, OutputType output_type) : 
    log_level(log_level), output_type(output_type) {}

    public:
    static CompilerLogger& get_instance();
    void log(std::string function_name, std::string message, bool error, int line_number, LogLevel level);
    void print_logs();
};



#endif