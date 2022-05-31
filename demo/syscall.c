#include <stdarg.h>

#define SYSCALL_WRITE 64
#define SYSCALL_EXIT 93

long strlen(char *s) {
    long c = 0;
    while (s[c]) {
        c += 1;
    }
    return c;
}

long sys_call(long id, long args[3]) {
    long ret; 
    asm("mv a7, %0" : : "r" (id));
    asm("ld a0, (%0)" : : "r" (args));
    asm("ld a2, (%0)" : : "r" (args+2));
    asm("ld a1, (%0)" : : "r" (args+1));
    asm("ecall");
    asm("mv a0, %0" : "=r" (ret));
    return ret;
}

long sys_write(long fd, char *s) {
    long len = strlen(s);
    long args[3] = {1, (long)s, len};
    return sys_call(SYSCALL_WRITE, args);
}

long sys_exit(long xstate) {
    long args[3] = {xstate, 0, 0};
    return sys_call(SYSCALL_EXIT, args);
}

static char digits[] = "0123456789ABCDEF";

#define STDOUT 1

static void puts(char *s) {
    sys_write(STDOUT, s);
}

void panic(char* s) {
    puts("panic: ");
    puts(s);
    puts("\n");
    for (;;)
        ;
}

static void putc(char c) {
    char s[] = {c};
    puts(s);
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

int main() {
    printf("Hello, world!\n");
    return 0;
}

long _start() {
    return sys_exit((long)main());
}