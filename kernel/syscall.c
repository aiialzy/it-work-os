#include "syscall.h"
#include "string.h"
#include "printf.h"
#include "log.h"
#include "console.h"
#include "batch.h"

long sys_call(long id, unsigned long args[3]) {
    switch (id) {
        case SYSCALL_WRITE:
            return sys_write((long)args[0], (char *)args[1], args[2]);

        case SYSCALL_EXIT:
            sys_exit((long)args[0]);

        default:
            break;
    }

    return 0;
}

long sys_write(long fd, char* s, unsigned long len) {
    switch (fd) {
        case STDOUT:
            for (unsigned long i=0; i<len; i++) {
                consoleputc(s[i]);
            } 
            break;
    }
    return len;
}

void sys_exit(long xstate) {
    info("[kernel] Application exited with code %d", xstate);

    run_next_app();
}