#include "syscall.h"

long sys_call(long id, long args[3]) {
    long ret; 
    asm volatile ("mv a7, %0" : : "r" (id));
    asm volatile ("ld a0, (%0)" : : "r" (args));
    asm volatile ("ld a2, (%0)" : : "r" (args+2));
    asm volatile ("ld a1, (%0)" : : "r" (args+1));
    asm("ecall");
    asm volatile ("mv a0, %0" : "=r" (ret));
    return ret;
}

long sys_write(long fd, char *s, unsigned long len) {
    long args[3] = {1, (long)s, len};
    return sys_call(SYSCALL_WRITE, args);
}

long sys_exit(long xstate) {
    long args[3] = {xstate, 0, 0};
    return sys_call(SYSCALL_EXIT, args);
}