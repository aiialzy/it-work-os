#include "riscv.h"
#include "console.h"
#include "printf.h"
#include "log.h"
#include "batch.h"

void skernel();
void ekernel();
void stext();
void etext();
void srodata();
void erodata();
void sdata();
void edata();
void sbss();
void ebss();

void app_0_start();
void app_0_end();
void app_1_start();
void app_1_end();
void app_2_start();
void app_2_end();
void app_3_start();
void app_3_end();
void app_4_start();
void app_4_end();

extern void __alltraps();

void clear_bss() {
    for (void* p = &sbss; p < (void*)(&ebss); p++) {
        *(unsigned char*)p = 0;
    }
}

void print_memory_layout() {
    error("skernel: %p", &skernel);
    warn("stext: %p, etext: %p", &stext, &etext);
    info("srodata: %p, erodata: %p", &srodata, &erodata);
    debug("sdata: %p, edata: %p", &sdata, &edata);
    trace("sbss: %p, ebss: %p", &sbss, &ebss);
    error("ekernel: %p", &ekernel);
}

void print_status() {
    info("sstatus: %b", r_sstatus());
}

void inittrap() {
    w_stvec((unsigned long) __alltraps);
}

void main() {
    consoleinit();
    printfinit();
    clear_bss();

    inittrap();

    print_memory_layout();

    void *app_start[] = {app_0_start, app_1_start, app_2_start, app_3_start, app_4_start, app_4_end};
    init_app_manager(5, app_start);

    run_next_app();

    while (1) {
    }
}
