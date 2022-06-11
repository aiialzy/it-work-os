#include "string.h"

long strlen(char *s) {
    long c = 0;
    while (s[c]) {
        c += 1;
    }
    return c;
}