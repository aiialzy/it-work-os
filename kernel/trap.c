#include "riscv.h"
#include "trap.h"
#include "log.h"
#include "syscall.h"
#include "batch.h"

static TrapContext trap_context;

void set_sp(unsigned long sp) {
    trap_context.x[2] = sp;
}

TrapContext* init_app_context(void *entry, unsigned long sp) {
    unsigned long sstatus = r_sstatus();
    trap_context.sstatus = sstatus & (~(1UL << 8));
    trap_context.sepc = (unsigned long)entry;
    set_sp(sp);
    return &trap_context;
}

TrapContext *trap_handler(TrapContext *ctx) {
    // unsigned long sstatus = r_sstatus();
    // unsigned long sepc = r_sepc();
    unsigned long scause = r_scause();
    // unsigned long stval = r_stval();

    char is_interrupt = (scause >> 63) & 1;
    unsigned long exception_code = scause & ~(1UL << 63);
    if (is_interrupt) {
        info("scause: %b", scause);
        info("是中断");
        while(1){}
        return ctx;
    }

    switch (exception_code) {
        case UserEnvCall:
            ctx->sepc += 4;
            unsigned long args[3] = {ctx->x[10], ctx->x[11], ctx->x[12]};
            ctx->x[10] = sys_call(ctx->x[17], args);
            break;

        case StoreFault:
        case StorePageFault:
            error("保存错误");
            run_next_app();
            break;

        case IllegalInstruction:
            error("非法指令");
            run_next_app();
            break;

        default:
            error("未知错误");
            run_next_app();
            break;
    }

    return ctx;
}