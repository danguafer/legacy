#include "LogService.h"

using Veritas::etc::LogService;

#include <cstdio>
#include <cstdarg>
#include <iostream>

void LogService::log(const char *format, ...) {
    std::cout << "[Log] ";

    va_list arg;
    va_start(arg, format);
    vprintf(format, arg);
    va_end(arg);

    std::cout << std::endl;
}

void LogService::error(const char *format, ...) {
    std::cout << "[Error] ";

    va_list arg;
    va_start(arg, format);
    vprintf(format, arg);
    va_end(arg);

    std::cout << std::endl;
}

void LogService::fatalError(const char *format, ...) {
    std::cout << "[Fatal Error] ";

    va_list arg;
    va_start(arg, format);
    vprintf(format, arg);
    va_end(arg);

    std::cout << std::endl;

    exit(0);
}
