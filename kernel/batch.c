#include "log.h"
#include "batch.h"
#include "string.h"
#include "trap.h"

static unsigned char KERNEL_STACK[KERNEL_STACK_SIZE];
static unsigned char USER_STACK[USER_STACK_SIZE];
static AppManager app_manager;

unsigned long get_user_sp() {
    return (unsigned long)USER_STACK + USER_STACK_SIZE;
}

unsigned long get_kernel_sp() {
    return (unsigned long)KERNEL_STACK + KERNEL_STACK_SIZE;
}

unsigned long push_context(TrapContext *ctx) {
    memcpy((void *)(get_kernel_sp() - sizeof(TrapContext)), ctx, sizeof(TrapContext));
    return get_kernel_sp() - sizeof(TrapContext);
}

void print_app_info() {
    info("[kernel] num_app = %d", app_manager.num_app);
    for (int i=0; i<app_manager.num_app; i++) {
        info("[kernel] app_%d [%p, %p)", i, app_manager.app_start[i], app_manager.app_start[i+1]);
    }
}

void load_app(int app_id) {

    info("[kernel] Loading app_%d", app_id);
    asm("fence.i");
    memset(APP_BASE_ADDRESS, 0, APP_SIZE_LIMIT);
    unsigned long app_size = app_manager.app_start[app_id + 1] - app_manager.app_start[app_id];
    memcpy(APP_BASE_ADDRESS, app_manager.app_start[app_id], app_size);
}

int get_current_app() {
    return app_manager.current_app;
}

void move_to_next_app() {
    app_manager.current_app += 1;
}

void init_app_manager(int num_app, void *app_start[]) {
    app_manager.num_app = num_app;
    for (int i=0; i<num_app + 1; i++) {
        app_manager.app_start[i] = app_start[i];
    }
    app_manager.current_app = 0;
    print_app_info();
}

extern void __restore(unsigned long ctx_addr);

void run_next_app() {
    int current_app = app_manager.current_app;
    info("current_app: %d", current_app);
    info("num_app: %d", app_manager.num_app);
    if (current_app >= app_manager.num_app) {
        info("%d个应用程序已执行完毕", current_app);
        while(1){}
    }
    load_app(current_app);
    move_to_next_app();
    __restore(push_context(init_app_context(APP_BASE_ADDRESS, get_user_sp())));
}
