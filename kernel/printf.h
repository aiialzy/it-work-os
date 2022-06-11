#include <stdarg.h>

#define STDOUT 1

void vprintf(const char *fmt, va_list ap);
void printf(const char *fmt, ...);
void panic(const char* s);
void printfinit();