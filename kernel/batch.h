#define MAX_APP_NUM 16
#define APP_BASE_ADDRESS ((void *)0x80400000)
#define APP_SIZE_LIMIT 0x20000

#ifndef _AppManager
#define _AppManager

typedef struct {
    volatile int num_app;
    volatile int current_app;
    void *app_start[MAX_APP_NUM + 1];
} AppManager;

#endif

#define USER_STACK_SIZE (4096 * 2)
#define KERNEL_STACK_SIZE (4096 * 2)

unsigned long get_user_sp();
unsigned long get_kernel_sp();

void print_app_info();
void load_app(int app_id);
int get_current_app();
void move_to_next_app();
void init_app_manager(int num_app, void *app_start[]);
void run_next_app();
AppManager *get_app_manager();