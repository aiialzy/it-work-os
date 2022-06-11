#include <stdarg.h>

#ifndef _LogLevel
#define _LogLevel

typedef struct {
    char* name;
    char* sstyle;
    char* estyle;
}LogLevel;

#endif

void log(LogLevel level, char* fmt, va_list ap);
void error(char* fmt, ...);
void warn(char* fmt, ...);
void info(char* fmt, ...);
void debug(char* fmt, ...);
void trace(char* fmt, ...);