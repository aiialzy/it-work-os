#include "log.h"
#include "printf.h"

void log(LogLevel level, char* fmt, va_list ap) {
    printf("%s[%s] ", level.sstyle, level.name);
    vprintf(fmt, ap);
    printf("%s\n", level.estyle);
}

void error(char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    LogLevel level = {
        name : "ERROR",
        sstyle : "\033[31m",
        estyle : "\033[0m",
    };
    log(level, fmt, ap);
    va_end(ap);
}

void warn(char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    LogLevel level = {
        name : "WARN ",
        sstyle : "\033[33m",
        estyle : "\033[0m",
    };
    log(level, fmt, ap);
    va_end(ap);
}

void info(char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    LogLevel level = {
        name : "INFO ",
        sstyle : "\033[34m",
        estyle : "\033[0m",
    };
    log(level, fmt, ap);
    va_end(ap);
}

void debug(char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    LogLevel level = {
        name : "DEBUG",
        sstyle : "\033[32m",
        estyle : "\033[0m",
    };
    log(level, fmt, ap);
    va_end(ap);
}

void trace(char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    LogLevel level = {
        name : "TRACE",
        sstyle : "\033[35m",
        estyle : "\033[0m",
    };
    log(level, fmt, ap);
    va_end(ap);
}
