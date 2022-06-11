#include "syscall.h"
#include "printf.h"
#include "string.h"

static char digits[] = "0123456789ABCDEF";

void puts(char *s) {
    unsigned long len = strlen(s);
    sys_write(STDOUT, s, len);
}

void panic(char* s) {
    puts("panic: ");
    puts(s);
    puts("\n");
    for (;;)
        ;
}

void putc(char c) {
    sys_write(STDOUT, &c, 1);
}

static void printstring(char* s) {
    for (char* p = s; *p; p++) {
        putc(*p);
    }
}

static void printchar(int c) {
    putc(c & 0xff);
}

static void printptr(unsigned long ptr) {
    puts("0x");
    for (int i = 0; i < (sizeof(unsigned long) * 2); i++, ptr <<= 4) {
        putc(digits[ptr >> (sizeof(unsigned long) * 8 - 4)]);
    }
}

static void printint(int xx, int base, int sign) {
    char buf[16];
    int i;
    unsigned int x;

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
        putc(buf[i]);
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
            putc(c);
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
                printptr(va_arg(ap, unsigned long));
                break;
            case 'c':
                printchar(va_arg(ap, int));
                break;
            case 's':
                printstring(va_arg(ap, char*));
                break;
            case '%':
                putc('%');
                break;
            default:
                putc('%');
                putc(c);
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