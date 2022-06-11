#include "string.h"

void memset(void *s, char ch, unsigned long n) {
    unsigned long begin = (unsigned long)s;
    unsigned long end = begin + n;
    while (begin < end) {
        *(char *)begin = ch;
        begin += 1;
    }
}

void memcpy(void *dest, void *src, unsigned long n) {
    for (unsigned long i = 0; i < n; i++) {
        *(char *)dest++ = *(char *)src++;
    }
}

long strlen(char *s) {
    long c = 0;
    while (s[c]) {
        c += 1;
    }
    return c;
}