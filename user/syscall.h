#define SYSCALL_WRITE 64
#define SYSCALL_EXIT 93
#define SYSCALL_YIELD 124
#define SYSCALL_GET_TIME 169

long sys_write(long fd, char *s, unsigned long len);
long sys_exit(long xstate);
long sys_yield();
long sys_get_time();