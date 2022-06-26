#include "printf.h"
#include "syscall.h"

int main() {
    long current_time = sys_get_time();
    long wait_for = current_time + 3000;
    while (sys_get_time() < wait_for) {
        sys_yield();
    }
    printf("Test sleep OK!");
    return 0;
}