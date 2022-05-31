#include "syscall.h"
#include "strings.c"

#define SYSCALL_WRITE 64
#define SYSCALL_EXIT 93

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