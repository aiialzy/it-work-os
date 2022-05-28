#include <stdarg.h>
#include "console.c"
#include "types.h"
#include "defs.h"

static char digits[] = "0123456789ABCDEF";

static void printstring(char* s) {
    for (char* p = s; *p; p++) {
        consoleputc(*p);
    }
}

static void printchar(int c) {
    consoleputc(c & 0xff);
}

static void printptr(uint64 ptr) {
    consoleputc('0');
    consoleputc('x');
    for (int i = 0; i < (sizeof(uint64) * 2); i++, ptr <<= 4) {
        consoleputc(digits[ptr >> (sizeof(uint64) * 8 - 4)]);
    }
}

static void printint(int xx, int base, int sign) {
    char buf[16];
    int i;
    uint x;

    if (sign && xx < 0) {
        x = -xx;
    } else {
        x = xx;
    }
    sign = xx < 0;

    i = 0;
    do {
        buf[i++] = digits[x % base];
        x /= base;
    } while (x);

    if (sign) {
        buf[i++] = '-';
    }

    while (i >= 0) {
        --i;
        consoleputc(buf[i]);
    }
}


void vprintf(const char *fmt, va_list ap) {
    if (fmt == 0) {
        panic("null fmt");
    }

    int i;
    char c;
    for (i = 0; fmt[i] != 0; i++) {
        c = fmt[i];

        if (c != '%') {
            consoleputc(c);
            continue;
        }

        c = fmt[++i];
        if (c == 0) {
            break;
        }
        switch (c) {
            case 'b':
                printint(va_arg(ap, int), 2, 1);
                break;
            case 'd':
                printint(va_arg(ap, int), 10, 1);
                break;
            case 'x':
                printint(va_arg(ap, int), 16, 1);
                break;
            case 'p':
                printptr(va_arg(ap, uint64));
                break;
            case 'c':
                printchar(va_arg(ap, int));
                break;
            case 's':
                printstring(va_arg(ap, char*));
                break;
            case '%':
                consoleputc('%');
                break;
            default:
                consoleputc('%');
                consoleputc(c);
                break;
        }
    }
}

void printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
}

void panic(const char* s) {
    printf("panic: ");
    printf(s);
    printf("\n");
    for (;;)
        ;
}

void printfinit() {}