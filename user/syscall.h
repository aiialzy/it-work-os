#define SYSCALL_WRITE 64
#define SYSCALL_EXIT 93

long sys_write(long fd, char *s, unsigned long len);
long sys_exit(long xstate);