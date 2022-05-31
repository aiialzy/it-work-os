#include "syscall.h"

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

int _start() {
    clear_bss();
    return (int)exit((long)main());
}