#define InstructionMisaligned 0 // 指令地址未对齐
#define InstructionFault 1 // 指令错误
#define IllegalInstruction 2 // 非法指令
#define Breakpoint 3 // 断点
#define LoadFault 5 // 加载错误
#define StoreMisaligned 6 // 保存未对齐
#define StoreFault 7 // 保存错误
#define UserEnvCall 8 // U调用
#define VirtualSupervisorEnvCall 10 // 虚拟S调用
#define InstructionPageFault 12 // 指令页错误
#define LoadPageFault 13 // 加载页错误
#define StorePageFault 15 // 保存页错误
#define InstructionGuestPageFault 20
#define LoadGuestPageFault 21
#define VirtualInstruction 22
#define StoreGuestPageFault 23

#ifndef _TrapContext
#define _TrapContext

typedef struct {
    unsigned long x[32];
    unsigned long sstatus;
    unsigned long sepc;
} TrapContext;

#endif

TrapContext *init_app_context(void *entry, unsigned long sp);
TrapContext *trap_handler(TrapContext *ctx);