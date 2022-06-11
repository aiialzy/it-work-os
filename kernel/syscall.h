#define SYSCALL_WRITE 64
#define SYSCALL_EXIT 93

long sys_call(long id, unsigned long args[3]);
long sys_write(long fd, char* s, unsigned long len);
void sys_exit(long xstate);