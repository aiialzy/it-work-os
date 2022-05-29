#include <stdarg.h>

// console.c
void consoleinit();

// printf.c
void printfinit();
void printf(const char*, ...);
void vprintf(const char*, va_list);
void panic(const char*) __attribute__((noreturn));
void printfinit();

// log.c
void error(char* fmt, ...);
void warn(char* fmt, ...);
void info(char* fmt, ...);
void debug(char* fmt, ...);
void trace(char* fmt, ...);