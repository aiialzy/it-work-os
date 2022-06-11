#include "syscall.h"
#include "printf.h"

extern int main();

void start_bss();
void end_bss();

void clear_bss() {
    for (void *p = &start_bss; p < (void *)(&end_bss); p++) {
        *(unsigned char *)p = 0;
    }
}

long exit(long code) {
    return sys_exit(code);
}

void start() {
    clear_bss();
    exit((long)main());
}